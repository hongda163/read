KVERS= /home/user1/disk2/buildroot-2018.11.1/output/build/linux-custom
obj-m += mmap2.o
arm=/home/user1/disk2/buildroot-2018.11.1/output/host/bin/aarch64-linux-
build:kernel_modules

kernel_modules:
	make ARCH=arm64 CROSS_COMPILE=$(arm) -C $(KVERS) M=$(CURDIR) modules
clean:
	make -C $(KVERS)	 M=$(CURDIR) clean
