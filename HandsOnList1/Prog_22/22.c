/*
=============================================================================
Name : 22.c
Author : Pranjal Gawande
Description : Write a program, open a file, call fork, and then write to the 
	      file by both the child as well as the
Date: 2nd Sept, 2023.
=============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Please pass one file\n");
		return 0;
	}

	int fd = open(argv[1], O_RDWR | O_CREAT, 0744);

	if (fd == -1) {
		perror("Error in opening in file\n");
		return 1;
	}

	if (!fork()) {
		char* child_msg = "This is written by child process.\n";
		write(fd, child_msg, strlen(child_msg));
	}
	else {
		char* parent_msg = "This is written by parent process.\n";
		write(fd, parent_msg, strlen(parent_msg));
	}
	
	printf("Written on file successfully\n");

	int fd_close = close(fd);
	if (fd_close == -1) {
		perror("Error in closing the file\n");
		return 1;
	}

	return 0;
}
