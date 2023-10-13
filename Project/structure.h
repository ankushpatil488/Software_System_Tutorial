struct UserCredentials
{
    char username[100];
    char pass[100];
};
struct UserCredentials adminCredentials = {"Ankush", "0125"};

struct student
{
	char loginId[11];
    char password[10];
	char name[30];
    char age[3];
    char emailAddress[25];
};

struct Faculty
{
	char loginId[11];
    char password[10];
	char name[30];
    char dept[30];
    char designation[30];
    char emailAddress[25];
};