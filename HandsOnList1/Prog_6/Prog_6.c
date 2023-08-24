#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	char buffer[1024];
	ssize_t byteCount;

	while ((byteCount = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
		write(STDOUT_FILENO, buffer, byteCount);
	}

	if (byteCount == -1) {
		perror("Error reading from STDIN");
	}

	return 0;
}
