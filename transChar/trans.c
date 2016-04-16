#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Device Driver Demo");
MODULE_AUTHOR("Kevin Han");

static dev_t dev_num;
/*
static struct file_operations fops =
{
	.read = dev_read,
	.open = dev_open,
	.write = dev_write,
	.release = dev_release,
}*/

static int trans_init(void)
{
	int t;
	
	//acquire major number for device
	t = alloc_chrdev_region(&dev_num,0,1,"trans");
	if (t < 0)
	{
		printk(KERN_ALERT "No available major numbers\n");
		return t;
	}

	//initialize dev structure
	//cdev_init(cdev, &fops);
	//cdev->owner = THIS_MODULE;
	//int t = cdev_add(cdev, major);
	return t;
}

static void trans_exit(void)
{
	unregister_chrdev_region(dev_num, 1);
}	


module_init(trans_init);
module_exit(trans_exit);
