// SPDX-License-Identifier: GPL-3.0+
// Author: Subhra Sankha Sarkar <rurtle.coder@gmail.com>

/*
 * @brief	Task 06 - Write a misc char device driver
 */
#include <linux/init.h>
#include <linux/module.h>				/* Needed by all modules */
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rurtle");
MODULE_DESCRIPTION("Eudyptual Challenge - Task 06 - misc char driver");
MODULE_VERSION("0.01");

#define	MY_ID		"XxXxXxXxXxXx"
#define	ID_LEN		sizeof(MY_ID)

static int dev_opened;

static int rurtles_misc_open(struct inode *ip, struct file *fp)
{
	if (xchg(&dev_opened, 1))
		return -EBUSY;
	return 0;
}

static int rurtles_misc_release(struct inode *ip, struct file *fp)
{
	dev_opened = 0;
	return 0;
}

static ssize_t rurtles_misc_read(struct file *fp, char __user *buf,
				 size_t nbytes, loff_t *ppos)
{
	char *my_id = MY_ID;
	int len = ID_LEN;

	return simple_read_from_buffer(buf, nbytes, ppos, my_id, len);
}

static const struct file_operations rurtles_misc_fops = {
	.owner			= THIS_MODULE,
	.read			= rurtles_misc_read,
	.open			= rurtles_misc_open,
	.release		= rurtles_misc_release,
#if 0
	.write			= rurtles_misc_write,
#endif
};

static struct miscdevice rurtles_misc_dev = {
	.name			= "eudyptula",
	.minor			= MISC_DYNAMIC_MINOR,
	.fops			= &rurtles_misc_fops,
};

static int __init rurtles_init(void)
{
	int retval;

	retval = misc_register(&rurtles_misc_dev);

	if (retval) {
		pr_warn("[rurtle] Couldn't initialize miscdevice /dev/eudyptula.\n");
		return -ENODEV;
	}

	pr_info("[rurtle] Initialized device: /dev/eudyptula, node (MAJOR 10, MINOR %d).\n",
		rurtles_misc_dev.minor);
	return 0;
}

static void __exit rurtles_exit(void)
{
	misc_deregister(&rurtles_misc_dev);
	pr_info("[rurtle] Unregistered miscdevice /dev/eudyptual.\n");
}

module_init(rurtles_init);
module_exit(rurtles_exit);
