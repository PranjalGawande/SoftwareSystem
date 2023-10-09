/*
============================================================================
Name : 19.c
Author : Pranjal Gawande
Description : Create a FIFO file by
	      a. mknod command
	      b. mkfifo command
      	      c. use strace command to find out, which command 
	      	 (mknod or mkfifo) is better.
	      c. mknod system call
	      d. mkfifo library function
Date: 5 Oct, 2023.
============================================================================
*/

// a. using mknod fifo_a p -> to make fifo file using mknod command
// b. using mkfifo fifo_b -> to make fifo file using mkfifo command
// c. strace -c mknod fifo_c1 p & strace -c mkfifo fifo_c2

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int isfifo = mknod("fifo_d", S_IFIFO | 0777, 0);
	if(isfifo == -1) {
		perror("Error in creation fifo file using mknod");
		return 1;
	}

	printf("fifo_d file successfully created using mknod system call.\n");

	isfifo = mkfifo("fifo_e", 0777);
	if(isfifo == -1) {
		perror("Error in creating fifo file using mkfifo");
		return 1;
	}

	printf("fifo_e file successfully created using mkfifo system call.\n");

	return 0;
}
