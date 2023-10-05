/*
============================================================================
Name : 15.c
Author : Pranjal Gawande
Description : Write a simple program to send some data from parent to the 
	      child process.
Date: 15 Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char buf2[1024];
	char buf[1024];
	int fd[2];
	
	if (pipe(fd) == -1) {
		perror("Error in creating pipe");
		return 1;
	}

	if (fork()) {
		close(fd[0]);

		printf("Enter a message for the child: ");
		scanf("%[^\n]", buf);
	       	ssize_t writefd = write (fd[1], &buf, sizeof(buf));
		if (writefd == -1) {
			perror("Error in writing in pipe");
			return 1;
		}
	}
	else {
		close(fd[1]);

		ssize_t readpipe = read(fd[0], &buf2, sizeof(buf2));
		if (readpipe == -1) {
			perror("Error in reading from pipe");
			return 1;
		}
		printf("Message for child by parent: %s\n",buf2);
	}

	return 0;
}
