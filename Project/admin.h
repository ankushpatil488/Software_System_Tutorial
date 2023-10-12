/*#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS
*/
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
#include "structure.h"

int authenticateadmin(int clientSocket)
{
    char username[100];
    char pass[100];

    // Send a prompt for the username
    const char *userPrompt = "\nEnter Username of Admin: ";
    send(clientSocket, userPrompt, strlen(userPrompt), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(clientSocket, username, sizeof(username), 0);
    if (bytesRead <= 0)
    {
        close(clientSocket);
        return false;
    }
    if (username[bytesRead - 1] == '\n')
    {
        username[bytesRead - 1] = '\0';
    }
    else
    {
        username[bytesRead] = '\0';
    }

    // Send a prompt for the password
    const char *passPrompt = "\nEnter password of the Admin: ";
    send(clientSocket, passPrompt, strlen(passPrompt), 0);

    // Receive the password from the client
    bytesRead = recv(clientSocket, pass, sizeof(pass), 0);
    if (bytesRead <= 0)
    {
        close(clientSocket);
        return false;
    }
    if (pass[bytesRead - 1] == '\n')
    {
        pass[bytesRead - 1] = '\0';
    }
    else
    {
        pass[bytesRead] = '\0';
    }

    // Compare the received username and password with stored credentials
    if (strcmp(username, adminCredentials.username) == 0 &&
        strcmp(pass, adminCredentials.pass) == 0)
    {
        // Authentication successful
        send(clientSocket, "Authentication successful\n", strlen("Authentication successful\n"), 0);
        return true;
    }
    else
    {
        // Authentication failed
        send(clientSocket, "Authentication failed\n", strlen("Authentication failed\n"), 0);
        close(clientSocket);
        return false;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to send a prompt to the client and receive a response
int sendPromptAndReceiveResponse(int clientSocket, const char *prompt, char *response, size_t responseSize)
{
    send(clientSocket, prompt, strlen(prompt), 0);
    ssize_t bytes_received = recv(clientSocket, response, responseSize - 1, 0);

    if (bytes_received <= 0)
    {
        perror("recv");
        return -1;
    }

    response[bytes_received] = '\0'; // Null-terminate the received string
    if (response[bytes_received - 1] == '\n')
    {
        response[bytes_received - 1] = '\0';
    }

    return 0; // Success
}

int addStudent(int clientSocket)
{
    struct student stud;

    if (sendPromptAndReceiveResponse(clientSocket, "Enter Student Name: ", stud.name, sizeof(stud.name)) == -1)
    {
        close(clientSocket);
        return 0;
    }

    if (sendPromptAndReceiveResponse(clientSocket, "Enter Student LoginId: ", stud.loginId, sizeof(stud.loginId)) == -1)
    {
        close(clientSocket);
        return 0;
    }

    if (sendPromptAndReceiveResponse(clientSocket, "Enter Student Password: ", stud.password, sizeof(stud.password)) == -1)
    {
        close(clientSocket);
        return 0;
    }

    if (sendPromptAndReceiveResponse(clientSocket, "Enter Student Age: ", stud.age, sizeof(stud.age)) == -1)
    {
        close(clientSocket);
        return 0;
    }

    if (sendPromptAndReceiveResponse(clientSocket, "Enter Student Email Address: ", stud.emailAddress, sizeof(stud.emailAddress)) == -1)
    {
        close(clientSocket);
        return 0;
    }

    int openFD = open("student_database.txt", O_RDWR | O_CREAT | O_APPEND, 0644); // Open the file in append mode

    if (openFD == -1)
    {
        perror("open");
        close(clientSocket);
        return 0;
    }

    lseek(openFD, 0, SEEK_END);
    ssize_t bytes_written = write(openFD, &stud, sizeof(stud));

    if (bytes_written == -1)
    {
        perror("write");
        close(openFD);
        close(clientSocket);
        return 0;
    }

    close(openFD);

    // Optionally, you can send a success message to the client.
    const char successMessage[] = "Student added successfully...\n";
    send(clientSocket, successMessage, strlen(successMessage), 0);

    return 1; // Success
}

int customStrCmp(const char *str1, const char *str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

int viewStudentDetails(int clientSocket)
{
    struct student my_student, temp;
    int openFD = open("student_database.txt", O_RDONLY, 0644); // Open in read-only mode

    if (openFD == -1)
    {
        perror("Error opening file");
        return 0;
    }
    bool found = false; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data
    send(clientSocket, "Enter Student ID: ", strlen("Enter Student ID: "), 0);
    int readResult = read(clientSocket, my_student.loginId, sizeof(my_student.loginId) - 1);

    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student ID from server", strlen("Error receiving student ID from server"), 0);
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
        // Construct the details message
        sprintf(buffer, "...................Student..................\nName: %s\nAge: %s\nLogin ID: %s\nPassword: %s\nEmail Address: %s\n.............................................\n",
                temp.name, temp.age, temp.loginId, temp.password,temp.emailAddress);

        // Send the details to the client
        send(clientSocket, buffer, strlen(buffer), 0);
        return 1;
    }
    else
    {
        send(clientSocket, "Student not found\n", strlen("Student not found\n"), 0);
        return 0;
    }
    close(openFD);
    return 0; // Close the file after use
}
int updateDetails(int clientSocket)
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
    send(clientSocket, "Enter Student ID for updation of data: ", strlen("Enter Student ID for updation of data: "), 0);
    int readResult = read(clientSocket, my_student.loginId, sizeof(my_student.loginId) - 1);

    if (readResult <= 0)
    {
        send(clientSocket, "Error receiving student ID from server", strlen("Error receiving student ID from server"), 0);
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
        // Construct the details message
        sprintf(buffer, "...................Student..................\n...................Original Details ..................\nName: %s\nAge: %s\nLogin ID: %s\nPassword: %s\nEmail Address: %s\n.............................................\n",
                temp.name, temp.age, temp.loginId, temp.password,temp.emailAddress);

        // Send the details to the client
        send(clientSocket, buffer, strlen(buffer), 0);
        
        send(clientSocket, "Enter Student Name to update: ", strlen("Enter Student Name to update: "), 0);
        readResult = read(clientSocket, temp.name, sizeof(temp.name) - 1);
        send(clientSocket, "Enter password to update: ", strlen("Enter password to update: "), 0);
        readResult = read(clientSocket, temp.password, sizeof(temp.password) - 1);
        send(clientSocket, "Enter Age to update: ", strlen("Enter Age to update: "), 0);
        readResult = read(clientSocket, temp.age, sizeof(temp.age) - 1);
        send(clientSocket, "Enter Email Address to update: ", strlen("Enter Email Address to update: "), 0);
        readResult = read(clientSocket, temp.emailAddress, sizeof(temp.emailAddress) - 1);

        lseek(openFD,-sizeof(struct student),SEEK_CUR);
        memset(&my_student, 0, sizeof(struct student));
        write(openFD,&temp,sizeof(temp));

        sprintf(buffer, "...................Student..................\n...................Updated Details ..................\nName: %s\nAge: %s\nLogin ID: %s\nPassword: %s\nEmail Address: %s\n.............................................\n",
                temp.name, temp.age, temp.loginId, temp.password,temp.emailAddress);
        
        // Send the details to the client
        send(clientSocket, buffer, strlen(buffer), 0);

        return 1;
    }
    else
    {
        send(clientSocket, "Student not found\n", strlen("Student not found\n"), 0);
        return 0;
    }
    close(openFD);
    return 0; // Close the file after use
}
/*
int addStudent(int clientSocket){
    struct student stud;

    int openFD = open("student_database.txt", O_RDWR | O_CREAT | O_APPEND , 0644); // Provide appropriate permissions

    if (openFD == -1) {
        perror("open");
        close(clientSocket);
        return 0;
    }


    send(clientSocket, "Enter Student Name: ", strlen("Enter Student Name: "), 0);
    ssize_t bytes_received = recv(clientSocket, stud.name, strlen(stud.name) - 1, 0);

    if (bytes_received == -1) {
        perror("recv");
        close(openFD);
        close(clientSocket);
        return 0;
    }
    stud.name[bytes_received] = '\0'; // Null-terminate the received string
    if (stud.name[bytes_received - 1] == '\n')
    {
        stud.name[bytes_received - 1] = '\0';
    }

    send(clientSocket, "Enter Student LoginId: ", strlen("Enter Student LoginId: "), 0);
    bytes_received = recv(clientSocket, stud.loginId, strlen(stud.loginId) - 1, 0);

    if (bytes_received == -1) {
        perror("recv");
        close(openFD);
        close(clientSocket);
        return 0;
    }
    stud.loginId[bytes_received] = '\0'; // Null-terminate the received string
    if (stud.loginId[bytes_received - 1] == '\n')
    {
        stud.loginId[bytes_received - 1] = '\0';
    }

    send(clientSocket, "Enter Student Password: ", strlen("Enter Student Password: "), 0);
    bytes_received = recv(clientSocket, stud.password, strlen(stud.password) - 1, 0);

    if (bytes_received == -1) {
        perror("recv");
        close(openFD);
        close(clientSocket);
        return 0;
    }
    stud.password[bytes_received] = '\0'; // Null-terminate the received string
    if (stud.password[bytes_received - 1] == '\n')
    {
        stud.password[bytes_received - 1] = '\0';
    }

    send(clientSocket, "Enter Student Age: ", strlen("Enter Student Age: "), 0);
    bytes_received = recv(clientSocket, stud.age, strlen(stud.age) - 1, 0);

    if (bytes_received == -1) {
        perror("recv");
        close(openFD);
        close(clientSocket);
        return 0;
    }
    stud.age[bytes_received] = '\0'; // Null-terminate the received string
    if (stud.age[bytes_received - 1] == '\n')
    {
        stud.age[bytes_received - 1] = '\0';
    }

    send(clientSocket, "Enter Student Email Address: ", strlen("Enter Student Email Address: "), 0);
    bytes_received = recv(clientSocket, stud.emailAddress, strlen(stud.emailAddress) - 1, 0);

    if (bytes_received == -1) {
        perror("recv");
        close(openFD);
        close(clientSocket);
        return 0;
    }
    stud.emailAddress[bytes_received] = '\0'; // Null-terminate the received string
    if (stud.emailAddress[bytes_received - 1] == '\n')
    {
        stud.emailAddress[bytes_received - 1] = '\0';
    }

    lseek(openFD, 0, SEEK_END);
    ssize_t bytes_written = write(openFD, &stud, sizeof(stud));

    if (bytes_written == -1) {
        perror("write");
        close(openFD);
        close(clientSocket);
        return 0;
    }

    close(openFD);

    // Optionally, you can send a success message to the client.
    const char successMessage[] = "Student added successfully.\n";
    send(clientSocket, successMessage, strlen(successMessage), 0);
}
*/
// return 1 if login successfully else 0
int admin_functionality(int clientSocket)
{
    if (authenticateadmin(clientSocket))
    {

        char readbuff[1000], writebuff[1000]; // A buffer used for reading & writing to the client
        int a;
        while (1)
        {
            if (a == 1)
            {
                send(clientSocket, "Login Successfully\n", strlen("Login Successfully\n"), 0);
                a = 0;
            }
            char adminPrompt[] = "\nAdmin can Do:\n - 1.Add Student\n - 2.Add Faculty\n -3.View Details\n- 4.Deactivate Student\n - 5. Deactivate Faculty\n - 6. Update Student\n - 7. Update Faculty\n - 8.Exit from this menu\n";

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
                if (!addStudent(clientSocket))
                    continue;
                break;
            case 3:
                if (!viewStudentDetails(clientSocket))
                    continue;
                break;
            case 6:
                if (!updateDetails(clientSocket))
                    continue;
                break;
            default:
                break;
            }
        }
    }
    else
    {
        return 0;
    }
}
