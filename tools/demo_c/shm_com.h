/*************************************************************************
    > File Name: shm_com.h
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Mon 10 Dec 2018 06:26:34 PM PST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<signal.h>
#define shm_buff_sz 2048

struct shm_buff
{
	int pid;
	char buffer[shm_buff_sz];

};
