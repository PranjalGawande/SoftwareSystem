/*
==============================================================================
Name : 24.c
Author : Pranjal Gawande
Description : Write a program to create an orphan process.
Date: 5th Sept, 2023.
==============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	if (!fork()) {
		printf("Child process (%d) is running.\n", getpid());
		sleep(20);
		printf("Child process (%d) is exiting...\n", getpid());
		printf("Parent process id after parent is exited : %d\n", getppid());
	}
	else {
		printf("Parent process (%d) is exiting...\n", getpid());
		exit(EXIT_SUCCESS);
	}


	return 0;
}
