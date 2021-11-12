KERNEL_PATH=/usr/src/linux

obj-m := frame.o

total: app driver

app:
	gcc ./app.c -o ./app

driver:
	make -C $(KERNEL_PATH) M=$(PWD) modules

clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean
	rm -rf ./app
