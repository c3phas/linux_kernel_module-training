#makefile for our little programe
#we need a makefile to build a loadavle kernel module
#note in makefile we use Tabs after specifying the rule
obj-m := hello.o
KVERSION=$(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
