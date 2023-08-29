#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Enter the file\n");
		return 0;
	}

	int fd = open(argv[1], O_RDONLY | O_CREAT, 0644);
	
	if (fd == -1) {
		perror ("Error in opening the file");
		return 1;
	}

	int flag = fcntl(fd, F_GETFL);
	
	printf("File is opened in: ");
	
	if((flag & O_ACCMODE) == O_RDONLY) {
		printf("Read Only mode\n");
	}
	else if ((flag & O_ACCMODE) == O_WRONLY) {
		printf("Write Only mode\n");
	}
	else if ((flag & O_ACCMODE) == O_RDWR) {
		printf("Read Write mode\n");
	}
	else {
		printf("Unknown\n");
	}
	
	close(fd);

	return 0;
}
