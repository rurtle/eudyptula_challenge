// SPDX-License-Identifier: GPL-3.0+
// Author: Subhra Sankha Sarkar <rurtle.coder@gmail.com>

/*
 * @brief	Task 05 - Write a Linux kernel module
 */
#include <linux/init.h>
#include <linux/module.h>				/* Needed by all modules */
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/usb/storage.h>


#if 0
static const struct usb_device_id usb_kbd_id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{ }						/* Terminating entry */
};
#endif

static const struct usb_device_id usb_kbd_id_table[] = {
	{
		USB_INTERFACE_INFO(
			USB_CLASS_MASS_STORAGE,
			USB_SC_SCSI,
			USB_PR_UAS
			)
	},
	{ }						/* Terminating entry */
};

static int rurtles_usb_kbd_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	pr_alert("[rurtle] Connected Sandisk 16GB USB stick");
	return 0;
}

static void rurtles_usb_kbd_disconnect(struct usb_interface *intf)
{
	// pr_alert("Disconnected USB keyboard\n");
	pr_alert("[rurtle] Disconnected Sandisk USB mass storage\n");
}

static struct usb_driver rurtles_usb_driver = {
	.name = "rurtlesusbstick",
	.probe = rurtles_usb_kbd_probe,
	.disconnect = rurtles_usb_kbd_disconnect,
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
MODULE_DESCRIPTION("Test module to check USB mass storage hotplugging");
MODULE_VERSION("0.01");
