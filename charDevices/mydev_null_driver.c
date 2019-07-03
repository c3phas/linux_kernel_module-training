//learning device drivers in linux
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

static dev_t first;//holds our major and minor number
static struct class *cl;//var for the device class
static struct cdev c_dev;//global var for character device structure
static int file_open(struct inode *i,struct file *fp){
	printk(KERN_INFO "the file is opened\n");
	return 0;

}
static int file_close(struct inode *i ,struct file *fp){

	printk(KERN_INFO "The file has been closed\n");
	return 0;
}
static ssize_t file_read(struct file *fp,char __user *buf,size_t len, loff_t *off){
	printk(KERN_INFO "the file will be read\n");
	return 0;
}
static ssize_t file_write(struct file *fp, const char *buf,size_t len,loff_t *off){
	printk(KERN_INFO "writing to the device\n");
	return len;

}
//the file opeartions include
struct file_operations fops = {

	.owner = THIS_MODULE,
	.open =  file_open,
	.release = file_close,
	.read = file_read,
	.write = file_write

};
//constructor and destructor
static int __init loadDriver(void)
{
	int ret;
	struct device *dev_ret;
	ret = alloc_chrdev_region(&first,0,1,"cephas");
	if ( ret < 0){
		return ret;
	}
	cl = class_create(THIS_MODULE,"chardrv");
	if ( IS_ERR(cl)){
		unregister_chrdev_region(first,1);
		return PTR_ERR(cl);
	}
	dev_ret = device_create(cl,NULL,first,NULL,"mynull");
	if (IS_ERR(dev_ret)){
		class_destroy(cl);
		unregister_chrdev_region(first,1);
		return PTR_ERR(dev_ret);
	
	}
	cdev_init(&c_dev,&fops);
	ret = cdev_add(&c_dev,first,1);
	if (ret  < 0){
		device_destroy(cl,first);
		class_destroy(cl);
		unregister_chrdev_region(first,1);
		return ret;
	}
	printk(KERN_INFO "loading the first driver\n");
	printk(KERN_INFO "major number is %d and minor number is %d\n",MAJOR(first),MINOR(first));
	return 0;


}
static void __exit unloadDriver(void)
{
	//unregister our driver
	//reverse the functions performed by the init module
	cdev_del(&c_dev);
	device_destroy(cl,first);
	class_destroy(cl);
	unregister_chrdev_region(first,1);
	printk(KERN_ALERT "unloading our driver\n");


}
//functions to call on loading and unloading
module_init(loadDriver);
module_exit(unloadDriver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CEPHAS");
MODULE_DESCRIPTION("works similar to the dev/null");
