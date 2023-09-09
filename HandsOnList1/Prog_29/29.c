/*
==============================================================================
Name : 29.c
Author : Pranjal Gawande
Description : Write a program to get scheduling policy and modify the 
	      scheduling policy (SCHED_FIFO,SCHED_RR).
Date: 7th Sept, 2023.
==============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

int main() {
	pid_t pid = getpid();

	int policy = sched_getscheduler(pid);
	
	if (policy == -1) {
		perror("Error in getting scheduler\n");
		return 1;
	}

	printf("Current scheduling policy is: ");
	switch (policy) {
		case SCHED_FIFO:
			printf("SCHED_FIFO\n");
			break;
		case SCHED_RR:
			printf("SCHED_RR\n");
			break;
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
		default:
			printf("Unknown\n");
			break;
	}
	
	struct sched_param parameter;
	
	parameter.sched_priority = 50;

	printf("Enter the scheduling policy you want to change to: \n");
	printf("1. SCHED_FIFO\n");
	printf("2. SCHED_RR\n");
	int choice;

	scanf("%d", &choice);

	int set_schedule;
	switch(choice) {
		case 1:
			set_schedule = sched_setscheduler(pid, SCHED_FIFO, &parameter);
			if (set_schedule == -1) {
				perror("Error in setting the policy");
				return 1;
			}
			printf("Scheduling policy updated!!\n");
			break;
		case 2:
			set_schedule = sched_setscheduler(pid, SCHED_RR, &parameter);
                        if (set_schedule == -1) {
                                perror("Error in setting the policy");
                                return 1;
                        }
                        printf("Scheduling policy updated!!\n");
                        break;
		default:
			printf("Invalid option\n");
			break;
	}

	printf("Updated scheduling policy: ");

	int new_policy = sched_getscheduler(pid);

        if (new_policy == -1) {
                perror("Error in getting scheduler\n");
                return 1;
        }

        switch (new_policy) {
                case SCHED_FIFO:
                        printf("SCHED_FIFO\n");
                        break;
                case SCHED_RR:
                        printf("SCHED_RR\n");
                        break;
                case SCHED_OTHER:
                        printf("SCHED_OTHER\n");
                        break;
                default:
                        printf("Unknown\n");
                        break;
        }

	return 0;
}
