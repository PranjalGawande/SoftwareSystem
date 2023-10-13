/*
==============================================================================
Name : 28.c
Author : Pranjal Gawande
Description : Write a program to change the exiting message queue permission.
              (use msqid_ds structure)
Date: 13 Oct, 2023.
==============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int key;
    int msqid;

    // creating key
    key = ftok(".", 28);

    if (key == -1)
    {
        perror("Error in ftok");
        return 1;
    }

    // creating message queue
    msqid = msgget(key, IPC_CREAT | 0766);

    if (msqid == -1)
    {
        perror("Error in msgget");
        return 1;
    }

    struct msqid_ds info;

    // checking current message queue permissions
    if (msgctl(msqid, IPC_STAT, &info) == -1)
    {
        perror("Error in msgctl");
        return 1;
    }
    printf("Access Permission Before: %o\n", info.msg_perm.mode);

    // setting new permissions
    info.msg_perm.mode = 0777;

    if (msgctl(msqid, IPC_SET, &info) == -1)
    {
        perror("msgctl (IPC_SET)");
        exit(1);
    }
    printf("Access Permission After: %o\n", info.msg_perm.mode);
    printf("Message queue permissions updated successfully.\n");

    return 0;
}