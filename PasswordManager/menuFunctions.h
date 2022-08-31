struct site
{
    int id;
    char sitename[50];
    char username[50];
    char password[50];
};

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define MAG   "\x1B[35m"
#define RST "\x1B[0m"

char * genRandPwd(int);
void viewPassWords();// The built in functionality is cumbersome. This allows auto-completion
void storeNewCombo();
void modUnamePwd(int index);
void delete();
void rmWhtSpcEndStr(char []);
