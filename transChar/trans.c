#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/spinlock.h>

#define BUFFER_SIZE 40

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Device Driver");
MODULE_AUTHOR("Kevin Han");



struct trans_dev {
	int pos;
	rwlock_t dev_lock;
	char buffer[BUFFER_SIZE];
	struct cdev cdev;
};

static ssize_t trans_read(struct file *filp, char * buff, size_t len, loff_t *off);
static int trans_open(struct inode *inod, struct file *fil);
static ssize_t trans_write(struct file *filp, const char *buff, size_t len, loff_t *off);
static int trans_release(struct inode *nod, struct file *fil) ;
static int trans_open_proc(struct inode *inode, struct file *file) ;
static int trans_show_proc(struct seq_file *seq, void *v);

static struct file_operations fops =
{
	.read = trans_read,
	.open = trans_open,
	.write = trans_write,
	.release = trans_release,
};

static const struct file_operations s_fops =
{
	.owner = THIS_MODULE,
	.open = trans_open_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static struct trans_dev tdev;
static dev_t dev_num;
static int times;

static void trans_setup_cdev(struct trans_dev * dev) 
{
	int err = 0;
	int i = 0;
	printk(KERN_ALERT "Major Number: %d\n", MAJOR(dev_num));
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		dev->buffer[i] = 0;
	}
	rwlock_init(&(dev->dev_lock));
	cdev_init(&(dev->cdev), &fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &fops;
	err = cdev_add(&(dev->cdev), dev_num, 1);
	printk(KERN_ALERT "Current error status: %d", err);
}


static int trans_init(void)
{
	int err;
	
	//acquire major number for device
	err  = alloc_chrdev_region(&dev_num,0,1,"trans");
	if (err < 0) {
		printk(KERN_ALERT "No available major numbers\n");
		return err;
	}

	//create proc entry
	if (!proc_create("transInfo", 0, NULL, &s_fops)) {
		return -ENOMEM;
	}

	//initialize dev structure
	trans_setup_cdev(&tdev);
	return err;
}
static void trans_exit(void)
{
	cdev_del(&(tdev.cdev));
	remove_proc_entry("transInfo", NULL);
	unregister_chrdev_region(dev_num, 1);
}	

static int trans_open(struct inode *inod, struct file *filp)
{
	static struct trans_dev *dev;
	dev = container_of(inod->i_cdev, struct trans_dev, cdev);
	filp->private_data = dev;
	times++;
	//printk(KERN_ALERT "Device file opened %d times\n", times);
	return 0;
}

static ssize_t trans_read(struct file *filp, char * buff, size_t len, loff_t *off)
{	
	int to_return = 0;
	if (*off >= BUFFER_SIZE) return 0;
	struct trans_dev *dev = (struct trans_dev*) filp->private_data;
	if (len > BUFFER_SIZE) len = BUFFER_SIZE;
	to_return = len;
	read_lock(&(dev->dev_lock));
	if (copy_to_user(buff, dev->buffer, len)) {
		to_return = -EFAULT;
	}
	(*off) += len;	
	read_unlock(&(dev->dev_lock));
	return to_return;
}

static ssize_t trans_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	int to_return = 0;
	char x = 0;
	struct trans_dev *dev = (struct trans_dev*) filp->private_data;
	short i = 0;
	write_lock(&(dev->dev_lock));
	while(len > 0)
	{
		if (dev->pos  >=  BUFFER_SIZE) dev->pos = 0;
		if (*off >= BUFFER_SIZE) *off = 0;
		if (get_user(x, buff + i)) {
			to_return = -EFAULT;
			goto out;
		}
		if (x >= 'a' && x <= 'z') x -= 32;
		dev->buffer[dev->pos] = x;
		len--;
		i++;
		(*off)++;
		dev->pos++;
		to_return++;
	}

	out:
	write_unlock(&(dev->dev_lock));
	return to_return;
}

static int trans_release(struct inode *nod, struct file *fil) 
{
	printk(KERN_ALERT "Device closed\n");
	return 0;
}

static int trans_open_proc(struct inode *inode, struct file *file) 
{
	return single_open(file, trans_show_proc, NULL);
}

static int trans_show_proc(struct seq_file *seq, void *v)
{
	seq_printf(seq, "This device has been opened %d times and holds %d bytes.\n", times, BUFFER_SIZE);
	return 0;
}

module_init(trans_init);
module_exit(trans_exit);
