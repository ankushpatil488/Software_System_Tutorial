#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include"structure.h"
int customStrCmp(const char *str1, const char *str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

int main() {
    char *auth,*cid;
    strcpy(auth,"cid3");
    struct Course my_course, temp;
    int openFD = open("course_database.txt", O_RDWR, 0644); // Open in read-only mode

    if (openFD == -1)
    {
        perror("Error opening file");
        return 0;
    }
    int found = 0; // Initialize found to false
    char buffer[1024];  // Declare buffer for sending data
    printf("Enter Course ID to Remove: ");
    scanf("%s",cid);
    //my_course.cid[readResult] = '\0';
    
    // Reset the file pointer to the beginning of the file
    lseek(openFD, 0, SEEK_SET);
    printf("Auth %s ",auth);
    strcpy(my_course.proffesor_id,auth);
    // Loop to search for the student in the file
    while (read(openFD, &temp, sizeof(temp)) > 0)
    {
        if((customStrCmp(my_course.cid, temp.cid) == 0) && (customStrCmp(my_course.proffesor_id, temp.proffesor_id) == 0)&& customStrCmp(temp.active,"1"))
        { // Compare the student IDs
            found = 1;
            printf("Active %s",temp.active);
            strcpy(temp.active,"0");
            printf("Active %s",temp.active);
            break;
        }
    }
    
    lseek(openFD,-sizeof(struct Course),SEEK_CUR);
    size_t bytesWrite=write(openFD,&temp,sizeof(temp));
    if(bytesWrite==-1){
        perror("Error while removing course");
        close(openFD);
        return 0;
    }
    if (found)
    {
        printf("Removed the course from catalog");
    }
    else
    {
        printf("Course not found\n");
  
    }
    return 0; 
}
