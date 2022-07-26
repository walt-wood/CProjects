#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include  "menuFunctions.h"

char * genRandPwd(int length) {
    char * randStr;
	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_+=?!@$^&*%<>~";

	if (length) {
		srand((unsigned int) (time(NULL)));
		randStr = (char *) malloc((char) sizeof(char) * length);

		if (randStr) {
			int l = (int) (sizeof (charset) - 1);
			int key;
			for(int inx = 0; inx < length; inx++) {
				key = rand() % l;
				randStr[inx] = charset[key];
			}

			randStr[length] = '\0';
		}
	}

	printf("%s\n", randStr);
	getchar();

	
	return randStr;
} 

void viewPassWords() {

	FILE * fPtr;
	fPtr = fopen("passwords.txt", "r");
	char sName[50];
	char uName[50];
	char pWord[50];
	int id = -1;

	printf("Sitename                       | Username                       | Password                    \n");
	printf("----------------------------------------------------------------------------------------------\n");
	while(fscanf(fPtr, "%d %s %s %s", &id, sName, uName, pWord) != EOF) {
		rmWhtSpcEndStr(sName);
		rmWhtSpcEndStr(uName);
		rmWhtSpcEndStr(pWord);
		printf("%-30s | %-30s | %-30s\n", sName, uName, pWord);
	}
	getchar();
	fclose(fPtr);

}

void storeNewCombo() {

    struct site newSite, parseSite;
    
    printf("Sitename: ");
    fgets(newSite.sitename , 50, stdin);    
    printf("Username: ");
    fgets(newSite.username , 50, stdin);
    printf("Password: ");
    fgets(newSite.password, 50, stdin);

    FILE * fPtr;
    fPtr = fopen("passwords.txt", "r");

    // get last index in file
    while(fscanf(fPtr, "%d %s %s %s", &parseSite.id, parseSite.sitename, parseSite.username, parseSite.password) != EOF);
    // increment id
    fclose(fPtr);
    fPtr = fopen("passwords.txt", "a");
    newSite.id = parseSite.id + 1;
    rmWhtSpcEndStr(newSite.sitename);
    rmWhtSpcEndStr(newSite.username);
    rmWhtSpcEndStr(newSite.password);
    fprintf(fPtr, "%d %s %s %s\n", newSite.id, newSite.sitename, newSite.username, newSite.password);
    fclose(fPtr);
}

void rmWhtSpcEndStr(char str[]) {
    str[strcspn(str, "\r\n")] = 0;
}