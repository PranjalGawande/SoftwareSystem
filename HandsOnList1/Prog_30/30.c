/*
========================================================================================
Name : 30.c
Author : Pranjal Gawande
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 8th Sept, 2023.
========================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main() {
	pid_t sid;

	if (fork()) {
		printf ("Parent PID : %d\n", getpid());
		exit(0);
	}

	sid = setsid();
	printf ("Child PID : %d\n", getpid());
	prctl(PR_SET_NAME, "my_daemon_process");

	if( chdir("/") < 0 ) {
		exit(0);
	}

	umask(0);

	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);

	time_t current;
	time(&current);

	struct tm *action;
	action = localtime(&current);
	action->tm_min += 1;

	do {
		time(&current);
	} while ( difftime(current, mktime(action)) < 0 );

	int fd = open ("/home/hari/Desktop/Software_System/sample.txt", O_CREAT | O_RDWR, 0644);
	if ( -1 == fd ) {
		perror ("File opening error");
		return -1;
	}

	char buff[] = "Daemon writing after wating for a minute.\n";
	size_t size = write (fd, buff, strlen(buff));
	if ( -1 == size ) {
		perror ("File writing error");
		return -1;
	}
	close (fd);
	return 0;
}
