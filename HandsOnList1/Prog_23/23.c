/*
==============================================================================
Name : 23.c
Author : Pranjal Gawande
Description : Write a program to create a Zombie state of the running program.
Date: 2nd Sept, 2023.
==============================================================================
*/

#include <stdio.h>	
#include <stdlib.h>
#include <unistd.h>

int main() {
	if (!fork()) {
		printf("Child Process is exiting...\n");
		exit(EXIT_SUCCESS);
	}
	else {
		sleep(30);        // Using ps aux | grep Z+ to check zombie process or using top command
		printf("Parent process is not waiting.\n");
	}
	

	return 0;
}
