/*************************************************************************
    > File Name: signal.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Sun 09 Dec 2018 10:21:03 PM PST
 ************************************************************************/
 
#include<stdio.h>
#include<signal.h>
#include<stdio.h>

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
	int a=0,b=0;
	printf("waiting for signal sigint or sigquit...\n");
	signal(SIGINT,my_func);
	a=signal(SIGINT,my_func);
	printf("address is %d\n",a);
	signal(SIGQUIT,my_func);
	b=signal(SIGQUIT,my_func);
	printf("address is %d\n",b);
	pause();

	exit(0);
}
