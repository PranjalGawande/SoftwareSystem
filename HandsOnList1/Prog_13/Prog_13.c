#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
	printf("Waiting for Input from STDIN for 10 sec...\n");
	fd_set read_fd;
	FD_ZERO(&read_fd);
	FD_SET(STDIN_FILENO, &read_fd);
	
	struct timeval wait_time;
	wait_time.tv_sec = 10;
	wait_time.tv_usec = 0;

	int result = select(STDIN_FILENO + 1, &read_fd, NULL, NULL, &wait_time);
	
	if (result == -1) {
		perror("Error in Select");
		return 1;
	}

	if (result == 0) {
		printf("TIMEOUT, no data received within 10 seconds.\n");
	}
	else {
		if (FD_ISSET(STDIN_FILENO, &read_fd)) {
			printf("Data is available within 10 sec !\n");
			char input[1024];
			if (fgets(input, sizeof(input), stdin)) {
				input[strcspn(input, "\n")] = '\0';
				printf("Input entered: %s\n", input);
			}
		}
	}

	return 0;
}
