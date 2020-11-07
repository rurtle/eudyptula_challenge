// SPDX-License-Identifier: GPL-3.0+
//
// Author: Subhra Sankha Sarkar <rurtle.coder@gmail.com>

/*
 * @brief	Task 01 - Write a Linux kernel module
 */
#include <linux/init.h>
#include <linux/module.h>				/* Needed by all modules */
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rurtle");
MODULE_DESCRIPTION("First kernel module in a long while - since 3.14 days");
MODULE_VERSION("0.01");

static int __init lkml_example_start(void)
{
	pr_alert("Hello World!\n");
	return 0;
}

static void __exit lkml_example_end(void)
{
	pr_alert("Goodbye World.\n");
}

module_init(lkml_example_start);
module_exit(lkml_example_end);
