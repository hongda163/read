/*************************************************************************
    > File Name: client.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Wed 12 Dec 2018 11:28:47 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define port 4321
 #define buffer_size 1024
int main(int a,char *argv[])
{
	int sockfd,sendbytes;
	char buf[buffer_size];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	
	if ((host = gethostbyname("localhost")) == NULL)
	{	
		perror("gethostbyname"); 
		exit(1);	
	}
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%s",argv[2]);

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port);
	serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);

	
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connent");
		exit(1);

	}
	do
	{
		gets(buf);
	if((sendbytes=send(sockfd,buf,strlen(buf),0))==-1)
	{
		perror("send");
		exit(1);
	}
	memset(buf,0,sizeof(buf));
		if(buf[0]=='q'&&strlen(buf)==1)
			break;
	}
	while(1);
	close(sockfd);
	printf("success\n");
	exit(0);
}
