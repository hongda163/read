/************************************************************************
    > File Name: producer.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Mon 10 Dec 2018 05:54:08 PM PST
 ************************************************************************/
#include"shm_com.h"
#include"sem_com.h"
int ignore_signal(void)
{
	signal(SIGINT,SIG_IGN);
	signal(SIGSTOP,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);

}

int main()
{
	void *share_memory=NULL;
	struct shm_buff *shm_buff_inst;
	char buffer[BUFSIZ];
	int shmid,semid;
	ignore_signal();
	semid=semget(ftok(".",'a'),1,0666|IPC_CREAT);
	init_sem(semid,1);

	shmid=shmget(ftok(".",'b'),sizeof(struct shm_buff),0666|IPC_CREAT);
	if(shmid==-1)
	{
		perror("shmget failed");
		del_sem(semid);
		exit(1);
	}

	share_memory=shmat(shmid,(void*)0,0);
	if(share_memory==(void*)-1)
	{
		perror("shmat");
		del_sem(semid);
		exit(1);
	}

	printf("memory attached at %X\n",(int)share_memory);
	shm_buff_inst = (struct shared_use_st *)share_memory;
	do
	{
		sem_p(semid);
		printf("enter some text to the shared memory (enter 'quit' to exit)");

		if(fgets(shm_buff_inst->buffer,shm_buff_sz,stdin)==NULL)
		{
			perror("fgets");
			sem_v(semid);
			break;

		}
		shm_buff_inst->pid=getpid();
		sem_v(semid);
	}while(strncmp(shm_buff_inst->buffer,"quit",4)!=0);
	del_sem(semid);

	if(shmdt(share_memory)==1)
	{
		perror("shmid");
		exit(1);
	}

	exit(0);
}
