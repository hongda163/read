/*************************************************************************
    > File Name: server.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Wed 12 Dec 2018 10:43:50 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>

#define port 4321
#define buffer_size 1024
#define max_que_conn_nm 5

int main()
{
	struct sockaddr_in server_sockaddr,client_sockaddr;
	int sin_size,recvbytes;
	int sockfd,client_fd;
	char buf[buffer_size];
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);

	}
	printf("socket id =%d \n",sockfd);
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(port);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);

	int i=1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));

	if(bind(sockfd,(struct sockaddr*)&server_sockaddr,
				sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}
	
	if(listen(sockfd,max_que_conn_nm)==-1)
	{
		perror("listen");
		exit(1);

	}
	printf("listening..........\n");
	if((client_fd=accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size))==-1)
	{
	
		perror("accept");
		exit(1);
	}
	do
	{
		if((recvbytes=recv(client_fd,buf,buffer_size,0))==-1)
		{
			perror("recv");
			exit(1);
		}
		printf("received message: %s\n",buf);	
		if(buf[0]=='q'&&(strlen(buf)==1))
			break;
		memset(buf,0,sizeof(buf));
	}while(1);
	
	close(sockfd);
	exit(0);
}
