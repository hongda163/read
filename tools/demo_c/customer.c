/*************************************************************************
    > File Name: customer.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Mon 10 Dec 2018 06:32:59 PM PST
 ************************************************************************/

#include<stdio.h>
#include"shm_com.h"
#include"sem_com.h"
int main()
{

	void *shared_memory=NULL;
	struct shm_buff *shm_buff_inst;
	int shmid,semid;
	semid=semget(ftok(".",'a'),1,0666);
	if(semid==-1)
{
	perror("producer is'nt exist");
	exit(1);
}
shmid=shmget(ftok(".",'b'),sizeof(struct shm_buff),0666|IPC_CREAT);
if(shmid==-1)
{
	perror("shmget");
	exit(1);
}
shared_memory=shmat(shmid,(void*)0,0);
if(shared_memory==(void*)-1)
{
	perror("shmat");
	exit(1);

}

printf("memory attached at %X\n",(int)shared_memory);

shm_buff_inst=(struct shm_buff *)shared_memory;
do
{
	sem_p(semid);
	printf("shared memory was written by process%d :%s",shm_buff_inst->pid,shm_buff_inst->buffer);
	if(strncmp(shm_buff_inst->buffer,"quit",4)==0)
	{
		break;
	}
	shm_buff_inst->pid=0;
	memset(shm_buff_inst->buffer,0,shm_buff_sz);
	sem_v(semid);
}while(1);

if(shmdt(shared_memory)==-1)
{
	perror("shmdt");
	exit(1);
}
if(shmctl(shmid,IPC_RMID,NULL)==-1);
{
	perror("shmctl(IPC_RMID)");
	exit(1);
}
exit(0);
}
