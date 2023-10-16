/*
==================================================================================
Name : 31.c
Author : Pranjal Gawande
Description : Write a program to create a semaphore and initialize value to the
              semaphore.
              a. create a binary semaphore
              b. create a counting semaphore
Date: 16 Oct, 2023.
==================================================================================
*/

#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h> 

int main(){

    int binarySemId, countingSemId;
    int key;

    union semun{
        int val;
        struct semid_ds *buf;
        short *array;
    };
    union semun arg;

    key = ftok(".", 31);

    binarySemId = semget(key, 1, IPC_CREAT | 0777);
    arg.val = 1;

    int status = semctl(binarySemId, 0, SETVAL, arg);
    if(status == -1){
        perror ("Error in semctl");
    }
    else{
        printf("Binary semaphore has been created with ID: %d\n", binarySemId);
    }

    key = ftok(".", 31);

    countingSemId = semget(key, 1, IPC_CREAT | 0777);
    arg.val = 5;
    
    status = semctl(countingSemId, 0, SETVAL, arg);
    if(status == -1){
        perror ("Error in semctl");
    }
    else{
        printf("Counting semaphore has been created with ID: %d\n", countingSemId);
    }
    return 0;
}
