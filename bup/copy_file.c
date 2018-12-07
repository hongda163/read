#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define filename "src_file"
#define filename1 "desk_file"
#define buff_size 1024
#define change_pi 1
int main()
{
		int src_file,desk_file;
		int real_read_len;
		unsigned char buff[buff_size];
		src_file=open(filename,O_RDONLY);
		desk_file=open(filename1,
						O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if(src_file<0||desk_file<0)
		{
				printf("open file error");
		}
		lseek(src_file,change_pi,SEEK_SET);
		while((real_read_len=read(src_file,buff,sizeof(buff)))>0)
		{	
				write(desk_file,buff,real_read_len);
		}
		printf("%s",buff);
		close(src_file);
		close(desk_file);
		return 0;
}
