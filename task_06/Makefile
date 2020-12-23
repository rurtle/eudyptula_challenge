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
