/*
============================================================================
Name : 27.c
Author : Pranjal Gawande
Description : Write a program to receive messages from the message queue.
              a. with 0 as a flag
              b. with IPC_NOWAIT as a flag
Date: 12 Oct, 2023.
============================================================================
*/

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

struct msg
{
  long int messageType;
  char messageText[1024];
} myq;

int main()
{
  int messageId;
  key_t key;

  key = ftok(".", 27);
  messageId = msgget(key, IPC_CREAT | 0777);

  myq.messageType = 1;
  strncpy(myq.messageText, "Data Received", 1024);

  msgsnd(messageId, &myq, sizeof myq, 0);

  msgrcv(messageId, &myq, sizeof myq, 1, 0);

  printf("Part a with 0 as a flag\n");
  printf("Message: %s\n\n", myq.messageText);

  msgrcv(messageId, &myq, sizeof myq, 22, IPC_NOWAIT);
  printf("Part b with IPC_NOWAIT as a flag\n");
  printf("Message: %s\n", myq.messageText);

  return 0;
}