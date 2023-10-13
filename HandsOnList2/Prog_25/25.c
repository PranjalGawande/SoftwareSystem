/*
============================================================================
Name : 25.c
Author : Pranjal Gawande
Description : Write a program to print a message queue's 
              (use msqid_ds and ipc_perm structures)
              a. access permission
              b. uid, gid
              c. time of last message sent and received
              d. time of last change in the message queue
              d. size of the queue
              f. number of messages in the queue
              g. maximum number of bytes allowed
              h. pid of the msgsnd and msgrcv
Date: 12 Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

int main() {
    int key;
    int msqid;

    
    key = ftok(".", 25);  
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    
    msqid = msgget(key, IPC_CREAT|0744);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msqid_ds info;

    if (msgctl(msqid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        return 1;
    }
    
    printf("Message Queue Information:\n");
    printf("Access Permission: %o\n", info.msg_perm.mode);
    printf("UID: %d\n", info.msg_perm.uid);
    printf("GID: %d\n", info.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&info.msg_ctime));
    printf("Size of the Queue: %lu bytes\n", (unsigned long)info.msg_qbytes);
    printf("Number of Messages in the Queue: %lu\n", (unsigned long)info.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", (unsigned long)info.msg_qbytes);
    printf("PID of msgsnd: %d\n", info.msg_lspid);
    printf("PID of msgrcv: %d\n", info.msg_lrpid);

    return 0;
}