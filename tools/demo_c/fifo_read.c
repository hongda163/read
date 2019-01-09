/*************************************************************************
    > File Name: fifo_read.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Fri 07 Dec 2018 03:56:23 PM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define myfifo "/tmp/myfifo"
#define max_buff_size  255

int main()
{
	char buff[max_buff_size];
	int fd;
	int nread;


	if(access(myfifo,F_OK)==-1)
	{
		if((mkfifo(myfifo,0666)<0)&&(errno!=EEXIST))
		{
			printf("cannot create fifo file\n");
			exit(1);
		
		}
	}	
		fd=open(myfifo,O_RDONLY);
		if(fd==-1)
		{
			printf("open fifo file error\n");
			exit(1);
		}
		while(1)
		{
			memset(buff,0,sizeof(buff));
			if((nread=read(fd,buff,max_buff_size))>0)
			{
				printf("read '%s'' from fifo \n",buff);
			}
		}

		close(fd);
		exit(0);
	}

	

	

			






