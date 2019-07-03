# linux_kernel_module-training
kernel programming tutorials 
NOTE:we must have linux headers installed on our system to do any work 
related to kernel programming.
check with your distribution how to do this

we start with the bare hello program just to demonstare the flow of device
driver programming.
Note How different the program is laid as compared to the usual c programs.
The modules are said to leave in kernel space while the usual c applications operate in user space.
In the kernel space we do not have the usual c library but instead we have 
some modified libraries .
The immediate one to notice is the absence of printf function from our programs, the Kernel space alternative is printk.
Another notable feature is the absence of the main function , in kernel programming the entry point of our programs is the init module and the exit is the exit function
The two are specified with the macros module_init() and module_exit()

Linux allows us to load and unload modules dynamically(ie you can insert a module to the running kernel without need to reboot)

To load the modules in the system we use
insmod <module.ko>
the above requires sudo privillages
to unload the module
rmmod module
To check the modules installed 
lsmod

important: check how we can use modprobe to load and unload modules


//To test this drivers just download and uncompress them on your machine
Then cd into the directory you've uncompressed into and run make
make -it will compile the programs and give a .ko (kernel object ) which we are going to load into our machine using (sudo insmod *.ko)
To clean the directory just add the clean option to your make command
ie make clean

the make command will invoke the gcc compiler


