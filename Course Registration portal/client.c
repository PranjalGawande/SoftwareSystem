#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

// #include "./functions/login.h"
#include "./structures/admin.h"
#include "./structures/faculty.h"
#include "./structures/student.h"
// #include "./functions/showmenu.h"
// #include "./functions/admin_functions.h"

// int clientcall(int);
int welcome_menu(int);
int show_menu(int);
void admin_login(int);
void faculty_login(int);
void student_login(int);
void admin_functions(int, int);
void faculty_funtions(int, int);
void student_functions(int, int);
void add_student(int, int);

#define DEFAULT_PASS "abc123"
#define STUDENT_DB "/home/pranjal-gawande/Software System/Course Registration portal/database/student_db"

int choice;

int main()
{
    struct sockaddr_in server;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Error in creating socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    int status = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (status == -1)
    {
        perror("Error during connect");
        return 1;
    }

    welcome_menu(sockfd);
    show_menu(sockfd);
    close(sockfd);

    return 0;
}

int welcome_menu(int sockfd)
{
    printf("********** Course Registration Portal **********\n\n");
    printf("Type of login: \n");
    printf("1. Admin\n");
    printf("2. Faculty\n");
    printf("3. Student\n\n");
    printf("Enter a choice: ");
    scanf("%d", &choice);

    getchar();
    switch (choice)
    {
    case 1:
        admin_login(sockfd);
        break;
    case 2:
        faculty_login(sockfd);
        // faculty_menu();
        // faculty_funtions(sockfd);
        break;
    case 3:
        student_login(sockfd);
        // student_menu();
        // student_functions(sockfd);
        break;
    default:
        printf("\nInvalid choice \n");
        welcome_menu(sockfd);
        break;
    }

    return 0;
}

int show_menu(int sockfd)
{
    int option;
    switch (choice)
    {
    case 1:
        printf("********** Welcome to Admin Menu **********\n\n");
        printf("1. Add Student\n");
        printf("2. View Student Details\n");
        printf("3. Add Faculty\n");
        printf("4. View Faculty Details\n");
        printf("5. Activate Student\n");
        printf("6. Block Student\n");
        printf("7. Modify Student Details\n");
        printf("8. Modify Faculty Details\n");
        printf("9. Logout and Exit\n\n");

        printf("Enter a option: ");
        scanf("%d", &option);

        admin_functions(sockfd, option);
        break;

    case 2:
        printf("********** Welcome to Faculty Menu **********\n\n");
        printf("1. View Offering Courses\n");
        printf("2. Add New Course\n");
        printf("3. Remove Course\n");
        printf("4. Update Course Details\n");
        printf("5. Change Password\n");
        printf("9. Logout and Exit\n\n");

        printf("Enter your choice: \n");
        break;

    case 3:
        printf("********** Welcome to Student Menu **********\n\n");
        printf("1. View All Courses\n");
        printf("2. Enroll New Course\n");
        printf("3. Drop Course\n");
        printf("4. View Enrolled Course Details\n");
        printf("5. Change Password\n");
        printf("9. Logout and Exit\n\n");
        printf("Enter your choice: \n");

        scanf("%d", &option);
    
    default:
        printf("Invalid choice");
        break;
    }
    // admin_functions(sockfd, option);

    return 0;
}

// Menu of Faculty
// int faculty_menu()
// {
//     int option;
//     printf("********** Welcome to Faculty Menu **********\n\n");
//     printf("1. View Offering Courses\n");
//     printf("2. Add New Course\n");
//     printf("3. Remove Course\n");
//     printf("4. Update Course Details\n");
//     printf("5. Change Password\n");
//     printf("9. Logout and Exit\n\n");

//     printf("Enter your choice: \n");

//     scanf("%d", &option);
//     return option;
// }

// Menu of Student
// int student_menu()
// {
//     int option;
//     printf("********** Welcome to Student Menu **********\n\n");
//     printf("1. View All Courses\n");
//     printf("2. Enroll New Course\n");
//     printf("3. Drop Course\n");
//     printf("4. View Enrolled Course Details\n");
//     printf("5. Change Password\n");
//     printf("9. Logout and Exit\n\n");
//     printf("Enter your choice: \n");

//     scanf("%d", &option);
//     return option;
// }

void admin_login(int sockfd)
{
    struct admin curr_user;
    bool res;
    // int choice = 1;
    printf("Login id: ");
    scanf("%s", curr_user.login_id);
    
    printf("Password: ");
    char *password = getpass("");
    strcpy(curr_user.password, password);

    send(sockfd, &choice, sizeof(choice), 0);

    send(sockfd, &curr_user, sizeof(struct admin), 0);

    recv(sockfd, &res, sizeof(res), 0);

    if (res == true)
    {
        printf("\nLogin Successful \n\n");
    }
    else
    {
        printf("\nInvalid credentials\n\n");
        welcome_menu(sockfd);
    }

    return;
}

void faculty_login(int sockfd) {
    struct faculty curr_user;
    bool res;
    printf("Login id: ");
    scanf("%s", curr_user.login_id);
    printf("Password: ");
    char* password = getpass("");
    strcpy(curr_user.password, password);

    send(sockfd, &choice, sizeof(choice), 0);

    send(sockfd, &curr_user, sizeof(struct faculty), 0);

    recv(sockfd, &res, sizeof(res), 0);

    if (res == true) {
        printf("\nLogin Successful \n\n");
    }
    else {
        printf("\nInvalid credentials\n\n");
        welcome_menu(sockfd);
    }

    return;
}

void student_login(int sockfd) {
    struct student curr_user;
    bool res;
    printf("Login id: ");
    scanf("%s", curr_user.login_id);
    printf("Password: ");
    char* password = getpass("");
    strcpy(curr_user.password, password);

    send(sockfd, &choice, sizeof(choice), 0);

    send(sockfd, &curr_user, sizeof(struct student), 0);

    recv(sockfd, &res, sizeof(res), 0);

    if (res == true) {
        printf("\nLogin Successful \n\n");
    }
    else {
        printf("\nInvalid credentials\n\n");
        welcome_menu(sockfd);
    }

    return;
}

void admin_functions(int sockfd, int option)
{
    // printf("Entered admin function\n");
    // scanf("%d", &option);
    switch (option)
    {
    case 1:
        // printf("add func called\n");
        add_student(sockfd, option);
        // printf("add func returned\n");
        break;
    case 2:
        // view_student_details(sockfd, option);
        break;
    case 3:
        // add_faculty(sockfd, option);
        break;
    case 4:
        // view_faculty_details(sockfd, option);
        break;
    case 5:
        // activate_student(sockfd, option);
        break;
    case 6:
        // block_student(sockfd, option);
        break;
    case 7:
        // modify_student(sockfd, option);
        break;
    case 8:
        // modify_faculty(sockfd, option);
        break;
    case 9:
        // logout(sockfd, option);
        break;
    default:
        printf("Invalid choice");
        show_menu(sockfd);
        break;
    }
    return;
}

void add_student(int sockfd, int option)
{
    // printf("add func entered\n");
    struct student new_student, login;
    bool result;

    // printf("sended option\n");
    send(sockfd, &option, sizeof(option), 0);
    getchar();

    // Taking inputs for new student
    printf("Enter name: ");
    scanf("%s", new_student.name);

    printf("Enter age: ");
    scanf("%d", &new_student.age);

    printf("Enter address: ");
    scanf("%s", new_student.address);

    printf("Enter email: ");
    scanf("%s", new_student.email);

    strcpy(new_student.login_id, "");

    strcpy(new_student.password, DEFAULT_PASS);

    // printf("sended new_student record\n");
    send(sockfd, &new_student, sizeof(struct student), 0);

    int id;
    recv(sockfd, &id, sizeof(id), 0);
    // printf("received id\n");
    recv(sockfd, &result, sizeof(result), 0);
    // printf("received new_student record\n");

    if (result == true)
    {
        printf("\nStudent record added Successfully\n\n");
        printf("Student Id generated is: %d\n\n", id);
        printf("NOTE: Login Id is MT{Student Id}\n\n");
    }
    else
    {
        printf("Error during adding student record\n");
    }
    // printf("add student completed\n");
    show_menu(sockfd);
    return;
}
