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
#include<signal.h>
#define port 4321
#define buffer_size 1024
int fun_sign(int sign);
char* list_check(int a,struct student *user,char *buf);
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
		struct sockaddr_in server_sockaddr,client_sockaddr,send;
		int sin_size,recvbytes;
		int sockfd,client_fd,shmid,b,sockfd1;
		char buf[buffer_size];
		char *shm_addr;
		struct student
		{
			char name[20];
			char ip[20];
		}user[20];
			char* list_check(int a,struct student *user,char *buf)
			{
				int i;
				for(i=0;i<a;i++)
				{

					if(strcmp(user[i].name,buf)==0)
						return user[i].ip;
					if(strcmp(user[i].ip,buf)==0)
						return user[i].name;
				}
				return NULL;
			}
		/*if ((shmid = shmget(IPC_PRIVATE,1024, 0666)) < 0)
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
		close(shmid);*/
		if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
		{
			perror("socket");
			exit(1);
		}
		if((sockfd1=socket(AF_INET,SOCK_DGRAM,0))==-1)
		{
			perror("socket");
			exit(1);
		}
		socklen_t len=sizeof(server_sockaddr);
		server_sockaddr.sin_family=AF_INET;
		server_sockaddr.sin_port=htons(port);
		server_sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		bzero(&(server_sockaddr.sin_zero),8);
		
		
		send.sin_family=AF_INET;
		send.sin_port=htons(port);
		bzero(&(send.sin_zero),8);
		if(bind(sockfd,(struct sockaddr *)&server_sockaddr,len)==-1)
		{
			perror("bind");
			exit(1);
		}
		printf("listening..........\n");
		memset(buf,0,sizeof(buf));
		int i=0;
		char *userip;
		char *check;
		while(1)
		{

			if((recvbytes=recvfrom(sockfd,buf,buffer_size,0,(struct sockaddr*)&server_sockaddr,&len))==-1)
			{
				perror("recv");
				exit(1);
			}			
			userip=(char *)inet_ntoa(server_sockaddr.sin_addr);
			if(strcmp(buf,"list")==0)
			{
				for(b=0;b<19;b++)
				{
					if(user[b].name[0]=='[')
					{
					printf("ip:%s %s\n",user[b].ip,user[b].name);
					}
				}
				continue;
			}
			if(strncmp(buf,"[offline]",(size_t)9)==0)
			{
				if(check=list_check((int)20,userip,buf)!=NULL)
				{
					memset(check,0,sizeof(user[1].name));
				}
				continue;
			}
		
			/*list data processing*/
		
			if((strncmp(buf,"[online]",(size_t)8))==0)
			{	

				if(check=(list_check((int)20,user,buf))!=NULL)
				continue;
				printf("ip%s %s\n",userip,buf);
				memset(user[i].name,0,sizeof(user[i].name));
				memset(user[i].ip,0,sizeof(user[i].ip));
				strcpy(user[i].ip,userip);
				strcpy(user[i].name,buf);
				send.sin_addr.s_addr=inet_addr(userip);
				if(	sendto(sockfd,"[iknow]hd",strlen("[iknow]hd"),0,(struct sockaddr*)&send,len)==-1)
				{
					perror("send to");
					exit(1);
				}		
				i++;
				if(i>20)
					i=0;
				memset(buf,0,sizeof(buf));
				continue;
			}
			if((strncmp(buf,"[iknow]",(size_t)7))==0)
			{	
			printf("ip%s %s\n",userip,buf);
				if(check=list_check((int)20,user,buf)!=NULL)
				continue;
				memset(user[i].name,0,sizeof(user[i].name));
				memset(user[i].ip,0,sizeof(user[i].ip));
				strcpy(user[i].ip,userip);
				strcpy(user[i].name,"[online]");
				strcpy((user[i].name)+8,buf+7);
				i++;
				if(i>20)
					i=0;
				memset(buf,0,sizeof(buf));
				continue;
			}
			printf("%s:  %s\n",list_check((int)20,user,userip),buf);	
			memset(buf,0,sizeof(buf));
		}



		close(sockfd);
		exit(0);
		
	}
	else
	{
		sleep(1);
		int sockfd,sendbytes,sockfd1;
		char buf[buffer_size];
		struct hostent *host;
		struct sockaddr_in serv_addr;
		char smsg[20];
		int res;
		socklen_t  nlen;
	
		if((sockfd1=socket(AF_INET,SOCK_DGRAM,0))==-1)
		{
			perror("socket");
			exit(1);
		}
		int rdo=0;
		const int opt=1;
		if(rdo=(setsockopt(sockfd1,SOL_SOCKET,SO_BROADCAST,(void*)&opt,sizeof(opt)))==-1)
		{
			perror("setsockopt");
			exit(1);
		}
		struct sockaddr_in addrto;
		addrto.sin_family=AF_INET;
		addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
		addrto.sin_port=htons(port);
		bzero(&(addrto.sin_zero),8);
		nlen=sizeof(addrto);
		void fun_sign(int sign_no)
		{
			if(sign_no==SIGINT)
			{
				strcpy(smsg,"[offline]");
				printf("offline\n");
				res=sendto(sockfd1,smsg,strlen(smsg),0,(struct sockaddr*)&addrto,nlen);
				if(res<0)
				{
					perror("sendto");
					exit(1);
				}
				close(sockfd);
				close(sockfd1);
				exit(0);
			}
		}
		signal(SIGINT,fun_sign);
		/*send message [online*/
		strcpy(smsg,"[online]hd");
		res=sendto(sockfd1,smsg,strlen(smsg),0,(struct sockaddr*)&addrto,nlen);
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
		serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		char bufip[20];
		do
		{	
			printf("plaese input char\n");
			scanf("%s",&buf);
			if(strcmp(buf,"list")==0)
			{
				serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
				if((sendbytes=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,
								sizeof(struct sockaddr_in)))==-1)
				{
				perror("send");
				exit(1);
				}
				serv_addr.sin_addr.s_addr=inet_addr(bufip);
				printf("list get\n");
				memset(buf,0,sizeof(buf));
				continue;
			}
			if(strncmp(buf,"//",2)==0)
			{	
				memset(bufip,0,sizeof(bufip));
				strcpy(bufip,(buf+2));
				serv_addr.sin_addr.s_addr=inet_addr(bufip);
				printf("getip %s\n",(buf+2));
				memset(buf,0,sizeof(buf));
				continue;
			}

			if((sendbytes=sendto(sockfd,buf,strlen(buf),0,

							(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in)))==-1)
			{
	
				perror("send");
				continue;
			}
			memset(buf,0,sizeof(buf));	
		}while(1);
		close(sockfd);
		printf("success\n");
		exit(0);
	}
}
