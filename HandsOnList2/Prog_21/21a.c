/*
============================================================================
Name : 21a.c
Author : Pranjal Gawande
Description : Write two programs so that both can communicate by FIFO-
	      Use two way communication.
Date: 5 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd;    
    char * myfifo = "fifoFile";
    char buf[1024];
    mkfifo(myfifo, 0777);
    
    while (1)
    {   fd = open(myfifo, O_WRONLY);
        if(fd == -1){
            perror("Error in opening fifo file");
            return 1;
        }             
        
        printf("Enter a message or type 'exit' to close connection: ");
        fgets(buf, 1024, stdin);
        
        if(strcmp(buf,"exit\n") == 0) {    
            unlink(myfifo);
            close(fd);
            exit(0);
        }
        write(fd, buf, sizeof(buf));
        close(fd);

        fd = open(myfifo,O_RDONLY);
        if(fd == -1){
            perror("Error in opening fifo file");
            return 1;
        }
        
        ssize_t byteread = read(fd, buf, sizeof(buf));
        if(byteread == -1) {
            perror("Error in reading from file");
            return 1;
        }
        
        printf("Program 2 : %s\n", buf);
        close(fd);
                
    }
    
    return 0;
}
