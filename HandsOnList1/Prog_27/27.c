/*
==============================================================================
Name : 27.c
Author : Pranjal Gawande
Description : Write a program to execute ls -Rl by the following system calls
	      a. execl
	      b. execlp
	      c. execle
	      d. execv
	      e. execvp
Date: 8th Sept, 2023.
==============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int choice;

	printf("Enter a choice: \n");
	printf("1. execl\n");
	printf("2. execlp\n");
	printf("3. execle\n");
	printf("4. execv\n");
	printf("5. execvp\n");

	scanf ("%d", &choice);

	switch (choice) {
		case 1 : if (execl ("/bin/ls", "ls", "-Rl", NULL) == -1) {
				perror ("Error in execl");
				return 1;
			 }
			 break;
		case 2 : if (execlp ("/bin/ls", "ls", "-Rl", NULL) == -1) {
				 perror ("Error in execlp");
				 return 1;
			 }
			 break;
		case 3 : char *envp[] = {NULL};
			 if (execle ("/bin/ls", "ls", "-Rl", NULL, envp) == -1) {
				 perror ("Error in execle");
				 return 1;
			 }
			 break;
		case 4 : char *args1[] = {"ls", "-Rl", NULL};
			 if (execv ("/bin/ls", args1) == -1) {
				 perror ("Error in execv");
				 return 1;
			 }
			 break;
		case 5 : char *args2[] = {"ls", "-Rl", NULL};
			 if (execvp ("/bin/ls", args2) == -1) {
				 perror ("Error in execvp");
				 return 1;
			 }
			 break;
		default : printf ("Invalid option\n");
			  break;
	}

	return 0;
}
