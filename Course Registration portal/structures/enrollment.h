#ifndef ENROLLMENT_RECORD
#define ENROLLMENT_RECORD

struct enrollment
{
    // int id; // 0, 1, 2 ....
    int courseid;
    // int no_of_student_enrolled;
    int studentid;
    char status[12];
    //time_t enroll_time;    
};

#endif