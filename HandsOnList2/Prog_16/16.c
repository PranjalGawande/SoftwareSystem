/*
============================================================================
Name : 16.c
Author : Pranjal Gawande
Description : Write a program to send and receive data from parent to child
	      vice versa. Use two way communication.
Date: 15 Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int fd1[2], fd2[2];
	char readbuf[1024], writebuf[1024];

	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		perror("Error in creating pipe");
		return 1;
	}

	if (fork()) {
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], &readbuf, sizeof(readbuf));
		printf("Message from the child: %s\n", readbuf);
		printf("Parent: Enter a message for child: ");
        	scanf(" %[^\n]", writebuf);
        	write(fd2[1], &writebuf, sizeof(writebuf));
	}
	else {
		close(fd1[0]);
		close(fd2[1]);
		printf("Child: Enter a message for parent: ");
		scanf("%[^\n]", writebuf);
		write(fd1[1], &writebuf, sizeof(writebuf));
		read(fd2[0], &readbuf, sizeof(readbuf));
		printf("Message from the parent: %s\n", readbuf);
	}

	return 0;
}
