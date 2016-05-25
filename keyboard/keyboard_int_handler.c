#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");


static int keyboard_int_init(void);
static void keyboard_int_exit(void);
static irq_handler_t keyboard_intr_handler(int irq, void *dev_id, struct pt_regs *regs);

static irq_handler_t keyboard_intr_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	static unsigned char scancode = 0;
	scancode = inb(0x60);
	printk(KERN_INFO "Scancode of key pressed: %02X \n", scancode);
	return (irq_handler_t) IRQ_HANDLED;
}

/*module initialization*/
static int keyboard_int_init(void)
{
	int err = 0;
	//request IRQ 1 which is the keyboard interrupt line
	//has to be shared to keep old interrupt handler I assume
	//use location of method as unique identifier
	err = request_irq(1, (irq_handler_t) keyboard_intr_handler, IRQF_SHARED, "my_keyboard_intr", (void *) (keyboard_intr_handler));
	if (err) printk(KERN_INFO "Unable to request IRQ 1\n");
	return err;
}

/*module removal*/
static void keyboard_int_exit(void)
{
	//free using unique identifier so that correct interrupt handler is freed
	free_irq(1, (void *)(keyboard_intr_handler));
}

module_init(keyboard_int_init);
module_exit(keyboard_int_exit);