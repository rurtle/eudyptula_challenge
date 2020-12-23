// SPDX-License-Identifier: GPL-3.0+
// Author: Subhra Sankha Sarkar <rurtle.coder@gmail.com>

/*
 * @brief	Task 06 - Write a misc char device driver
 */
#include <linux/init.h>
#include <linux/module.h>				/* Needed by all modules */
#include <linux/kernel.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rurtle");
MODULE_DESCRIPTION("Eudyptual Challenge - Task 06 - misc char driver");
MODULE_VERSION("0.01");

static struct miscdevice rurtles_misc_dev;

static int __init rurtles_start(void)
{
	int retval;

	rurtles_misc_dev.minor = MISC_DYNAMIC_MINOR;
	rurtles_misc_dev.name = "eudyptula";
	rurtles_misc_dev.fops = &rurtles_misc_fops;
	retval = misc_register(&rurtles_misc_dev);

	if (retval) {
		pr_alert("[rurtle] Filed to register misc char driver");
	}

	pr_debug("[rurtle] misc char driver 'eudyptula' registered!\n");
	return 0;
}

static void __exit rurtles_end(void)
{
	misc_deregister(&rurtles_misc_dev);
	pr_alert("[rurtle] Goodbye World. misc char driver deregistered\n");
}

module_init(rurtles_start);
module_exit(rurtles_end);
