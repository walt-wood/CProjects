// Log in function
// Generate random password of given length
// View all the stored Username-Password combinations for a particular user.
// Store a Username-Password combination for a site
    // Store hash not text of pw
// Modify a previously stored Username-Password combination
// Delete record
// Modify master username and password

    // Features to add 
        // Button debouncing (press f1 for options);
        // Hashing names and passwords
        // Database for passwords and usernames
        // Max login attempts
        // Login feedback: The password or username was incorrect
        // Command line arguments?
        // Add pointer and malloc for variable length strings
            // This implementation has some serious limitations
        // - Add pattern to password generator, so passwords are easier to remember.
            // Th1s!S@p@ssW0Rd*
    // Code improvements
    //    1. Use varaible length strings when applicable.
    //    2. There is too much repeated code. It needs to be modularized.
    //    3. Add color to output

// To-Do
// 1. Valid input checks throughout
// 2. Test code for valid input checks
//      a. Design use cases
// 3. Redesign for better modularization
// 4. Add more color to output
// 5. In firstLogin(), verify password by making user type in twice.
// 6. In option 6, add code for root password check
// 7. Non-repudiation: Keep list of access and/or when root password changed.b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "menu.h"

static void printMenu(int, char **);
static void createRandPW(char[], char *, int);
static void getNameAndPass(char[], char[], int);
static void firstLogin(struct site, int);
static void initialLogin();
static int getModInx();
static void getDelInx();
int fileno(FILE *);

int main (void) {

    const char * clear = "clear";
    initialLogin();
    
    char * options[7] = {
        BLU"1."WHT" Generate random password",
        BLU"2."WHT" View all stored usernames and passwords",
        BLU"3."WHT" Add new username and password for site",
        BLU"4."WHT" Modify username or password",
        BLU"5."WHT" Delete record",
        BLU"6."WHT" Modify master username or password",
        BLU"7."WHT" Exit"RST
    };

    int selection = 0;
    int numOptions = 7;
    char *selInPtr;    
    int buffLen = 10;
    char selInput[10];
    int index = -1;

    do {
        system(clear);
        printMenu(numOptions, options);
        fgets(selInput, sizeof(selInput), stdin);
        selection = (int) strtol(selInput, &selInPtr, buffLen);
        system(clear);

        switch (selection)
        {            
            case 1:
                createRandPW(selInput, selInPtr, buffLen);
                break;
            case 2:
                viewPassWords();
                break;
            case 3:
                storeNewCombo();
                break;
            case 4: 
                index = getModInx();
                if(index > 0) {
                    modUnamePwd(index);
                }        
                break;
            case 5:
                getDelInx();            
                break;
            case 6:
                modUnamePwd(0);
                break;
            default:            
                break;
        }

    } while(selection != 7);
}

static void printMenu(int numOptions, char * options[]) {
    for(int i = 0; i < numOptions; i++) {
        printf("%s\n", options[i]);
    }
}

static void createRandPW(char selInput[], char *selInPtr, int buffLen) {
    const char * clear = "clear";
    int pwLen = -1;

    do {
        system(clear);
        printf("Enter length for random password: ");
        fgets(selInput, 10, stdin);
        pwLen = (int) strtol(selInput, &selInPtr, buffLen);
        if(pwLen < 15) {
            printf("Password should be at least 15 characters, but 26 would be better.\n");
            getchar();
        } else if (pwLen > 999) {
            printf("It would take 5,783,128,169,837,158,197,871 years to break a 26 character password, so anything greater than 999 is unreasonable.\n");
            getchar();
        }
        
    } while(pwLen < 15 || pwLen > 999);
    genRandPwd(pwLen);
}

static void getNameAndPass(char username[], char password[], int buffLen) {
    
    printf("Enter username: ");
    fgets(username, buffLen, stdin);
    printf("Enter password: ");
    
    // Turn off ECHO for stdin
    struct termios old, new;
    tcgetattr(fileno(stdin), &old);
    new = old;
    new.c_lflag &= ~ECHO;    
    tcsetattr(fileno(stdin), TCSAFLUSH, &new);

    fgets(password, buffLen, stdin);

    // Restore ECHO for stdin
    (void) tcsetattr(fileno(stdin), TCSAFLUSH, &old);
    
    rmWhtSpcEndStr(username);
    rmWhtSpcEndStr(password);

}

static void firstLogin(struct site root, int buffLen) {

    const char clear[] = "clear";
    const char* const fileName = "passwords.txt";
    FILE *fPtr = fopen(fileName, "w");
    
    system(clear);
    printf("\nYou have not set up a root login.\nPlease enter a username: ");
    fgets(root.username, buffLen, stdin);
    // Have to remove \n from end of string, so it's not printed in the file.
    rmWhtSpcEndStr(root.username);
    printf("Please enter password: ");
    fgets(root.password, buffLen, stdin);
    // Do not remove white space here, b/c we want to go to next line of file.
    // Manually set root.id, so it is ALWAYS 0
    root.id = 0;
    // Manually set root.sitename
    snprintf(root.sitename, buffLen, "%s", "root");
    fprintf(fPtr, "%d %s %s %s", root.id, root.sitename, root.username, root.password);
    fclose(fPtr);
}

static void initialLogin() {

    struct site rootLogin;

    const char* const fileName = "passwords.txt";

    // if(access(fileName, F_OK)) {
    if(!fopen(fileName, "r")) {
        // file passwords.txt does not exist
        firstLogin(rootLogin, 50);
    
    } else {
        // file does exist
        FILE *filePtr = fopen(fileName, "r"); 
        fscanf(filePtr, "%d %s %s %s\n", &rootLogin.id, rootLogin.sitename, rootLogin.username, rootLogin.password);
        char enteredRootUName[50];
        char enteredRootPW[50];
        int buffLen = 50;
   
        if(rootLogin.id == 0 && strcmp(rootLogin.sitename, "root") == 0) { // Root already created since we read 0 from file
            // file exists and root id established                          
            rmWhtSpcEndStr(rootLogin.username);
            rmWhtSpcEndStr(rootLogin.password);
            do {
                // system("clear");
                // Need to add valid input check
                getNameAndPass(enteredRootUName, enteredRootPW, buffLen);
                printf("\n");
            } while(strcmp(rootLogin.username, enteredRootUName) || strcmp(enteredRootPW, rootLogin.password));
            fclose(filePtr);
            
        } else {
            // file exists but no root id
            firstLogin(rootLogin, buffLen);
        }
        
    }
}

static int getModInx() {
    int index = -1;
    char inBuff[20];
    int buffLen = 20;
    char * inPtr;

    printf("Enter index of entry you wish to change: ");
    fgets(inBuff, buffLen, stdin);
    index = (int) strtol(inBuff, &inPtr, buffLen);

    if(!index) {
        printf("To modify root login, choose option 6 from main menu.");
        getchar();
        index = -1;
    }

    return index;
}

static void getDelInx() {

    int index = -1;
    char inBuff[20];
    int buffLen = 20;
    char * inPtr;

    printf("Enter index of entry to delete: ");
    fgets(inBuff, buffLen, stdin);
    index = (int) strtol(inBuff, &inPtr, buffLen);

    delete(index);
}
