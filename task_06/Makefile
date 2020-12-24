## To prevent the kernel from complaining
## "module verification failed: signature and/or required key missing - tainting kernel"

CONFIG_MODULE_SIG=n

obj-m +=	rurtles_misc_char.o

all:
		make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

test:
		sudo dmesg -C
		sudo insmod rurtles_misc_char.ko
		sudo rmmod rurtles_misc_char
		dmesg

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
