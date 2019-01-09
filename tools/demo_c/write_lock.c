#include<unistd.h>
#include<sys/file.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include"lock_set.c"
int lock_set(int fd,int type);
int main()
{
		int fd;
		fd=open("hello",O_RDWR|O_CREAT,0664);
		if(fd<0)
		{
				printf("open file error\n");
				exit(1);
		}
		lock_set(fd,F_WRLCK);
		getchar();
		lock_set(fd,F_UNLCK);
		getchar();
		close(fd);
		exit(0);
}
