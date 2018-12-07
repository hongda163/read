/*************************************************************************
    > File Name: waitpid.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 05 Dec 2018 11:54:27 PM PST
 ************************************************************************/
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
	pid_t pc,pr;
	int i;
	pc=fork();
	if(pc<0)
	{
		printf("error fork\n");

	}
	else if(pc==0)
	{
		sleep(5);
		exit(5);

	}
	else
	{
		do
		{
			pr=waitpid(pc,&i,WNOHANG);
			if(pr==0)
			printf("The child process has not exited\n");
			sleep(1);

		}while(pr==0);


		if(pr==pc)
		{
			printf("Get child exit code:%d\n",pr);
		printf("get child statu %d \n",i>>8);
		}
		else
		{ printf("Some error occured.\n");
		}
	}
}
