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

#define	MY_ID		"xxxxxxxxxxxx"
#define	ID_LEN		sizeof(MY_ID)
#define	TEXT_MSG	"eudyptula challenge - task 06 - write successful!"

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

static ssize_t rurtles_misc_write(struct file *fp,
		const char __user *buf,
		size_t nbytes, loff_t *ppos)
{
	int ret;
	char my_id[ID_LEN];

	memset(my_id, 0, sizeof(my_id));
	ret = simple_write_to_buffer(my_id, sizeof(my_id) - 1, ppos,
			buf, nbytes);
	if (ret < 0) {
		ret = -EFAULT;
		pr_err("We don't know what went wrong.");
	} else {
		if (strncmp(my_id, MY_ID, strlen(my_id)) != 0) {
			pr_err("Written string doesn't match ID.");
			ret = -EINVAL;
		} else {
			pr_info("%s", TEXT_MSG);
			ret = (ID_LEN - 1);
		}
	}

	return ret;
}

static const struct file_operations rurtles_misc_fops = {
	.owner			= THIS_MODULE,
	.read			= rurtles_misc_read,
	.open			= rurtles_misc_open,
	.release		= rurtles_misc_release,
	.write			= rurtles_misc_write,
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
		pr_warn("[rurtle] Couldn't initialize miscdevice /dev/eudyptula.");
		return -ENODEV;
	}

	pr_info("[rurtle] Initialized device: /dev/eudyptula, node (MAJOR 10, MINOR %d).",
		rurtles_misc_dev.minor);
	return 0;
}

static void __exit rurtles_exit(void)
{
	misc_deregister(&rurtles_misc_dev);
	pr_info("[rurtle] Unregistered miscdevice /dev/eudyptula.");
}

module_init(rurtles_init);
module_exit(rurtles_exit);
