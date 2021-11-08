obj-m := test_linked_list.o
test_linked_list-objs := test_linked_list_module.o data_structure.o linked_list_api.o time_calculating.o utilities.o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.dwo *.mod *.order Module.symvers