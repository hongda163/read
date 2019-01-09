/*************************************************************************
    > File Name: ss.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Sun 06 Jan 2019 06:31:02 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/file.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#define GPIO_OUT 33
#define GPIO_W 34
#define GPIO_R 35
#define GPIO_PIN_VL 0X0001001a
#define GPIO 0X00000001a
    


//#include<sys/file.h>
int main()
{
	int ret;
	int fd;
	char buf[5];
	fd=open("/dev/iomem",O_RDWR,0);
		printf("write end\n");
		ioctl(fd,GPIO_OUT,GPIO_PIN_VL);
		ioctl(fd,GPIO_W,GPIO_PIN_VL);
		ret=ioctl(fd,GPIO_R,GPIO);
sleep(1);
		printf("write%x\n",ret);
			ioctl(fd,GPIO_W,GPIO);
		ret=ioctl(fd,GPIO_R,GPIO);

		printf("write%x\n",ret);
		printf("write end\n");
		sleep(1);
	return 0;
}
