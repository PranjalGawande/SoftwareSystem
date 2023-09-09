/*
==============================================================================
Name : 25.c
Author : Pranjal Gawande
Description : Write a program to create three child processes. 
	      The parent should wait for a particular child 
	      (use waitpid system call).
Date: 6th Sept, 2023.
==============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pids[3];

    for (int i = 0; i < 3; i++) {
        child_pids[i] = fork();

        if (child_pids[i] == -1) {
            perror("Error in for fork call");
            return 1;
        }

        if (child_pids[i] == 0) {
            printf("Child %d (%d) is running.\n", i+1, getpid());
            sleep(2*(i+1)); 
            printf("Child %d (%d) is exiting.\n", i+1, getpid());
            exit(i+1); 
        }
    }

    printf("Parent process (%d) is waiting for Child 3 to terminate.\n", getpid());

    pid_t wait;

    wait = waitpid(child_pids[2], WIFEXITED(3), 0);

    if (wait == -1) {
        perror("Error in waitpid");
        return 1;
    }

    printf("Parent process (%d) is exiting.\n", getpid());

    return 0;
}

