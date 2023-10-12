#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<stdbool.h>

#include "./structures/admin.h"
#include "./structures/faculty.h"
#include "./structures/student.h"
#include "./functions/validate.h"

#define DEFAULT_PASS "abc123"
#define STUDENT_DB "/home/pranjal-gawande/Software System/Course Registration portal/database/student_db"
#define FACULTY_DB "/home/pranjal-gawande/Software System/Course Registration portal/database/faculty_db"


int servercall (int);
bool addstudent(int, struct student);
bool addfaculty(int, struct faculty);

int main() {
	struct sockaddr_in server, client;
	int sockfd, clifd, c_size;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);		// Create socket
	if (sockfd == -1) {
		perror("Error in creating socket");
		return 1;
	}

	printf("Server socket is created\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(8080);

	int status = bind (sockfd, (struct sockaddr *)&server, sizeof(server));			
	if (status == -1) {
		perror ("Error during bind");
		return 1;
	}
	printf("Bind successful\n");

	status = listen (sockfd, 5);		// 5 request will be queued, after that request will be rejected 
	if (status == -1) {
		perror("Error during listen");
		return 1;
	}
	printf("listening...\n");
	printf ("Welcome to IIITB Academia Portal\n\n");
    printf ("Waiting for client to connect...\n");

	
	while(1) {
		c_size = sizeof(client);
		clifd = accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&c_size);
		if (clifd == -1) {
			perror ("Error during accepting a connection");
			return 1;
		}
		// printf("Client accepted connection\n");
		
		if (!fork()) {
			close(sockfd);
			printf("Connected to client\n");
			servercall(clifd);
			exit(EXIT_SUCCESS);
		}
		else {
			close(clifd);
		}
	}
	//close(sockfd);

	return 0;
}

int servercall(int clifd) {
	bool result;
	int choice, option, read_size;
	while(1) {			// for login
		recv(clifd, &choice, sizeof(choice), 0);
		printf("Choice: %d\n", choice);
		switch(choice) {
			case 1:
				struct admin curr_userA;
				//char curr_loginId[25];
				recv(clifd, &curr_userA, sizeof(struct admin), 0);
				//strcpy(curr_loginId,curr_user.login_id);
				result = validateAdmin(curr_userA);
				send(clifd, &result, sizeof(result), 0);
				break;
			case 2:
				struct faculty curr_userF;
				// //char curr_loginId[25];
				recv(clifd, &curr_userF, sizeof(struct faculty), 0);
				// //strcpy(curr_loginId,curr_user.login_id);
				result = validateFaculty(curr_userF);
				send(clifd, &result, sizeof(result), 0);
				break;
			case 3:
				struct student curr_userS;
				// //char curr_loginId[25];
				recv(clifd, &curr_userS, sizeof(struct student), 0);
				// //strcpy(curr_loginId,curr_user.login_id);
				result = validateStudent(curr_userS);
				send(clifd, &result, sizeof(result), 0);
				break;
			default:
				// result = false;
				// send(clifd, &result, sizeof(result), 0);
				break;
		}
		if (result == true) {
			break;
		}
	}

	while(1) {
		
		recv (clifd, &option, sizeof(option), 0);
		//printf("option: %d\n", option);
		switch (choice) {
			case 1:
				switch (option) {
					case 1:					// add student
						struct student record1;
						recv(clifd, &record1, sizeof(struct student), 0);
						//printf("Received record from client\n");
						result = addstudent(clifd, record1);
						//printf("resutl returned\n");
						send (clifd, &result, sizeof(result), 0);
						//printf("Sended record to client\n");
						//send (clifd, &record, sizeof(record), 0);
						// option = 9;
						break;
					case 2:
						break;
					case 3:
						struct faculty record3;
						recv(clifd, &record3, sizeof(struct faculty), 0);
						result = addfaculty(clifd, record3);
						send (clifd, &result, sizeof(result), 0);
						break;
					case 4:
						break;
					default:
						break;
					
				}
				break;
			case 9:
				break;
		}
		if (option == 9) {
			break;
		}

	}
	close(clifd);
	printf("client session end");

	return 0;
}

bool addstudent(int clifd, struct student record) {
	//printf("at add student\n");
	bool result;
	struct student prev_record;

	int fd = open(STUDENT_DB, O_RDWR, 0777);
    if (fd == -1 && errno == ENOENT) {
        fd = open(STUDENT_DB, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1) {
			perror("Error in opening student_db");
			exit(EXIT_FAILURE);
		}
		record.id = 1; 				// if student_db was not created
    }
    else if (fd == -1) {
        perror("Error in opening student_db file");
        exit(EXIT_FAILURE);
    }
    else {

        // using read lock for fetching id from prev student
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_END;
        lock.l_start = (-1) * sizeof(struct student);
        lock.l_len = sizeof(struct student);
        lock.l_pid = getpid();

        int status = fcntl(fd, F_SETLKW, &lock);
        if (status == -1) {
            perror("Error while locking student record");
            exit(EXIT_FAILURE);
        }

		lseek (fd, (-1)*sizeof(struct student), SEEK_END);

        ssize_t fd_read = read(fd, &prev_record, sizeof(struct student));
        if (fd_read == -1) {
            perror("Error in reading prev_student record");
            exit(EXIT_FAILURE);
        }

        lock.l_type = F_UNLCK;
        status = fcntl(fd, F_SETLK, &lock);
        if (status == -1) {
            perror("Error while unlocking student record");
            exit(EXIT_FAILURE);
        }
		// printf("prev_id: %d\n", prev_record.id);
		// printf("new_id: %d\n", record.id);
        record.id = prev_record.id + 1;
		// printf("generated_id: %d\n", record.id);

    }

	record.status = 1;

	// generate login_id -> MT{id}
    // strcpy(record.login_id, "MT");
	sprintf(record.login_id, "MT%d", record.id);

	int id = record.id;
	send(clifd, &id, sizeof(id), 0);

	printf("Generated_id: %d\n", record.id);

	ssize_t fd_write = write(fd, &record, sizeof(struct student));
	if (fd_write == -1) {
		perror("Error in writing student record");
		result = false;
		exit(EXIT_FAILURE);
	}
	else {
		result = true;
	}
	return result;
}


bool addfaculty(int clifd, struct faculty record) {
	//printf("at add student\n");
	bool result;
	struct faculty prev_record;

	int fd = open(FACULTY_DB, O_RDWR, 0777);
    if (fd == -1 && errno == ENOENT) {
        fd = open(FACULTY_DB, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1) {
			perror("Error in opening faculty_db");
			exit(EXIT_FAILURE);
		}
		record.id = 1; 				// if student_db was not created
    }
    else if (fd == -1) {
        perror("Error in opening faculty_db file");
        exit(EXIT_FAILURE);
    }
    else {

        // using read lock for fetching id from prev student
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_END;
        lock.l_start = (-1) * sizeof(struct faculty);
        lock.l_len = sizeof(struct faculty);
        lock.l_pid = getpid();

        int status = fcntl(fd, F_SETLKW, &lock);
        if (status == -1) {
            perror("Error while locking faculty record");
            exit(EXIT_FAILURE);
        }

		lseek (fd, (-1)*sizeof(struct faculty), SEEK_END);

        ssize_t fd_read = read(fd, &prev_record, sizeof(struct faculty));
        if (fd_read == -1) {
            perror("Error in reading prev_student record");
            exit(EXIT_FAILURE);
        }

        lock.l_type = F_UNLCK;
        status = fcntl(fd, F_SETLK, &lock);
        if (status == -1) {
            perror("Error while unlocking student record");
            exit(EXIT_FAILURE);
        }
		// printf("prev_id: %d\n", prev_record.id);
		// printf("new_id: %d\n", record.id);
        record.id = prev_record.id + 1;
		// printf("generated_id: %d\n", record.id);

    }


	// generate login_id -> FT{id}
	sprintf(record.login_id, "FT%d", record.id);

	int id = record.id;
	send(clifd, &id, sizeof(id), 0);

	printf("Generated_id: %d\n", record.id);

	ssize_t fd_write = write(fd, &record, sizeof(struct faculty));
	if (fd_write == -1) {
		perror("Error in writing faculty record");
		result = false;
		exit(EXIT_FAILURE);
	}
	else {
		result = true;
	}
	return result;
}

