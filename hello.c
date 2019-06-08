/*lets do some kernel stuff*/
/*include the necessary headers */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

//the default word to supply incase no arguements are given
static char *name = "world";
//module_param allows arguements to be supplied to the command line
module_param(name, charp, S_IRUGO);
//initialization module
static int __init hello_int(void)
{
	printk(KERN_ALERT "hello %s module starting\n",name);
	return 0;

}
//call this when we exit the program
static void __exit hello_exit(void)
{
	printk( "exiting the hello %s kernel module\n",name);


}
module_init(hello_int);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CEPHAS");

