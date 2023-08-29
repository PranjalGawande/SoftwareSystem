#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct Train {
	int train_no;
	int ticket_no;
}db;

int main() {

	struct flock lock;

	int fd = open("Record.txt", O_RDWR);
	int n;

	if (fd == -1) {
		perror("Error in opening file");
		return 1;
	}

	printf("Select Train number: ");
	scanf("%d",&n);

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (n - 1) * sizeof(struct Train);
	lock.l_len = sizeof(struct Train);
	lock.l_pid = getpid();

	printf("Before entering the critical sectioni...\n");
	
	fcntl(fd, F_SETLKW, &lock);

	lseek(fd, (n - 1) * sizeof(struct Train), SEEK_SET);
	read(fd, &db, sizeof(struct Train));

	printf("Current Ticket number is: %d\n",db.ticket_no);
	printf("Please press Enter to book a ticket \n");

	getchar();
	getchar();

	db.ticket_no++;

	lseek(fd, -1 * sizeof(struct Train), SEEK_CUR);
	write(fd, &db, sizeof(struct Train));

	printf("Unlocked");
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Booked ticket number is: %d\n", db.ticket_no);

	close(fd);
	return 0;
}
