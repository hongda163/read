#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	pid_t result;
	result=fork();
	if(result==-1)
	{
		printf("fork error\n");
	}
	else if(result==0)
	{	
		sleep(5);
		printf("the returned value is %d in child process!! \n my pid is %d \n",result,getpid());
		printf("%d",getppid());
	}
	else
	{
		printf("the returned value is %d  in father process!! \n my pid is %d\n",result,getppid());
	}
	return 0;
}
