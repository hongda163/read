/*************************************************************************
    > File Name: pipe.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Thu 06 Dec 2018 10:13:51 PM PST
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define max_data_len  256
#define delay_time  1
int main()
{
	pid_t pid;
	int a,b=0;
	int pipe_fd[2];
	char buf[max_data_len];
	 char data[]="pipe test program";
	data[17]='a';
	data[16]='a';
	int real_read,real_write;
	memset(buf,0,sizeof(buf));
		if(pipe(pipe_fd)<0)
		{
			printf("pipe creat error\n");
			exit(1);
		}
		if((pid=fork())==0)
		{
			close(pipe_fd[1]);
			sleep(delay_time*3);
			while((real_read=read(pipe_fd[0],buf,max_data_len))>0)
			{
				printf("%d %s;\n",b,buf);
			}
			close(pipe_fd[0]);
			exit(0);
		}
	else if(pid>0)
	{
		close(pipe_fd[0]);
		sleep(delay_time);
		if((real_write=write(pipe_fd[1],data,strlen(data)))!=-1)
		{
			printf("%dwrite%s\n",real_write,data);
		}
		close(pipe_fd[1]);
		waitpid(pid,NULL,0);
		exit(0);
	}
}
