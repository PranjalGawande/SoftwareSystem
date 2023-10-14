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
#include "./structures/course.h"
// #include "./functions/showmenu.h"
// #include "./functions/admin_functions.h"

// int clientcall(int);
int welcome_menu(int);
int show_menu(int);
void admin_login(int);
void faculty_login(int);
void student_login(int);
void admin_functions(int, int);
void faculty_functions(int, int);
void student_functions(int, int);
void add_student(int, int);
void view_student_details(int, int);
void add_faculty(int, int);
void view_faculty_details(int, int);
void activate_student(int, int);
void block_student(int, int);
void modify_student(int, int);
void modify_faculty(int, int);
void view_courses (int, int);
void add_course(int, int);

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
    printf("\n********** Course Registration Portal **********\n\n");
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
        printf("\n********** Welcome to Admin Menu **********\n\n");
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
        printf("\n********** Welcome to Faculty Menu **********\n\n");
        printf("1. View Offering Courses\n");
        printf("2. Add New Course\n");
        printf("3. Remove Course\n");
        printf("4. Update Course Details\n");
        printf("5. Change Password\n");
        printf("9. Logout and Exit\n\n");

        printf("Enter your choice: \n");
        scanf("%d", &option);

        faculty_functions(sockfd, option);
        break;

    case 3:
        printf("\n********** Welcome to Student Menu **********\n\n");
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

void faculty_login(int sockfd)
{
    struct faculty curr_user;
    bool res;
    printf("Login id: ");
    scanf("%s", curr_user.login_id);
    printf("Password: ");
    char *password = getpass("");
    strcpy(curr_user.password, password);

    send(sockfd, &choice, sizeof(choice), 0);

    send(sockfd, &curr_user, sizeof(struct faculty), 0);

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

void student_login(int sockfd)
{
    struct student curr_user;
    bool res;
    printf("Login id: ");
    scanf("%s", curr_user.login_id);
    printf("Password: ");
    char *password = getpass("");
    strcpy(curr_user.password, password);

    send(sockfd, &choice, sizeof(choice), 0);

    send(sockfd, &curr_user, sizeof(struct student), 0);

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

void admin_functions(int sockfd, int option)
{
    switch (option)
    {
    case 1:
        add_student(sockfd, option);
        break;
    case 2:
        view_student_details(sockfd, option);
        break;
    case 3:
        add_faculty(sockfd, option);
        break;
    case 4:
        view_faculty_details(sockfd, option);
        break;
    case 5:
        activate_student(sockfd, option);
        break;
    case 6:
        block_student(sockfd, option);
        break;
    case 7:
        modify_student(sockfd, option);
        break;
    case 8:
        modify_faculty(sockfd, option);
        break;
    case 9:
        break;
    default:
        printf("Invalid choice");
        show_menu(sockfd);
        break;
    }
    return;
}

void faculty_functions(int sockfd, int option) {
    switch (option)
    {
    case 1:
        view_courses(sockfd, option);
        break;
    case 2:
        add_course(sockfd, option);
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
        break;
    default:
        printf("Invalid choice");
        show_menu(sockfd);
        break;
    }
    return;
}



// *************************************
// ********* ADMIN FUNCTOINS ***********
// *************************************

// 1. Adding new student
void add_student(int sockfd, int option)
{
    // printf("add func entered\n");
    struct student new_student;
    bool result;

    // printf("sended option\n");
    send(sockfd, &option, sizeof(option), 0);
    getchar();

    // Taking inputs for new student
    printf("Enter name: ");
    // fgets(new_student.name, sizeof(new_student.name), stdin);
    scanf("%[^\n]", new_student.name);

    printf("Enter age: ");
    scanf("%d", &new_student.age);
    getchar();

    printf("Enter address: ");
    // fgets(new_student.address, sizeof(new_student.address), stdin);
    scanf("%[^\n]", new_student.address);
    getchar();

    printf("Enter email: ");
    // fgets(new_student.email, sizeof(new_student.email), stdin);
    scanf("%[^\n]", new_student.email);

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
        printf("NOTE: Login Id is MT{Student_Id}\n\n");
    }
    else
    {
        printf("Error during adding student record\n");
    }
    // printf("add student completed\n");
    show_menu(sockfd);
    return;
}

// 2. view student details
void view_student_details(int sockfd, int option)
{
    struct student record;
    bool result;

    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Student Id: ");
    scanf("%d", &record.id);

    send(sockfd, &record, sizeof(struct student), 0);

    recv(sockfd, &record, sizeof(struct student), 0);
    recv(sockfd, &result, sizeof(result), 0);

    if (result == true)
    {
        printf("\n********** Student Details **********\n\n");
        printf("Student Id: %d\n\n", record.id);
        printf("Name: %s\n", record.name);
        printf("Age: %d\n", record.age);
        printf("Email: %s\n", record.email);
        printf("Address: %s\n", record.address);
        printf("Login Id: %s\n", record.login_id);
        printf("Status: %s\n", record.status);
        printf("\n*********** End of Record ***********\n\n");
    }
    else
    {
        printf("\nRecord doesnot exist\n\n");
    }

    show_menu(sockfd);
    return;
}

// 3. add new faculty
void add_faculty(int sockfd, int option)
{
    // printf("add func entered\n");
    struct faculty new_faculty;
    bool result;

    // printf("sended option\n");
    send(sockfd, &option, sizeof(option), 0);
    getchar();

    // Taking inputs for new faculty
    printf("Enter name: ");
    scanf("%[^\n]", new_faculty.name);
    getchar();
    // fgets(new_faculty.name, sizeof(new_faculty.name), stdin);

    printf("Enter department: ");
    scanf("%[^\n]", new_faculty.department);
    getchar();
    // fgets(new_faculty.department, sizeof(new_faculty.department), stdin);

    printf("Enter designation: ");
    scanf("%[^\n]", new_faculty.designation);
    getchar();
    // fgets(new_faculty.designation, sizeof(new_faculty.designation), stdin);

    printf("Enter address: ");
    scanf("%[^\n]", new_faculty.address);
    getchar();
    // fgets(new_faculty.address, sizeof(new_faculty.address), stdin);

    printf("Enter email: ");
    scanf("%[^\n]", new_faculty.email);
    getchar();
    // fgets(new_faculty.email, sizeof(new_faculty.email), stdin);

    strcpy(new_faculty.login_id, "");

    strcpy(new_faculty.password, DEFAULT_PASS);

    // printf("sended new_student record\n");
    send(sockfd, &new_faculty, sizeof(struct faculty), 0);

    int id;
    recv(sockfd, &id, sizeof(id), 0);
    // printf("received id\n");
    recv(sockfd, &result, sizeof(result), 0);
    // printf("received new_student record\n");

    if (result == true)
    {
        printf("\nFaculty record added Successfully\n\n");
        printf("Faculty Id generated is: %d\n\n", id);
        printf("NOTE: Login Id is FT{Faculty_Id}\n\n");
    }
    else
    {
        printf("Error during adding faculty record\n");
    }
    // printf("add student completed\n");
    show_menu(sockfd);
    return;
}

// 4. view faculty details
void view_faculty_details(int sockfd, int option)
{
    struct faculty record;
    bool result;

    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Faculty Id: ");
    scanf("%d", &record.id);

    send(sockfd, &record, sizeof(struct faculty), 0);

    recv(sockfd, &record, sizeof(struct faculty), 0);
    recv(sockfd, &result, sizeof(result), 0);

    if (result == true)
    {
        printf("\n********** Faculty Details **********\n\n");
        printf("Faculty Id: %d\n\n", record.id);
        printf("Name: %s\n", record.name);
        printf("Department: %s\n", record.department);
        printf("Designation: %s\n", record.designation);
        printf("Email: %s\n", record.email);
        printf("Address: %s\n", record.address);
        printf("Login Id: %s\n", record.login_id);
        printf("\n*********** End of Record ***********\n\n");
    }
    else
    {
        printf("\nRecord doesnot exist\n\n");
    }

    show_menu(sockfd);
    return;
}

// 5. activate student
void activate_student(int sockfd, int option)
{
    struct student record;
    bool result;
    int msg;
    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Student Id to activate: ");
    scanf("%d", &record.id);
    getchar();

    send(sockfd, &record, sizeof(record), 0);

    recv(sockfd, &msg, sizeof(msg), 0);

    recv(sockfd, &result, sizeof(result), 0);

    if (msg == 0)
    {
        printf("student is already ACTIVE\n");
    }
    else if (msg == 1 && result == true)
    {
        printf("Succesfully activated the student\n");
    }
    else if (msg = 2)
    {
        printf("Student record not found!!\n");
    }
    else if (result == false)
    {
        printf("Error in activating the student\n");
    }

    show_menu(sockfd);
    return;
}

// 6. block student
void block_student(int sockfd, int option)
{
    struct student record;
    bool result;
    int msg;
    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Student Id to block: ");
    scanf("%d", &record.id);
    getchar();

    send(sockfd, &record, sizeof(record), 0);

    recv(sockfd, &msg, sizeof(msg), 0);

    recv(sockfd, &result, sizeof(result), 0);

    if (msg == 0)
    {
        printf("Student is already BLOCKED\n");
    }
    else if (msg == 1 && result == true)
    {
        printf("Succesfully blocked the student\n");
    }
    else if (msg = 2)
    {
        printf("Student record not found!!\n");
    }
    else if (result == false)
    {
        printf("Error in blocking the student\n");
    }

    show_menu(sockfd);
    return;
}

// 7. Modify student
void modify_student(int sockfd, int option)
{
    struct student record;
    bool result;

    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Student Id to modify: ");
    scanf("%d", &record.id);

    printf("New Name of the Student : ");
    scanf(" %[^\n]", record.name);
    printf("New Age: ");
    scanf("%d", &record.age);
    getchar();
    printf("New Address: ");
    scanf("%[^\n]", record.address);
    getchar();
    printf("New email: ");
    scanf("%[^\n]", record.email);

    send(sockfd, &record, sizeof(struct student), 0);

    recv(sockfd, &result, sizeof(result), 0);

    if (result == false)
    {
        printf("Error modifying the student details,please re-check the User ID!\n\n");
    }
    else
    {
        printf("Succesfully modified the student details!\n\n");
    }

    show_menu(sockfd);
    return;
}


// 8. Modify faculty
void modify_faculty(int sockfd, int option)
{
    struct faculty record;
    bool result;

    send(sockfd, &option, sizeof(option), 0);

    printf("Enter Faculty Id to modify: ");
    scanf("%d", &record.id);

    printf("New Name of the Faculty : ");
    scanf(" %[^\n]", record.name);
    getchar();
    printf("New Department: ");
    scanf("%[^\n]", record.department);    
    getchar();
    printf("New Designation: ");
    scanf("%[^\n]", record.designation);
    getchar();
    printf("New Address: ");
    scanf("%[^\n]", record.address);
    getchar();
    printf("New email: ");
    scanf("%[^\n]", record.email);

    send(sockfd, &record, sizeof(struct faculty), 0);

    recv(sockfd, &result, sizeof(result), 0);

    if (result == false)
    {
        printf("Error modifying the faculty details,please re-check the User ID!\n\n");
    }
    else
    {
        printf("Succesfully modified the faculty details!\n\n");
    }

    show_menu(sockfd);
    return;
}


// ***************************************
// ********* FACULTY FUNCTOINS ***********
// ***************************************


void view_courses (int sockfd, int option) {
    send (sockfd, &option, sizeof(option), 0);

    struct course record;
    bool resutl;
    
    printf ("Enter your Faculty Id: ");
    scanf("%d", &record.faculty_id);

    send (sockfd, &record, sizeof(struct course), 0);

    


}

void add_course(int sockfd, int option) {
    send (sockfd, &option, sizeof(option), 0);

    struct course record;
    bool result;

    getchar();
    printf ("Enter Course Name: ");
    scanf("%[^\n]", record.name);

    getchar();
    printf ("Enter Your Faculty Id: ");
    scanf("%d", &record.faculty_id);

    getchar();
    printf ("Enter Department: ");
    scanf("%[^\n]", record.department);

    getchar();
    printf ("Enter Number of seats: ");
    scanf("%d", &record.no_of_seats);

    getchar();
    printf ("Enter Course Credits: ");
    scanf("%d", &record.credits);

    getchar();
    printf ("Enter Course Code (First 2 letters): ");
    scanf("%[^\n]", record.course_code);

    // strcpy(record.courseid, "");

    send (sockfd, &record, sizeof(struct course), 0);

    // int id;
    // recv (sockfd, &id, sizeof(id), 0);

    char code[6];
    strcpy(code, record.course_code);
    recv (sockfd, &code, sizeof(code), 0);

    recv (sockfd, &result, sizeof(result), 0);

    if (result == true) {
        printf ("\nNew Course Added Successfully\n\n");
        printf ("Course Code generated: %s\n\n", code);
    }
    else {
        printf ("Error during adding course");
        return;
    }

    show_menu(sockfd);
    return;

}