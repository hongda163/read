/*************************************************************************
    > File Name: hello.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 25 Dec 2018 10:55:38 PM PST
 ************************************************************************/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/io.h>
#include<linux/mman.h>
#define  ADDR (u32)0x3f200000 
u32  *p=NULL;
static int __init hello_init(void)
{
	u32 a;
	char b;
	u32 *p1;
	request_mem_region(ADDR,44*4,&b);
	p=ioremap(ADDR,4);
	p1=p;
	p1=p1+0x02;
	*p1=(u32)0x00f40000;
	p1=p;
	p1=p1+0xa;	
	writel(0x00000008,p1);
//	*p1=(u32)0x00000008;


//a=(int)readl(p);
//writel((u32)0xffffffff,p);

a=(u32)readl(p1);
	printk("HELLO WOULD enter %x %x\n",p1,*p1);
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO"HELLO WOULD EXIT\n");
	iounmap(p);
	release_mem_region(ADDR,44*4);
}
module_exit(hello_exit);

MODULE_AUTHOR("BARRY SONG");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A SIMPLE");
MODULE_ALIAS("a simple");

