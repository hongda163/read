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
/*
int ctrl_c(void)
{
		close()
}*/
int main()
{
	int sockfd,sendbytes;
	char buf[buffer_size];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	int rdo=0;
	const int opt=1;
	if(rdo=(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,(void*)&opt,sizeof(opt)))==-1)
	{
		perror("setsockopt");
		exit(1);
	}
	struct sockaddr_in addrto;
	addrto.sin_family=AF_INET;
	addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
	addrto.sin_port=htons(port);
	bzero(&(addrto.sin_zero),8);
	socklen_t  nlen=sizeof(addrto);
	
	/*send message [online*/
	while(1)
	{

	
		sleep(1);
		char smsg[20]="[online]hda";
		int res;
		res=sendto(sockfd,smsg,strlen(smsg),0,(struct sockaddr*)&addrto,nlen);
		if(res<0)
		{
		perror("sendto");
		exit(1);
		}
	}
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}

	memset(buf,0,sizeof(buf));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port);
	bzero(&(serv_addr.sin_zero),8);
	char bufip[20];
gets(bufip);
	do
	{
		gets(buf);
		if(strcmp(buf,"beybey@")==0)
		{
			memset(bufip,0,sizeof(bufip));
			gets(bufip);
		printf("getip\n");
		}
		serv_addr.sin_addr.s_addr=inet_aton(bufip);
		if((sendbytes=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in)))==-1)
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
