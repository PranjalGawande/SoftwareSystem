#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int fd;
	char filename[100];
	char buf[1];
	ssize_t byteread;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("You are useless");
		return 1;
	}
	
	while((byteread = read(fd, buf, sizeof(buf))) > 0) {
		write(STDOUT_FILENO, buf, 1);
	}

	if (byteread == -1) {
		perror("Error Reading the file");
		return 1;
	}

	close(fd);
	return 0;
}
