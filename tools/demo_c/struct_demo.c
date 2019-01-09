/*************************************************************************
    > File Name: struct_demo.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 25 Dec 2018 05:00:14 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#define buffer_size 1024
int main()
{
	typedef struct
	
	{
		int b;
		int a;
	// *b;
	}u;
	u usr,*usr1;
		pid_t pid;
	int shmid;
	char *shm_addr;
	char flag[]="wrote";
	char buff[2048];
	if((shmid=shmget(IPC_PRIVATE,buffer_size,0666))<0)
	{
		perror("shmget");
		exit(1);
	}
	else
	{
		printf("create shared-memory:%d\n",shmid);
	}
	system("ipcs -m");
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		exit(1);
	}
	else if(pid==0)
	{
		if((shm_addr=shmat(shmid,0,0))==(void*)-1)
		{
			perror("child:shmat");
			exit(1);
		}
		else
		{
			printf("child;attach shared-memory:%p\n",shm_addr);
		}
	}
	usr1=(u*)shm_addr;
	usr1->a=16;
	printf("%d\n",usr1);
	printf("%d\n",usr1->a);
	printf("aaaa\n");
	return 0;
}
