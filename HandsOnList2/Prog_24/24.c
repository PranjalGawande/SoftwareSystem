/*
============================================================================
Name : 24.c
Author : Pranjal Gawande
Description : Write a program to create a message queue and print the key
	      and message queue id.
Date: 8 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
	key_t key;
	int msg_id;

	key = ftok(".", 24);
	if (key == -1) {
		perror ("Error in getting key");
		return 1;
	}

	msg_id = msgget(key, IPC_CREAT | 0766);
	if (msg_id == -1) {
		perror("Error in creating message queue");
		return 1;
	}

	printf("Message queue key: %d\n", key);
	printf("Message queue id: %d\n", msg_id);

	return 0;
}
