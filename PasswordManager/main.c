// Log in function
// Generate random password of given length
// View all the stored Username-Password combinations for a particular user.
// Store a Username-Password combination for a site
    // Store hash not text of pw
// Modify a previously stored Username-Password combination
// Delete record
// Modify master username and password

    // Features to add 
        // 1. Button debouncing (press f1 for options);
        // 2. Hashing names and passwords
        // 3. Database for passwords and usernames
        // 4. Max login attempts
        // 5. Login feedback: The password or username was incorrect
        // 6. Command line arguments?


#include <stdio.h>
#include <stdlib.h>
#include "menuFunctions.h"
#include <string.h>

struct site
{
    int id;
    char sitename[50];
    char username[50];
    char password[50];
};

static void printMenu(int, char **);
static void createRandPW(char[], char *);
static void getNameAndPass(char[], char[]);
static void firstLogin(struct site);
static void initialLogin();
// Need to remove white space at the end of strings for comparing
// The build in function is cumbersome to type and this allows auto-completion
void rmWhtSpcEndStr(char []);


int main (void) {
        
    initialLogin();
    
    char * options[7] = {
        "1. Generate random password",
        "2. View all stored usernames and passwords",
        "3. Store username and password for site",
        "4. Modify username or password",
        "5. Delete record",
        "6. Modify master username or password",
        "7. Exit"
    };

    int selection = 0;
    int numOptions = 7;
    char *selInPtr;
    char selInput[10];

    do {
        system("cls");
        printMenu(numOptions, options);
        fgets(selInput, 10, stdin);
        selection = (int) strtol(selInput, &selInPtr, 10);
        system("cls");

        switch (selection)
        {            
        case 1:
            createRandPW(selInput, selInPtr);
            break;
        case 2:
            viewPassWords();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:            
            break;
        }

    } while(selection != 7);

    // free randStr
}

static void printMenu(int numOptions, char * options[]) {
    // Assumes user has loggin in to pw manager
    for(int i = 0; i < numOptions; i++) {
        printf("%s\n", options[i]);
    }
}

static void createRandPW(char selInput[], char *selInPtr) {
    printf("Enter length for random password: ");
    fgets(selInput, 10, stdin);
    int pwLen = (int) strtol(selInput, &selInPtr, 10);
    genRandPwd(pwLen);
}

static void getNameAndPass(char username[], char password[]) {

    printf("Enter username: ");
    fgets(username, 50, stdin);    
    printf("Enter password: ");
    fgets(password, 50, stdin);
    rmWhtSpcEndStr(username);
    rmWhtSpcEndStr(password);

}

static void firstLogin(struct site root) {

    FILE *fPtr = fopen("passwords.txt", "w");
    system("cls");

    printf("You have not set up a root login.\nPlease enter a username: ");
    fgets(root.username, 50, stdin);
    // Have to remove \n from end of string, so it's not printed in the file.
    rmWhtSpcEndStr(root.username);
    printf("Please enter password: ");
    fgets(root.password, 50, stdin);
    // Do not remove white space here, b/c we want to go to next line of file.
    // Manually set root.id, so it is ALWAYS 0
    root.id = 0;
    // Manually set root.sitename
    snprintf(root.sitename, 50, "%s", "root");
    fprintf(fPtr, "%d %s %s %s", root.id, root.sitename, root.username, root.password);
    fclose(fPtr);
}

static void initialLogin() {
    struct site newSite, rootLogin;

    //rootLogin.id = 0;
    FILE *filePtr;
    char *fileName = "passwords.txt";


    filePtr = fopen(fileName, "r");
    fscanf(filePtr, "%d %s %s %s\n", &rootLogin.id, rootLogin.sitename, rootLogin.username, rootLogin.password);
    char enteredRootUName[50];
    char enteredRootPW[50];
    if(rootLogin.id == 0 && strcmp(rootLogin.username, "root") == 0) { // Root already created since we read 0 from file
        
        // Check root login credentials
        
        rmWhtSpcEndStr(rootLogin.username);
        rmWhtSpcEndStr(rootLogin.password);
        do {
            system("cls");
            // Need to add valid input check
            getNameAndPass(enteredRootUName, enteredRootPW);
        } while(strcmp(rootLogin.username, enteredRootUName) || strcmp(enteredRootPW, rootLogin.password));
        fclose(filePtr);
        
    } else {
        // create root login
        // rewind(filePtr);    // Go back to start of file
        // Same file opens in firstLogin
            // Need to close file
            // Not sure this is good way to do it
        fclose(filePtr);
        firstLogin(rootLogin);
    }
}

void rmWhtSpcEndStr(char str[]) {
    str[strcspn(str, "\r\n")] = 0;
}