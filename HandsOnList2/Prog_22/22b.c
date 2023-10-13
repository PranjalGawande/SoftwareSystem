/*
============================================================================
Name : 22b.c
Author : Pranjal Gawande
Description : Write a program to wait for data to be written into FIFO
              within 10 seconds, use select system call with FIFO.
Date: 7 Oct, 2023.
============================================================================
*/

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/time.h>  
#include <unistd.h>    
#include <stdio.h>     

int main()
{
    char *fifoFile = "fifo_22";
    int fd, writeBytes;

    fd = open(fifoFile, O_NONBLOCK | O_WRONLY, 0766);
    if (fd == -1)
    {
        perror("Error in opening FIFO file");
        return 1;
    }

    writeBytes = write(fd, "Data written: This is written to fifo file within 10 sec", 56);
    if (writeBytes == -1) {
        perror("Error while writing to FIFO!");
        return 1;
    }

    close(fd);
    return 0;
}