CONFIG_MODULE_SIG=n
CONFIG_MODULE_FORCE_UNLOAD=y
obj-m += filter.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
