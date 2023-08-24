#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf ("You are useless\n");
		return 0;
	}

	int fd;
	char data1[] = "abcdefghij";
	char data2[] = "klmnopqrst";

	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);

	if (fd == -1) {
		perror("Error in opening the file");
		return 1;
	}

	ssize_t dataWritten = write(fd, data1, sizeof(data1)-1);
	
	if (dataWritten == -1) {
		perror("Error in writing the data 1");
		close(fd);
		return 1;

	}

	off_t offset = lseek(fd, 10, SEEK_CUR);

	if (offset == -1) {
        	perror("Error seeking file pointer");
        	close(fd);
        	return 1;
	}

	dataWritten = write(fd, data2, sizeof(data2)-1);
	
	if (dataWritten == -1) {
        	perror("Error writing data2");
        	close(fd);
        	return 1;
    	}	

	close(fd);
	printf("Data written successfully.\n");
	return 0;
}	
