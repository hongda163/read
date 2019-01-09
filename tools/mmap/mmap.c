/*************************************************************************
    > File Name: globalmem_fun.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Fri 28 Dec 2018 05:51:43 PM PST
 ************************************************************************/
#include"include.h"
#include<linux/io.h>
#include<linux/mman.h>
u32 *buf = NULL; 
#define  ADDR (u32)0x3f200000
u32 *pp=NULL;
static ssize_t globalmem_read(struct file *filp, char __user *buf,size_t size,loff_t *ppos)
{
	return 0;
}
static ssize_t globalmem_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
	return 0;
}
static loff_t globalmem_llseek(struct file *filp, loff_t offset,int orig)
{
	return 0;
}
static int globalmem_open(struct inode *innod ,struct file *filp)
{
	return 0;
}
static long globalmem_ioctl(struct file *filp,unsigned int cmd,
		unsigned long arg)
{
	return 0;
	
}
static int device_mmap(struct file *file, struct vm_area_struct *vma)
{
	vma->vm_page_prot=pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff=(u32)0x3f200000>>PAGE_SHIFT;
	if(remap_pfn_range(vma,vma->vm_start,vma->vm_pgoff, vma->vm_end - vma->vm_start, vma->vm_page_prot))//保护属性，
    {
        return -EAGAIN;
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
	 .mmap = device_mmap,
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
			}
		globalmem_setup_cdev(globalmem_devp,0);
		return 0;
		unregister_chrdev_region(devno,1);
		return ret;
}
static void __exit globalmem_exit(void)
{
	printk(KERN_INFO"IOMEM EXIT\n");
	cdev_del(&globalmem_devp->cdev);
	kfree(globalmem_devp);
	unregister_chrdev_region(MKDEV(globalmem_major,0),1);
	iounmap(pp);
	release_mem_region(ADDR,44*4);
}
	module_init(globalmem_init);
	module_exit(globalmem_exit);
MODULE_AUTHOR("HONGDA");
MODULE_LICENSE("GPL V1");
