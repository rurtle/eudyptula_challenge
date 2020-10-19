/*
 * @brief	lkml_example simple kernel module
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
	printk(KERN_ALERT "Hello World!\n");
	return 0;
}

static void __exit lkml_example_end(void)
{
	printk(KERN_ALERT "Goodbye World.\n");
}

module_init(lkml_example_start);
module_exit(lkml_example_end);
