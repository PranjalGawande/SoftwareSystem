/*
============================================================================
Name : 20b.c
Author : Pranjal Gawande
Description : Write two programs so that both can communicate by FIFO-
              Use one way communication.
Date: 5 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	char buf[1024];
	char *fifoFile = "fifo_20";
      
	int fd = open(fifoFile, O_RDONLY);
	if (fd == -1) {
		perror("Error in opening the file");
		return 1;
	}

	ssize_t byteread = read(fd, &buf, sizeof(buf));
	if(byteread == -1) {
		perror ("Error in reading from fifo file");
		return 1;
	}

	printf("Message received: %s\n", buf);
	close(fd);

	return 0;
}
