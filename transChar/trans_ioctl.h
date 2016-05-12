#ifndef TRANS_IOCTL_H
#define TRANS_IOCTL_H

#include <linux/ioctl.h>
#define TRANS_MAGIC_NUM ']'
#define TRANS_MAX_NR 2

#define TRANS_CLEAR _IO(TRANS_MAGIC_NUM, 0)
#define TRANS_MODECHANGE _IO(TRANS_MAGIC_NUM, 1)

#endif