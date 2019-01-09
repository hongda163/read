/*************************************************************************
    > File Name: cesi.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 01 Jan 2019 11:42:53 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/file.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int fd;
	char buf[40];
	memset(buf,0,20);
	fd=open("/dev/globalmem",O_RDWR|O_CREAT,0664);
	if(fd<0)
	{
			printf("open file error\n");
			exit(1);
	}
	ioctl(fd,0x01);
	if(read(fd,buf,20)<0)
	{
		printf("read\n");
		exit(1);
	}
	if(lseek(fd,0,SEEK_SET)<0)
	{
		perror("lseek");
		exit(1);
	}
	if(write(fd,"hello",5)<0)
	{
		printf("write\n");
		exit(1);
	}
	if(write(fd,"would",20)<0)
	{
		printf("write\n");
		exit(1);
	}
	if(lseek(fd,0,SEEK_SET)<0)
	{
		perror("lseek");
		exit(1);
	}	
	if(read(fd,buf,40)<0)
	{
		perror("read");
		exit(1);
	}	
	printf("%s",buf);
	close(fd);
	return 0;

}

