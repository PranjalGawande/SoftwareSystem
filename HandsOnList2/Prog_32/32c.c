/*
===========================================================================================
Name : 32c.c
Author : Pranjal Gawande
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
              b. protect shared memory from concurrent write access
              c. protect multiple pseudo resources ( may be two) using counting semaphore
              d. remove the created semaphore
Date: 16 Oct, 2023.
============================================================================================
*/


#include <sys/ipc.h>  
#include <sys/sem.h>  
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>    

void main()
{
    char *filename = "./sample.txt"; 

    int fileDescriptor;           
    ssize_t readBytes; 
    off_t lseekOffset;
    char data[1000]; 

    key_t semKey;      // Semaphore Key
    int semIdentifier; // Semaphore Identifier
    int semctlStatus;  
    int semopStatus;   

    fileDescriptor = open(filename, O_CREAT | O_RDONLY , 0744);
    if (fileDescriptor == -1)
    {
        perror("Error while creating / opening the ticket file!");
        _exit(0);
    }

    union semun
    {
        int val;               
    } semSet;

    semKey = ftok(".", 32);
    if (semKey == -1)
    {
        perror("Error while computing key!");
        _exit(1);
    }

    semIdentifier = semget(semKey, 1, 0); 
    if (semIdentifier == -1)
    {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); 
        if (semIdentifier == -1)
        {
            perror("Error while creating semaphore!");
            _exit(1);
        }

        semSet.val = 2; 
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("Press enter to obtain lock for the critical section!\n");
    getchar();


    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    printf("Obtained lock on critical section!");

    printf("Now entering critical section!");

    // Start of Critical Section 

    readBytes = read(fileDescriptor, &data, 1000);
    if (readBytes == -1)
    {
        perror("Error while reading from sample file!");
        _exit(0);
    }
    else if (readBytes == 0) // Sample file has no data
        printf("No data exists!\n");
    else
        printf("Sample data: \n %s", data);

    printf("\n\nPress enter key to exit critical section!\n");
    getchar();

    // End of Critical Section 

    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    close(fileDescriptor);
}