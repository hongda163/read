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
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/ipc.h>
#include<netdb.h>
#include <arpa/inet.h>
#define port 4321
#define buffer_size 1024
int main()
{

	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		perror("fork falied");
		exit(1);
	}

	if(pid>0)
	{
		printf("fatehr\n");
/*		int fun_sign(int sign_no)
		{
			if(sign_no==SIGNQUIT)
			{
				close(shmid);
			}
		}*/
		struct sockaddr_in server_sockaddr,client_sockaddr;
		int sin_size,recvbytes;
		int sockfd,client_fd,shmid;
		char buf[buffer_size];
		char *shm_addr;
		typedef	struct
		{
			char name[20];
			char* ip;
		}useronline,*puseronline;
		

		puseronline user1;
		useronline user[20],usercpy;
		if ((shmid = shmget(IPC_PRIVATE,1024, 0666)) < 0)
		{
			perror("shmget"); 
			exit(1);
		}
		else
		{
		printf("Create shared-memory: %d\n",shmid);
		}
		if ((shm_addr = shmat(shmid, NULL, 0)) == (void*)-1)
		{
			perror("Child: shmat");
			exit(1);
		}
		else
		{
			printf("Child: Attach shared-memory: %x\n", shm_addr);
		}
		close(shmid);
		if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
		{
			perror("socket");
			exit(1);
		}
		socklen_t len=sizeof(server_sockaddr);
		printf("socket id =%d \n",sockfd);
		server_sockaddr.sin_family=AF_INET;
		server_sockaddr.sin_port=htons(port);
		server_sockaddr.sin_addr.s_addr=INADDR_ANY;
		bzero(&(server_sockaddr.sin_zero),8);

		if(bind(sockfd,(struct sockaddr *)&server_sockaddr,len)==-1)
		{
			perror("bind");
			exit(1);
		}
		printf("listening..........\n");
		memset(buf,0,sizeof(buf));
		int i=0;
		char *userip;
		while(1)
		{

			if((recvbytes=recvfrom(sockfd,buf,buffer_size,0,(struct sockaddr*)&server_sockaddr,&len))==-1)
			{
				perror("recv");
				exit(1);
			}
			if(strcmp(buf,"//list")==0)
			{
				for(int a=0;i<20;i++)
				{
					printf("%s ip%s\n",user[a].name,user[a].ip);
				}
				continue;
			}
			userip=(char *)inet_ntoa(server_sockaddr.sin_addr);
			if((strncmp(buf,"[online]",(size_t)8)==0)||(strncmp(buf,"[iknow]",(size_t)7)==0))
			{	
			
				printf("%s\n",buf);
				user[i].ip=userip;
				strcpy(user[i].name,buf);
				sendto(sockfd,"[iknow]hda",sizeof(buf),0,(struct sockaddr*)&server_sockaddr,len);
				if(i>20)
					i=0;
				memset(buf,0,sizeof(buf));
				continue;
			}
				printf("ip:%s:  %s\n",userip,buf);	
			memset(buf,0,sizeof(buf));
		}
		close(sockfd);
		exit(0);
	}
	else
	{
		sleep(1);
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
			char smsg[20]="[online]hda";
			int res;
			res=sendto(sockfd,smsg,strlen(smsg),0,(struct sockaddr*)&addrto,nlen);
			if(res<0)
			{
			perror("sendto");
			exit(1);
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
		printf("please input ip\n");
		gets(bufip);
		do
		{	printf("plaese input char\n");
			gets(buf);
			if(strcmp(buf,"//list")==0)
			{
				serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
				printf("list\n");
				if((sendbytes=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,
								sizeof(struct sockaddr_in)))==-1)
				{
				perror("send");
				exit(1);
				}
				continue;
			}
			if(strcmp(buf,"byby@")==0)
			{
				printf("please input ip\n");
				memset(bufip,0,sizeof(bufip));
				gets(bufip);
			printf("getip\n");
			continue;
			}
			serv_addr.sin_addr.s_addr=inet_addr(bufip);
			if((sendbytes=sendto(sockfd,buf,strlen(buf),0,
							(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in)))==-1)
			{
				perror("send");
				continue;
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
}
