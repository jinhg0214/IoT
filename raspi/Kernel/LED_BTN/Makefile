KERNEL_PATH=/lib/modules/$(shell uname -r)/build

obj-m := ioc.o

total: app driver

app:
	gcc ./app.c -o ./app

driver:
	make -C $(KERNEL_PATH) M=$(PWD) modules

clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean
	rm -rf ./app
