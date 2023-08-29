#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	struct flock lock;

	int fd = open("my_file.txt", O_RDWR | O_CREAT, 0644);
	
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

	printf("Inside Critical section\n");
	printf("Press Enter to unlock\n");
	getchar();

	printf("Unlocked\n");

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	
	printf("Finished\n");
	return 0;
}


