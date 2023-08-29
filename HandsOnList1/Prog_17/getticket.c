#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct ticket {
	int ticket_no;
}db;

int main(int argc, char* argv[]) {

	int fd = open ("ticket_no.txt", O_CREAT | O_RDWR, 0777);

	if (fd == -1) {
		perror("Error in opening file");
		return 1;
	}

	printf("Enter the starting ticket number: ");
	scanf("%d", &db.ticket_no);
	write(fd, &db, sizeof(db));
	
	printf("Current Ticket number is : %d \n", db.ticket_no);			
	
	close(fd);
	
	return 0;
}
