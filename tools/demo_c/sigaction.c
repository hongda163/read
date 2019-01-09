/*************************************************************************
    > File Name: sigaction.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Sun 09 Dec 2018 10:21:03 PM PST
 ************************************************************************/
 
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void my_func(int sign_no)
{
	if(sign_no==SIGINT)
	{
		printf("I have get SIGNINT\n");
	}
	else if(sign_no==SIGQUIT)
	{
		printf("i have get SIGQUI");
	}
}

int main()
{
	struct sigaction action;
	action.sa_handler=my_func;
	sigemptyset(&action.sa_mask);
	action.sa_flags=0;

	printf("waiting for signal sigint or sigquit...\n");
	sigaction(SIGINT,&action,0);
	sigaction(SIGQUIT,&action,0);
	pause();
	exit(0);
}
