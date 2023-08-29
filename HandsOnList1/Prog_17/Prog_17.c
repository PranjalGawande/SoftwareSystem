#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct {
	int ticket_no;
}db;

int main() {
	
	struct flock lock;

	int fd = open("ticket_no.txt", O_RDWR);
	
	if (fd == -1) {
		perror ("Error in opening the file");
		return 1;
	}

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();

	printf("Before entering the critical sectioni...\n");
	
	fcntl(fd, F_SETLKW, &lock);
	
	read(fd, &db, sizeof(db));
	printf("Current Ticket Number = %d\n", db.ticket_no);
	db.ticket_no++;
	lseek(fd, 0L, SEEK_SET);
	write(fd, &db, sizeof(db));
	printf("Press Enter to unlock\n");
	getchar();

	printf("Updated Ticket number : %d\n", db.ticket_no);
	printf("Unlocked\n");

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	
	printf("Finished\n");
	close(fd);
	return 0;
}


