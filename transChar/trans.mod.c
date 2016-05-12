#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x53a8e63d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6083a62f, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x54ffe6c6, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x95b52f82, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xc03fdabc, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x6a61864b, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x2eca246, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xf5a2fc7c, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xd755a45, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0xfac2a257, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x8d108923, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x73a11961, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x41425107, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0x167e7f9d, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0xd96ec02b, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x91831d70, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x65a06ea7, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6D83F722F5EF55BC3AFA4DD");
