/*************************************************************************
    > File Name: shmem.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 11 Dec 2018 02:02:09 AM PST
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#define buffer_size 2048
int main()
{
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
		system("ipcs -m");
		while(strncmp(shm_addr,flag,strlen(flag)))
		{
			printf("child:wait for enable data...\n");
			sleep(5);

		}
	printf("Child: Shared-memory :%s\n", shm_addr);
		if((shmdt(shm_addr))<0)
		{
			perror("shmdt");
			exit(1);

		}
	
		if(shmctl(shmid,IPC_RMID,NULL)==-1)
		{
			perror("child:shmctl(ipc_rmid\n)");
			exit(1);
		}
		else
		{
			printf("delete shared-memory\n");
		}
		system("ipcs -m");
	}
	else
	{
		if((shm_addr=shmat(shmid,0,0))==(void*)-1)
		{
			perror("parent:ahmat");
			exit(1);
		}
		else
		{
			printf("parent:attach shared-memory:%p\n",shm_addr);
		}
		sleep(1);
		printf("\ninput some string:\n");
		fgets(buff,buffer_size,stdin);
		printf("aaaa%s\n",buff);
		strncpy(shm_addr+strlen(flag),buff,strlen(buff));
		strncpy(shm_addr,flag,strlen(flag));


		if((shmdt(shm_addr))<0)
		{
			perror("parent:shmdt");
			exit(1);
		}
		system("ipcs -m");
		waitpid(pid,NULL,0);
		printf("finished\n");
	}
	exit(0);
}
