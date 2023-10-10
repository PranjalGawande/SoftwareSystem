/*
============================================================================
Name : 23.c
Author : Pranjal Gawande
Description : Write a program to print the maximum number of files can be
	      opened within a process and size of a pipe (circular buffer).
Date: 6 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
	char *fifoFile = "fifo_23";
	int status;
	long long max_files;
	long long pipe_size;

	status = mkfifo(fifoFile, 0777);
	
	if (!(errno == EEXIST || status != -1)) {
		perror ("Error in creating fifo file");
		return 1;
	}
	
	max_files = sysconf(_SC_OPEN_MAX);
	if (max_files == -1) {
		perror ("Error in getting max files");
		return 1;
	}
	
	printf("Maximum number of files can be opened within a process is: %lld\n", max_files);

	pipe_size = pathconf(fifoFile, _PC_PIPE_BUF);
	if (pipe_size == -1) {
		perror ("Error in getting pipe size");
		return 1;
	}

	printf("Size of a pipe fifo_23 is: %lld\n", pipe_size);

	return 0;
}
