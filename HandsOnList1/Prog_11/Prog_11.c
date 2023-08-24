#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd1, fd2, fd3, fd4;
	fd1=open("my_file.txt",O_RDWR);
	fd2=dup(fd1);
	dup2(fd2,fd3);
	fd4=fcntl(fd1, F_DUPFD);
	printf("fd1 = %d \nfd2 = %d \nfd4 = %d\n", fd1, fd2, fd4);
        return 0;
}	
