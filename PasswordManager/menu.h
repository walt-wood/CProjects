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
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RST   "\x1B[0m"

void genRandPwd(int);
void viewPassWords();
void storeNewCombo();
void modUnamePwd(int index);
void delete();
void rmWhtSpcEndStr(char []);
