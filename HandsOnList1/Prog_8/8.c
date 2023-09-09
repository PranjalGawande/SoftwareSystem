/*
==============================================================================================
Name : 8.c
Author : Pranjal Gawande
Description : Write a program to open a file in read only mode, read line by line and display
              each line as it is read. Close the file when end of file is reached.
Date: 18th Aug, 2023.
==============================================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd;
	char buf;
	ssize_t byteread;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("You are useless");
		return 1;
	}
	
	int i = 0;
	char temp[1024];

	while((byteread = read(fd, &buf, 1)) > 0) {
		
		if(buf != '\n' && i < 1024) {
			temp[i++] = buf;
		}
		else {
			temp[i] = '\n';
			write(STDOUT_FILENO, &temp, i+1);
			i = 0;
			memset(temp, '\0', sizeof(temp));
		}
	}

	if (byteread == -1) {
		perror("Error Reading the file");
		return 1;
	}

	close(fd);
	return 0;
}
