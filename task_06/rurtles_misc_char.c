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

static const struct file_operations rurtles_misc_fops = {
	.owner			= THIS_MODULE,
#if 0
	.open			= rurtles_misc_open,
	.read			= rurtles_misc_read,
	.write			= rurtles_misc_write,
	.close			= rurtles_misc_close,
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
		pr_err("[rurtle] Filed to register misc char driver");
		return retval;
	}
	/* Otherwise (misc device registered successfully) */
	pr_alert("[rurtle] misc char driver 'eudyptula' registered!\n");
	return 0;
}

static void __exit rurtles_exit(void)
{
	misc_deregister(&rurtles_misc_dev);
	pr_alert("[rurtle] Goodbye World. misc char driver deregistered\n");
}

module_init(rurtles_init);
module_exit(rurtles_exit);
