struct site
{
    int id;
    char sitename[50];
    char username[50];
    char password[50];
};

char * genRandPwd(int);
void viewPassWords();// The built in functionality is cumbersome. This allows auto-completion
void storeNewCombo();
void modUnamePwd();
void delete();
void rmWhtSpcEndStr(char []);
