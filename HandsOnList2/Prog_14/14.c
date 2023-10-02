/*
=============================================================================================
Name : 15.c
Author : Pranjal Gawande
Description : Write a simple program to send some data from parent to the child process.
Date: 15th Sept, 2023.
=============================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int fd[2];
	pipe (fd);
	char buf[1024];
	if (fork()) {
		close(fd[1]);
		ssize_t fd_read = read(fd[0], &buf, sizeof(buf));
		if (fd_read == -1) {
			perror("Error in reading from pipe");
			return 1;
		}
		printf("%s", buf);
		printf("\n");
		close(fd[0]);
	}
	else {
		close(fd[0]);
		scanf("%[^\n]", buf);
		ssize_t fd_write = write(fd[1], &buf, sizeof(buf));
		if (fd_write == -1) {
			perror("Error in writing from pipe");
			return 1;
		}
		close(fd[1]);
		
	}


	return 0;
}
