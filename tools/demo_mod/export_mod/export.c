/*************************************************************************
    > File Name: hello.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 25 Dec 2018 10:55:38 PM PST
 ************************************************************************/
#include<linux/init.h>
#include<linux/module.h>

 
int add_integar(int a,int b)
{
	return a+b;
}
EXPORT_SYMBOL_GPL(add_integar);

int sub_integar(int a,int b)
{
	return a-b;
}
EXPORT_SYMBOL_GPL(sub_integar);
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

