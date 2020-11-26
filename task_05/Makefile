obj-m +=	rurtles_hello.o

all:
		make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

test:
		sudo dmesg -C
		sudo insmod rurtles_hello.ko
		sudo rmmod rurtles_hello
		dmesg

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
