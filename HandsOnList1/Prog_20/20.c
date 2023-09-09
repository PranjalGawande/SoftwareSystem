/*
=============================================================================
Name : 20.c
Author : Pranjal Gawande
Description : Find out the priority of your running program.
	      Modify the priority with nice command.
Date: 1st Sept, 2023.
=============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
	pid_t pid  = getpid();
	int priority = getpriority(PRIO_PROCESS, pid);
	
	// Using renice <priority> -p <pid> to change priority and checking on top command

	printf("Priority of the process is: %d\n", priority);       
	getchar();
	while(1);

	return 0;
}
