/*************************************************************************
    > File Name: alarm_pause.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Sun 09 Dec 2018 11:18:15 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
int main()
{
	int ret=alarm(5);
	printf("waiting alarm time over\n");
	pause();
	printf("i have been waken up %d.\n",ret);

}

