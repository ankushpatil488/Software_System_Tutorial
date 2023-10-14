#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
char* authenticateStudent(int clientSocket) {
    struct student my_student, temp;
    int openFD = open("student_database.txt", O_RDONLY, 0644); // Open in read-only mode

    if (openFD == -1) {
        perror("Error opening file");
        return NULL; // Return NULL to indicate an error
    }

    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare a buffer for sending data
    send(clientSocket, "Enter Student Username(ID): ", strlen("Enter Student Username(ID): "), 0);
    int readResult = read(clientSocket, my_student.loginId, sizeof(my_student.loginId) - 1);

    if (readResult <= 0) {
        send(clientSocket, "Error receiving Student username from server", strlen("Error receiving Student username from server"), 0);
        return NULL; // Return NULL to indicate an error
    }
    my_student.loginId[readResult] = '\0';

    send(clientSocket, "Enter Student Password: ", strlen("Enter Student Password: "), 0);
    readResult = read(clientSocket, my_student.password, sizeof(my_student.password) - 1);

    if (readResult <= 0) {
        send(clientSocket, "Error receiving Student password from server", strlen("Error receiving Student password from server"), 0);
        return NULL; // Return NULL to indicate an error
    }
    my_student.password[readResult] = '\0';

    // Reset the file pointer to the beginning of the file
    lseek(openFD, 0, SEEK_SET);

    // Loop to search for the faculty in the file
    while (read(openFD, &temp, sizeof(temp)) > 0) {
        if (customStrCmp(my_student.loginId, temp.loginId) == 0 && customStrCmp(my_student.password, temp.password) == 0) {
            // Authentication succeeded, dynamically allocate memory for the loginId and return it
            char* loginIdCopy = (char*)malloc(strlen(my_student.loginId) + 1);
            if (loginIdCopy != NULL) {
                strcpy(loginIdCopy, my_student.loginId);
                close(openFD);
                return loginIdCopy;
            }
        }
    }
    // Authentication failed
    close(openFD);
    return NULL; // Return NULL to indicate an error
}

int viewAllCourses(int clientSocket,char* auth){}

int enrollNewCourse(int clientSocket,char* auth){}

int dropCourse(int clientSocket,char* auth){}

int viewEnrolledCourseDetails(int clientSocket,char* auth){}


int changeStudentPassword(int clientSocket)
{
    struct student my_student, temp;
    int openFD = open("student_database.txt", O_RDWR, 0644); // Open in read-only mode
    if (openFD == -1)
    {
        perror("Error opening file");
        return 0;
    }
    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data
    send(clientSocket, "Enter Student Username ID for updation of password ", strlen("Enter Student Username ID for updation of password: "), 0);
    int readResult = read(clientSocket, my_student.loginId, sizeof(my_student.loginId) - 1);

    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving Student ID from server", strlen("Error receiving Student ID from server"), 0);
        return 0;
    }
    my_student.loginId[readResult] = '\0';
    // Reset the file pointer to the beginning of the file
    lseek(openFD, 0, SEEK_SET);
    // Loop to search for the student in the file
    while (read(openFD, &temp, sizeof(temp)) > 0)
    {
        if (customStrCmp(my_student.loginId, temp.loginId) == 0)
        { // Compare the student IDs
            found = true;
            break;
        }
    }
    if (found)
    {
        send(clientSocket, "Enter Password to update: ", strlen("Enter Password to update: "), 0);
        readResult = read(clientSocket, temp.password, sizeof(temp.password) - 1);
        temp.password[readResult]='\0';

        lseek(openFD,-sizeof(struct student),SEEK_CUR); //// Move the file pointer back to the beginning of the current record
        write(openFD,&temp,sizeof(temp));// Overwrite the entire record with the updated data
        close(openFD);

        return 1;
    }
    else
    {
        send(clientSocket, "Student id not found\n", strlen("Student id not found\n"), 0);
        close(openFD);
        return 0;
    }
    return 0;
}


int student_functionality(int clientSocket)
{
    char *auth=authenticateStudent(clientSocket);
    if (strcmp(auth,"0")!=0)
    {
        char readbuff[1000], writebuff[1000]; // A buffer used for reading & writing to the client
        int a = 1;
        while (1)
        {
            if (a == 1)
            {
                send(clientSocket, "Login Successfully\n", strlen("Login Successfully\n"), 0);
                a = 0;
            }
            send(clientSocket, "Welcome to the Student Menu\n", strlen("Welcome to the Student Menu\n"), 0);
            char adminPrompt[] = "\nStudent can Do:\n - 1.View All Courses\n - 2.Enroll(Pick) New Course\n - 3.Drop Course\n - 4.View Enrolled Course Details\n - 5.Change Password\n - 6.Exit from this menu\n";

            send(clientSocket, adminPrompt, strlen(adminPrompt), 0);
            // readBytes store no of bytes read from the client by the server
            ssize_t readBytes = recv(clientSocket, readbuff, sizeof(readbuff), 0);
            if (readBytes == -1)
            {
                perror("Error in the choice you provided");
                return false;
            }
            int choice = atoi(readbuff);
            // send(clientSocket,readbuff,sizeof(readbuff),0);

            switch (choice)
            {
            case 1:
                if (!viewAllCourses(clientSocket,auth))
                    continue;
                break;
            case 2:
                if (!enrollNewCourse(clientSocket,auth))
                    continue;
                break;
            case 3:
                if (!dropCourse(clientSocket,auth))
                    continue;
                break;
            case 4:
                if (!viewEnrolledCourseDetails(clientSocket,auth))
                    continue;
                break;
            case 5:
                if (!changeStudentPassword(clientSocket))
                    continue;
                break;
            default:
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}