#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct Train {
	int train_no;
	int ticket_no;
}db[3];

int main() {

	printf("Enter the Train Details\n");

	for (int i = 0; i < 3; i++) {
		printf("Train number: ");
		scanf("%d", &db[i].train_no);
		printf("Ticket number: ");
		scanf("%d", &db[i].ticket_no);
	}

	int fd = open("Record.txt", O_CREAT | O_RDWR, 0744);
	
	if (fd == -1) {
		perror("Error opening in file\n");
		return 1;
	}

	ssize_t fd_write = write(fd, &db, sizeof(db));

	if (fd_write == -1) {
		perror("Error in writing in file\n");
		close(fd);
		return 1;
	}


	int fd_close = close(fd);
	
	if(fd_close == -1) {
		perror ("Error in closing the file");
		return 1;
	}

	printf("Record saved successfully\n");

	return 0;
}


