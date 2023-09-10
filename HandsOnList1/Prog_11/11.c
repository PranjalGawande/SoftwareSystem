/*
================================================================================================
Name : 11.c
Author : Pranjal Gawande
Description : Write a program to open a file, duplicate the file descriptor and append the file
              with both the descriptors and check whether the file is updated properly or not.
              a. use dup
              b. use dup2
              c. use fcntl
Date: 24th Aug, 2023.
================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <string.h>

int main()
{
	int fd1, fd2, fd4;
	fd1=open("my_file.txt",O_RDWR | O_CREAT, 0766);
	if (fd1 == -1) {
		perror ("Error");
		return 1;
	}
	char data[100] = "Written by fd1 \n";
	write(fd1, data, strlen(data));

	fd2=dup(fd1);
	if (fd2 == -1) {
                perror ("Error");
                return 1;
        }
        char data2[100] = "Written by fd2 using dup \n";
        write(fd2, data2, strlen(data2));

	int fd_dup = dup2(fd1,10);
	if (fd_dup == -1) {
	    perror("Error");
	    return 1;
	}
	char data3[100] = "Written by fd_dup using dup2 \n";
        write(fd_dup, data3, strlen(data3));

	int fd3 = fcntl(fd1, F_DUPFD, 0);
	if (fd3 == -1) {
            perror("Error");
            return 1;
        }
        char data4[100] = "Written by fd3 using fcntl \n";
        write(fd3, data4, strlen(data4));

	printf("fd1 = %d \nfd2 = %d \nfd_dup = %d\nfd3 = %d\n", fd1, fd2, fd_dup, fd3);
	getchar();
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd_dup);
        return 0;
}	
