/*
============================================================================
Name : 17b.c
Author : Pranjal Gawande
Description : Write a program to execute ls -l | wc.
	      a. use dup
	      b. use dup2
	      c. use fcntl
Date: 5 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int fd[2];
	
	if(pipe(fd) == -1) {
		perror("Error in creating pipe");
		return 1;
	}

	if(!fork()) {
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execl("/usr/bin/wc", "wc", NULL);
	}
	else {
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	        close(fd[0]);
       		execl("/usr/bin/ls", "ls -l", "-l", NULL);
	}		


	return 0;
}
