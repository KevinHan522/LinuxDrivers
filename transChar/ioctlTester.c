#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "trans_ioctl.h"


int main(int argc, char *argv[])
{
	char *file_name = argv[1];
	int fd = open(file_name, O_RDWR);
	if (fd == -1) {
		perror("Failed to open");
		return 2;
	}
	if (strcmp(argv[2], "-m") == 0) {
		if (ioctl(fd, TRANS_MODECHANGE)) perror("Failed to change mode");
	}
	if (strcmp(argv[2], "-c") == 0) {
		if (ioctl(fd, TRANS_CLEAR)) perror("Failed to clear buffer");
	}
	close(fd);
	return 0;
}