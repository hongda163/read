/*************************************************************************
    > File Name: globalmem_fun.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Fri 28 Dec 2018 05:51:43 PM PST
 ************************************************************************/
#include"include.h"
#include<linux/io.h>
#include<linux/mman.h>
#define  ADDR (u32)0x3f200000
u32 *pp=NULL;
u32 *p1=NULL;
static ssize_t globalmem_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
	unsigned long p=*ppos;
	unsigned int count =size;
	int ret=0;
	struct globalmem_dev *dev=filp->private_data;

	if (p>=GLOBALMEM_SIZE)
		return 0;
	if(count>GLOBALMEM_SIZE-p)
		count=GLOBALMEM_SIZE-p;

	if(copy_to_user(buf,dev->mem+p,count)){
		ret=-EFAULT;
	}else
	{
		*ppos+=count;
		ret=count;
		printk(KERN_INFO"read %u bytes(s) from %lu\n",count,p);

	}
	return ret;
	printk(KERN_INFO"READ BYTR\n");
	return 0;	
}
static ssize_t globalmem_write(struct file *filp,const char __user *buf,
		size_t size,loff_t *ppos)
{
	u32  *p3;
	p3=pp+0x2;
	writel(0x00000008,p3);
	p3=pp+0x07;
	writel(0x00f40000,p3);
	unsigned long  p =*ppos;
	unsigned int count=size;
	int ret=0;
	struct globalmem_dev *dev=filp->private_data;
	if(p>=GLOBALMEM_SIZE)
		return 0;
	if(count>GLOBALMEM_SIZE-p)
		count=GLOBALMEM_SIZE-p;

	if(copy_from_user(dev->mem+p,buf,count))
		ret=-EFAULT;
	else{
		*ppos+=count;
		ret=count;
		printk(KERN_INFO"writen %u bytes(s) from %lu\n",count,p);
	}
	return ret;
}
static loff_t globalmem_llseek(struct file *filp, loff_t offset,int orig)
{
	loff_t ret=0;
	switch (orig){
		case 0:
			if(offset<0){
				ret=-EINVAL;
				break;
			}
			if((unsigned int)offset>GLOBALMEM_SIZE){
				ret=-EINVAL;
				break;
			}
			filp->f_pos=(unsigned int)offset;
			ret = filp->f_pos;
			break;
		case 1:
			if((filp->f_pos+offset)>GLOBALMEM_SIZE) {
				ret=-EINVAL;
				break;
			}
			if((filp->f_pos+offset)<0) {
				ret=-EINVAL;
				break;
			}
			filp->f_pos+=offset;
			ret=filp->f_pos;
			break;
		default:
			ret=-EINVAL;
			break;
	}
	return ret;
}
static int globalmem_open(struct inode *innod ,struct file *filp)
{
	filp->private_data=globalmem_devp;
	return 0;
}
static long globalmem_ioctl(struct file *filp,unsigned int cmd,
		unsigned long arg)
{
	struct globalmem_dev *dev=filp->private_data;
	switch(cmd)
	{
		case MEM_CLEAR:
			memset(dev->mem,0,GLOBALMEM_SIZE);
			printk(KERN_INFO"globalmem is set to zero\n");
			break;
		default:
			return -EINVAL;
	}
	return 0;
}
static const struct file_operations globalmem_fops={
	.owner=THIS_MODULE,
	.llseek=globalmem_llseek,
	.read=globalmem_read,
	.write=globalmem_write,
	.unlocked_ioctl=globalmem_ioctl,
	.open=globalmem_open,
//	.release=globalmem_release,
};
static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)
{
	int err,devno=MKDEV(globalmem_major,index);
	cdev_init(&dev->cdev,&globalmem_fops);
	dev->cdev.owner=THIS_MODULE;
	err=cdev_add(&dev->cdev,devno,1);
	if(err)
		printk(KERN_NOTICE"Error %d adding globalmem %d",err,index);
}
static int __init globalmem_init(void)
{
	int ret;
	char b;
	request_mem_region(ADDR,44*4,&b);
	pp=ioremap(ADDR,44*4);
	p1=pp;
	dev_t devno=MKDEV(globalmem_major,0);
	if(globalmem_major)
		ret=register_chrdev_region(devno,1,"globalmem");
	else
	{
		ret=alloc_chrdev_region(&devno,0,1,"globalmem");
		globalmem_major=MAJOR(devno);
		
	}

	if(ret<0)
		return ret;

	globalmem_devp=kzalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
		if(!globalmem_devp)
		{
			ret=ENOMEM;
	//		goto fail_malloc;	
			}
		globalmem_setup_cdev(globalmem_devp,0);
		return 0;

//			fail_malloc;
		unregister_chrdev_region(devno,1);
		return ret;
}	








/*
static long globalmem_ioctl(struct file *filp,unsigned int cmd,
		unsignedd long arg)
{
	struct globalmem_dev *dev=filp->private_data;
	switch(cmd)
	{
		case MEM_CLEAR:
			memset(dev->mem,0,GLOBALMEM_SIZE);
			printk(FERN_INFO"globalmem is set to zero\n");
			break;
		default:
			return -EINVAL;
	}
	return 0;
}*/
static void __exit globalmem_exit(void)
{
	printk(KERN_INFO"IOMEM EXIT\n");
	cdev_del(&globalmem_devp->cdev);
	iounmap(pp);
	release_mem_region(ADDR,44*4);
}

	module_exit(globalmem_exit);
	module_init(globalmem_init);
