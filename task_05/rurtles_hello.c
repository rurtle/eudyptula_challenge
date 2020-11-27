// SPDX-License-Identifier: GPL-3.0+
// Author: Subhra Sankha Sarkar <rurtle.coder@gmail.com>

/*
 * @brief	Task 05 - Write a Linux kernel module which gets loaded when a
 * 		wireless USB keyboard is plugged in
 */
#include <linux/init.h>
#include <linux/module.h>				/* Needed by all modules */
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/hid.h>


static const struct usb_device_id usb_kbd_id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{ }						/* Terminating entry */
};

static struct usb_driver rurtles_usb_driver = {
	.name = "rurtlesusbwlkbd",
	.id_table = usb_kbd_id_table,
};

static int __init rurtles_start(void)
{
	pr_alert("[rurtle] Hello World!\n");
	return usb_register(&rurtles_usb_driver);
}

static void __exit rurtles_end(void)
{
	pr_alert("[rurtle] Goodbye World.\n");
	usb_deregister(&rurtles_usb_driver);
}

module_init(rurtles_start);
module_exit(rurtles_end);

MODULE_DEVICE_TABLE(usb, usb_kbd_id_table);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("rurtle");
MODULE_DESCRIPTION("Test module for checking USB wireless keyboard hotplugging");
MODULE_VERSION("0.01");
