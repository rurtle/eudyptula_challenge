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

static const struct file_operations rurtles_misc_fops = {
	.owner			= THIS_MODULE,
	.open			= rurtles_misc_open,
	.release		= rurtles_misc_release,
#if 0
	.read			= rurtles_misc_read,
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
	/* Otherwise (misc device registered successfully) */
	pr_info("[rurtle] Initialized device: /dev/eudyptula, node (MAJOR 10, MINOR %d).\n",
		rurtles_misc_dev.minor);
	return 0;
}

static void __exit rurtles_exit(void)
{
	misc_deregister(&rurtles_misc_dev);
	pr_alert("[rurtle] Unregistered miscdevice /dev/eudyptual. Goodbye World!\n");
}

module_init(rurtles_init);
module_exit(rurtles_exit);
