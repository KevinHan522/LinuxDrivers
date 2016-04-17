#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Device Driver Demo");
MODULE_AUTHOR("Kevin Han");



static struct trans_dev {
	int pos;
	struct cdev cdev;
};

static ssize_t trans_read(struct file *filp, char * buff, size_t len, loff_t *off);
static int trans_open(struct inode *inod, struct file *fil);
static ssize_t trans_write(struct file *filp, const char *buff, size_t len, loff_t *off);
static int trans_release(struct inode *nod, struct file *fil) ;

static struct file_operations fops =
{
	.read = trans_read,
	.open = trans_open,
	.write = trans_write,
	.release = trans_release,
};

static struct trans_dev tdev;
static dev_t dev_num;

static void trans_setup_cdev(struct trans_dev * dev, int index) 
{
	int err = 0;
	int devno = MKDEV(dev_num, index);
	cdev_init(&(dev->cdev), &fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &fops;
	err = cdev_add(&(dev->cdev), devno, 1);
}


static int trans_init(void)
{
	int err;
	
	//acquire major number for device
	err  = alloc_chrdev_region(&dev_num,0,1,"trans");
	if (err < 0)
	{
		printk(KERN_ALERT "No available major numbers\n");
		return err;
	}

	//initialize dev structure
	trans_setup_cdev(&tdev, 0);
	return err;
}
static void trans_exit(void)
{
	cdev_del(&(tdev.cdev));
	unregister_chrdev_region(dev_num, 1);
}	

static int trans_open(struct inode *inod, struct file *fil)
{
	return 0;
}

static ssize_t trans_read(struct file *filp, char * buff, size_t len, loff_t *off)
{
	return 0;
}

static ssize_t trans_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	return 0;
}

static int trans_release(struct inode *nod, struct file *fil) 
{
	return 0;
}

module_init(trans_init);
module_exit(trans_exit);
