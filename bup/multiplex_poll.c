#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<errno.h>
#include<poll.h>

#define buff_size			1024
#define in_files				3
#define time_delay			60


int main(void)
{
		struct pollfd  fds[in_files];
		char buff[buff_size];
		int i,res,real_read,maxfd;
		fds[0].fd=0;
	if((fds[1].fd=open("in1",O_RDONLY|O_NONBLOCK))<0)	
	{
			printf("open in1 error\n");
			return 1;
	}
	if((fds[2].fd=open("in2",O_RDONLY|O_NONBLOCK))<0)	
	{
			printf("open in2 error\n");
			return 1;
	}
	
	for(i=0;i<in_files;i++)
	{
		fds[i].events=POLLIN;
	}
	while(fds[0].events||fds[1].events||fds[2].events)
	{
		if(poll(fds,in_files,0)<0)
		{
			printf("poll error\n");
			return 1;
		}
		for(i=0;i<in_files;i++)
		{
			if(fds[i].revents)
			{
				memset(buff,0,buff_size);
				real_read=read(fds[i].fd,buff,buff_size);

				if(real_read<0)
				{
					if(errno!=EAGAIN)
					{
						return 1;
					}

				}
				else if(!real_read)
				{
					close(fds[i].fd);
					fds[i].events=0;
				}
				else
				{
					if(i==0)
					{
						if(buff[0]=='1'||buff[0]=='Q')
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
	return 0;
}
