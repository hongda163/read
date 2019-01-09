/*************************************************************************
    > File Name: sem_com.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Mon 10 Dec 2018 03:16:48 AM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<signal.h>
#include"sem_com.h"


#define delay_time  3
int main()
{
	pid_t result;
	int sem_id;

	sem_id=semget(ftok(".",'a'),1,0666|IPC_CREAT);
	init_sem(sem_id,0);

	result=fork();
	if(result==-1)
	{
		perror("fork\n");
	}
	else if(result==0)
	{
		printf("child process will wait for some seconds...\n");
		sleep(delay_time);
		printf("the returned value is %d in the child process(pid=%d)\n",result,getpid());
		sem_v(sem_id);
	}
	else
	{
		sem_p(sem_id);
		printf("The returned value is %d in the father process(PID = %d)\n", 
		result, getpid());
		sem_v(sem_id); 
		del_sem(sem_id);

	}
	exit(0);

}
