int lock_set(int fd,int type)
{
		struct flock old_lock,lock;
		lock.l_whence=SEEK_SET;
		lock.l_start=0;
		lock.l_len=0;
		lock.l_type=type;
		lock.l_pid=-1;

fcntl(fd,F_GETLK,&lock);
if(lock.l_type!=F_UNLCK)
{
		if(lock.l_type==F_RDLCK)
		{
				printf("read lock already set by %d\n",lock.l_pid);
		}
		else if(lock.l_type==F_WRLCK)
		{
				printf("write lock already set by %d\n",lock.l_pid);
		}

}
lock.l_type=type;
fcntl(fd,F_SETLKW,&lock);//zhu she shi shang suo
if((fcntl(fd,F_SETLKW,lock))<0)
{
		printf("lock failed:type=%d\n",lock.l_type);
}
switch(lock.l_type)
{
		case F_RDLCK:
				{
						printf("read lock set by %d \n",getpid());
						
				}
				break;
		case F_WRLCK:                                                      
                {
                        printf("WRITE lock set by %d \n",getpid());
                }
				break;
		case F_UNLCK:
				{
						printf("RELEASE lock set by %d \n",getpid());
						return 1;
				}
				break;
}
return 0;
}
