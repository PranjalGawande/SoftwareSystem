/*
============================================================================
Name : 18.c
Author : Pranjal Gawande
Description : Write a program to find out total number of directories on
	      the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 5 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
	int fd1[2], fd2[2];
	
	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		perror ("Error in creating pipe");
		return 1;
	}
	
	if (!fork()) {
		close(fd2[1]);
		close(fd1[0]);
		close(fd1[1]);
		close(STDIN_FILENO);

		dup2(fd2[0], STDIN_FILENO);
	
		execl("/usr/bin/wc", "wc", NULL);
	}
	else {
		if (!fork()) {
			close(fd1[1]);
			close(fd2[0]);
			close(STDIN_FILENO);

			dup2(fd1[0], STDIN_FILENO);
			close(STDOUT_FILENO);	
			
			dup2(fd2[1], STDOUT_FILENO);
			
			execl("/usr/bin/grep", "grep ^d", "^d", NULL);
		}
		else {
			close(fd1[0]);
			close(fd2[0]);
			close(fd2[1]);
			close(STDOUT_FILENO);

			dup2(fd1[1], STDOUT_FILENO);
			
			execl("/usr/bin/ls", "ls -l", "-l", NULL);
		}
	}


	return 0;
}
