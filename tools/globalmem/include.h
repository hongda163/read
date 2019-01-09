/*************************************************************************
    > File Name: char_mod.h
    > Author: hd6172
    > Mail: hd6172@163.com 
    > Created Time: Fri 28 Dec 2018 05:21:21 PM PST
 ************************************************************************/
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#define GLOBALMEM_SIZE 0X1000
#define MEM_CLEAR 0X1
#define GLOBALMEM_MAJOR 230
static int globalmem_major =GLOBALMEM_MAJOR;
module_param(globalmem_major,int,S_IRUGO);

struct globalmem_dev
{
	struct cdev cdev ;
	unsigned char mem[GLOBALMEM_SIZE];

};
struct globalmem_dev *globalmem_devp;

