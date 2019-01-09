/*************************************************************************
    > File Name: hello.c
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Tue 25 Dec 2018 10:55:38 PM PST
 ************************************************************************/
#include<linux/init.h>
#include<linux/module.h>

static char *book_name="dissecting Linux device driver";
module_param(book_name,charp,S_IRUGO);

static int book_num=4000;
module_param(book_num,int,S_IRUGO);

static int __init book_init(void)
{
	
	printk(KERN_INFO"BOOK name:%s\n",book_name);
	printk(KERN_INFO"BOOK num;%d\n",book_num);
	printk(KERN_INFO"BOOK WOULD enter\n");
	return 0;
}
module_init(book_init);

static void __exit book_exit(void)
{
	printk(KERN_INFO"BOOK WOULD EXIT\n");

}
module_exit(book_exit);

MODULE_AUTHOR("BARRY SONG");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A SIMPLE");
MODULE_ALIAS("a simple");

