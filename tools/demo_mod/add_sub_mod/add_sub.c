/*************************************************************************
    > File Name: hello.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 25 Dec 2018 10:55:38 PM PST
 ************************************************************************/
#include<linux/init.h>
#include<linux/module.h>
int add_integar(int a,int b);
int sub_integar(int a,int b);

static int a=7;
module_param(a,int,S_IRUGO);

static int b=1;
module_param(b,int,S_IRUGO);

static int __init  yun(void)
{
	

	
	printk(KERN_INFO"add:a+b=%d\n",add_integar(a,b));
	printk(KERN_INFO"sub:a-b=%d\n",sub_integar(a,b));
	return 0;
}

module_init(yun);
/*static int __init hello_init(void)
{
	printk(KERN_INFO"HELLO WOULD enter\n");
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO"HELLO WOULD EXIT\n");

}
module_exit(hello_exit);*/

MODULE_AUTHOR("BARRY SONG");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A SIMPLE");
MODULE_ALIAS("a simple");

