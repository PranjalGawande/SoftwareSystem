#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	struct stat fileInfo;
	const char * filename = "my_file.txt";
	int fd = open (filename, O_RDONLY);

	if (fd == -1) {
		perror ("Error in opening the file");
		return 1;
	}

	if (fstat(fd, &fileInfo) == -1) {
		perror("Error in getting file information");
		return 1;
	}

	printf("File Name:  %s\n", filename);
	printf("File Inode: %lu\n", fileInfo.st_ino);
	printf("Number of hardlinks: %lu\n", fileInfo.st_nlink);
	printf("File UID: %d\n", fileInfo.st_uid);
	printf("File GID: %d\n", fileInfo.st_gid);
	printf("File Size: %lu bytes\n", fileInfo.st_size);
	printf("File Block size: %lu\n", fileInfo.st_blksize);
	printf("Number of blocks: %lu\n", fileInfo.st_blocks);
	printf("Time of Last Access: %lu\n", fileInfo.st_atim.tv_nsec);
	printf("Time of Last Modification: %lu\n", fileInfo.st_mtim.tv_nsec);
	printf("Time of Last Change: %lu\n", fileInfo.st_ctim.tv_nsec);

	return 0;
}
