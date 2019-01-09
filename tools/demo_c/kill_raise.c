/*************************************************************************
    > File Name: kill_raise.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Sun 09 Dec 2018 10:46:41 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	int ret;
	if((pid=fork())<0)
	{
		printf("fork error\n");
		exit(1);
	}

	if(pid==0)
	{
		printf("child(pid:%d) is waiting for any signal\n",getpid());
		raise(SIGSTOP);
		exit(0);
	}
	if(pid>0)
	{
		sleep(2);
		if((waitpid(pid,NULL,WNOHANG))==0)
		{
			if((ret=kill(pid,SIGKILL))==0)
			{
				printf("Parent kill %d\n",pid);
			}
		}
		waitpid(pid,NULL,0);
		exit(0);
	}
}

