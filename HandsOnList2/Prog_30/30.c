/*
==================================================================================
Name : 30.c
Author : Pranjal Gawande
Description : Write a program to create a shared memory.
              a. write some data to the shared memory
              b. attach with O_RDONLY and check whether you are able to overwrite.
              c. detach the shared memory
              d. remove the shared memory
Date: 13 Oct, 2023.
==================================================================================
*/

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>

int main()
{
  int shmid;
  int key;
  key = ftok(".", 30);
  if (key == -1)
  {
    perror("Error in key");
    return 1;
  }

  printf("Creating shared memory.\n");
  shmid = shmget(key, 1024, IPC_CREAT | 0777);
  if (shmid == -1)
  {
    perror("Error in creating shared memory");
    return 1;
  }

  printf("Attaching shared memory.\n");
  char *writeData = shmat(shmid, 0, 0);
  
  printf("Enter some data: ");
  scanf("%[^\n]", writeData);

  char *readData = shmat(shmid, 0, SHM_RDONLY);
  printf("Reading data from shared memory: %s\n", readData);

  printf("Deattaching shared memory.\n");
  shmdt((void *)readData);

  printf("Removing shared memory.\n");
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}