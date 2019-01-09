#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<errno.h>

#define buff_size			1024
#define in_files				3
#define time_delay			60
#define max(a,b)			((a>b)?(a):(b))


int main(void)
{
		int fds[in_files];
		char buff[buff_size];
		int i,res,real_read,maxfd;
		struct timeval  tv;
		fd_set inset,tmp_inset;
printf("ss\n");
		fds[0]=0;
	if((fds[1]=open("in1",O_RDONLY|O_NONBLOCK))<0)	
	{
			printf("open in1 error\n");
			return 1;
	}
	if((fds[2]=open("in2",O_RDONLY|O_NONBLOCK))<0)	
	{
			printf("open in2 error\n");
			return 1;
	}
	maxfd=max(max(fds[0],fds[1]),fds[2]);


	FD_ZERO(&inset);
	for(i=0;i<in_files;i++)
	{
			FD_SET(fds[i],&inset);
	}
	tv.tv_sec=time_delay;
	tv.tv_usec=0;


	while(FD_ISSET(fds[0],&inset)||FD_ISSET(fds[1],&inset)||FD_ISSET(fds[2],&inset))
	{
			tmp_inset=inset;
			res=select(maxfd+1,&tmp_inset,NULL,NULL,&tv);
			switch(res)
			{
					case -1:
					{
							printf("select error\n");
							return 1;
					}
					break;
					case 0:
					{
							printf("time out");
							return 1;
					}
					break;

					default:
					{
							
						for(i=0;i<in_files;i++)
						{
							if(FD_ISSET(fds[i],&tmp_inset))
							{
										memset(buff,0,buff_size);
								
								real_read=read(fds[i],buff,buff_size);

								if(real_read<0)
								{
										if(errno!=EAGAIN)
										{
												return 1;
										}
								}

								else if(!real_read)
								{
										close(fds[i]);
										FD_CLR(fds[i],&inset);

								}

								else
								{
										if(i==0)
										{
												if(buff[0]=='q'||(buff[0]=='Q'))
												{
														return 1;
												}
										}
										else
										{
												buff[real_read]='\0';
												printf("%s",buff);
										}
								}
							}
						
						}
					}

				break;
			}
	}
	return 0;
}
