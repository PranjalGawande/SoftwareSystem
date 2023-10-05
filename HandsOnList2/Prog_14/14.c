/*
============================================================================
Name : 14.c
Author : Pranjal Gawande
Description : Write a simple program to create a pipe, write to the pipe, 
	      read from pipe and display on the monitor.
Date: 15 Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int fd[2];
	char buf1[80];
	char buf2[80];
	if(pipe(fd) == -1) {
		perror("Error in making a pipe");
		return 1;
	}
	
	ssize_t input = read (STDIN_FILENO, &buf1, sizeof(buf1));
	if (input == -1) {
		perror("Error in reading data");
		return 1;
	}
	buf1[input] = '\0';

	ssize_t pipeWrite = write (fd[1], &buf1, sizeof(buf1));
	if (pipeWrite == -1) {
		perror("Error in writing data to pipe");
		return 1;
	}

	close(fd[1]);

	ssize_t pipeRead = read (fd[0], &buf2, sizeof(buf2));
	if (pipeRead == -1) {
		perror ("Error in reading data from pipe");
		return 1;
	}
	buf2[pipeRead] = '\0';
	
	printf("Data from pipe : %s", buf2);
	
	close(fd[0]);
	
	return 0;
}
