/*************************************************************************
    > File Name: cesi.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 08 Jan 2019 03:44:55 AM PST
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h>  
  
int main( void )  
{  
    int fd;
	int a;
    unsigned int *p;  
    unsigned int *mapBuf;  
    fd = open("/dev/mmap", O_RDWR);//打开设备文件，内核就能获取设备文 
    if(fd<0)  
    {  
        printf("open device is error,fd = %d\n",fd);  
        return -1;  
    }  
    /*测试一：查看内存映射段*/  
    printf("before mmap\n");  
  
  
    mapBuf = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);//内存映射，会调用驱动的mmap函数 

	p=mapBuf;
    printf("after mmap\n");
	*(mapBuf+1)|=(unsigned int)1<<24;
	*(mapBuf+7)=(unsigned int)1<<18;

	a=(*(p+13)>>18)&1;
	printf("addr %x\n",a);
	sleep(1);
	*(p+10)=(unsigned int)1<<18;
		
	a=(*(p+13)>>18)&1;
	printf("addr %x\n",a);
   
      
      
    munmap(mapBuf, 1024);//去除映射     
    close(fd);//关闭文件，最终调用驱动的close  
    return 0;  
}
