/*
============================================================================
Name : 22a.c
Author : Pranjal Gawande
Description : Write a program to wait for data to be written into FIFO
              within 10 seconds, use select system call with FIFO.
Date: 7 Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/stat.h>
#include<sys/time.h>

int main() {
    char *fifoFile = "fifo_22";
    char buff[1024];
  
    int fd = open(fifoFile, O_NONBLOCK | O_RDONLY, 0766);
    if(fd==-1){
        printf("Error in opening fifo file\n");
        return 1;
    }
  
    fd_set rfds;  
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec=0;
  
    int status = select(fd+1,&rfds,NULL, NULL,&tv);
    if(status == -1) {
        printf("Error in select");
        return 1;
    }    
    if(status == 0) {
        printf("No data available within 10 seconds\n");
    }
    else {
        printf("Data is available now\n");
        int fd_read = read(fd, buff, sizeof(buff));
        if(fd_read==-1){
            perror("Error in reading the data from fifo file");
            close(fd);
            return 1;
        }
        printf("%s\n", buff);
    }
    close(fd);
    return 0;
}