/*************************************************************************
    > File Name: fifo_write.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Fri 07 Dec 2018 03:42:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<limits.h>

#define myfifo "/tmp/myfifo"
#define max_buffer_size 255

int main()
{

	int fd;
	char buff[max_buffer_size];
	int nwrite;
	fd=open(myfifo,O_WRONLY);

	if(fd==-1)
	{
		printf("open myfifo error");
		exit(1);
	}
	scanf("%s",buff);
	if((nwrite=write(fd,buff,max_buffer_size))>0)
	{
		printf("write '%s'' to fifo\n",buff);
	}
	close(fd);
	exit(0);
}
