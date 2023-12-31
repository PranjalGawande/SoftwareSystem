/*
==================================================================================
Name : 33_server.c
Author : Pranjal Gawande
Description : Write a program to communicate between two machines using socket.
Date: 16 Oct, 2023.
==================================================================================
*/

#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>      
#include <unistd.h>

void main(){
    int socketFileDescriptor, connectionFileDescriptor;  
    int bindStatus; 
    int listenStatus; 
    int clientSize;

    struct sockaddr_in address, client;

    ssize_t readBytes, writeBytes;
    char dataFromClient[100];
    char dataToClient[100];

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Error while creating socket!");
        _exit(0);
    }

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    bindStatus = bind(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (bindStatus == -1)
    {
        perror("Error while binding name to socket!");
        _exit(0);
    }

    listenStatus = listen(socketFileDescriptor, 2);
    if (listenStatus == -1)
    {
        perror("Error while trying to listen for connections!");
        _exit(0);
    }
    printf("Now listening for connections on a socket!\n");

    clientSize = (int)sizeof(client);
    connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&client, &clientSize);
    if (connectionFileDescriptor == -1)
        perror("Error while accepting a connection!");
    else
    {
        readBytes = read(connectionFileDescriptor, dataFromClient, 100);
        if (readBytes == -1)
            perror("Error while reading from network via socket!");
        else
            printf("%s\n", dataFromClient);
        
        printf("Enter message to client:\n");
        scanf("%[^\n]s",dataToClient);
        writeBytes = write(connectionFileDescriptor,dataToClient,sizeof(dataToClient));
        if (writeBytes == -1)
            perror("Error while writing to network via socket!");
    }

    close(connectionFileDescriptor);
    close(socketFileDescriptor);
}