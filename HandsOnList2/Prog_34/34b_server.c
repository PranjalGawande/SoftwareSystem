/*
==================================================================================
Name : 34b_server.c
Author : Pranjal Gawande
Description : Write a program to create a concurrent server.
              a. use fork
              b. use pthread_create
Date: 16 Oct, 2023.
==================================================================================
*/

// Server Side Program using pthread

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h> 
#include <string.h>
#include <pthread.h>

void communicate (int *fd) 
{
    char buff[100];

    size_t write_size = send (*fd, "I am server.", 12, 0 );
    if (-1 == write_size)
        perror ("Error while writing to network via socket");
    else 
        printf ("Data sent successfully.\n");

    size_t read_size = recv (*fd, buff, sizeof(buff), 0);
    if ( -1 == read_size )
        perror ("Error while reading from network via socket");
    else 
        printf ("Client : %s\n", buff);

    close (*fd);
}

int main () {
    int fd, client_fd;

    struct sockaddr_in address, client;
    pthread_t thread;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( -1 == fd ) {
        perror ("Unable to create socket");
        return -1;
    }

    printf ("Server Side Socket Created...\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    if ( -1 == bind (fd, (struct sockaddr *) &address, sizeof(address))) {
        perror ("Error while binding name to socket");
        return -1;
    }

    printf ("Binding to socket is successful\n");

    if ( -1 == listen(fd, 2)) {
        perror ("Error while trying to listen for connection");
        return -1;
    }

    printf ("Now listening for connection on socket\n");

    while (1) {

        int clientSize = (int) sizeof(client);
        client_fd = accept(fd, (struct sockaddr *) &client, &clientSize);
        if ( -1 == client_fd )
            perror ("Error while accepting connection");
        else {
                if ( pthread_create( &thread, NULL, (void *) communicate, (void *) &client_fd) ) {
                    perror ("Error while creating thread");
                }
            }
        }
    
    return 0;
}