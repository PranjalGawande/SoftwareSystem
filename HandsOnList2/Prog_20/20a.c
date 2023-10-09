/*
============================================================================
Name : 20a.c
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
	char buf[] = "Communicating via FIFO";
	char *fifoFile = "fifo_20";

	if(mkfifo(fifoFile, 0766) == -1) {
		perror("Error in creating fifo file");
		return 1;
	}

	int fd = open(fifoFile, O_WRONLY);
	if(fd == -1) {
		perror("Error in opening the fifo file");
		return 1;
	}

	ssize_t bytewrite = write(fd, &buf, sizeof(buf));
       	if (bytewrite == -1) {
		perror("Error in writing into the fifo file");
		return 1;
	}

	close(fd);	

	return 0; 
}
