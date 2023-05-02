#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "menu.h"

void genRandPwd(int length) {

    // This function assumes input is valid, b/c it is checked in main.c within createRandPW()
    char * randStr;
	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_+=?!@$^&*%<>~";
	
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

    printf("%s\n", randStr);    
    
	getchar();
	free(randStr);
} 

void viewPassWords() {

	FILE * fPtr;
    const char* const fileName = "pwords.bin";
	fPtr = fopen(fileName, "rb");
    struct site readSite;
    
	printf(CYN "Sitename"WHT "                       |"CYN" Username                       "WHT"|"CYN" Password                    \n");
	printf(MAG "----------------------------------------------------------------------------------------------\n" RST);
    while (fread(&readSite, sizeof(readSite), 1, fPtr) == 1) {
		rmWhtSpcEndStr(readSite.sitename);
		rmWhtSpcEndStr(readSite.username);
		rmWhtSpcEndStr(readSite.password);
		printf("%-30s | %-30s | %-30s\n", readSite.sitename, readSite.username, readSite.password);
	}

	fclose(fPtr);
	getchar();
}

void storeNewCombo() {

    struct site newSite, parseSite;
    
    printf("Sitename: ");
    fgets(newSite.sitename, 50, stdin);    
    printf("Username: ");
    fgets(newSite.username, 50, stdin);
    printf("Password: ");
    fgets(newSite.password, 50, stdin);

    rmWhtSpcEndStr(newSite.sitename);
    rmWhtSpcEndStr(newSite.username);
    rmWhtSpcEndStr(newSite.password);

    FILE * fPtr;
    const char* const fileName = "pwords.bin";
    fPtr = fopen(fileName, "rb");

    // get last index in file
    while (fread(&parseSite, sizeof(parseSite), 1, fPtr) == 1);
    fclose(fPtr);
    
    fPtr = fopen(fileName, "ab");

    // increment id
    newSite.id = parseSite.id + 1;
    fwrite(&newSite, sizeof(newSite), 1, fPtr);
    fclose(fPtr);
}

void modUnamePwd(int index) {
            
    struct site newSite, parseSite;  

    if(index) {
        printf("Enter new sitename: ");
        fgets(newSite.sitename, 50, stdin);
    } else {        
        snprintf(newSite.sitename, 50, "%s", "root");
    }

    printf("Enter new username: ");
    fgets(newSite.username, 50, stdin);
    printf("Enter new password: ");
    fgets(newSite.password, 50, stdin);

    rmWhtSpcEndStr(newSite.sitename);
    rmWhtSpcEndStr(newSite.username);
    rmWhtSpcEndStr(newSite.password);
    
    FILE * fPtr,* fPtr2;
    const char* const passFile = "pwords.bin";
    const char* const tmpFile = "temp.txt";

    fPtr = fopen(passFile, "r+b");    
    fPtr2 = fopen(tmpFile, "wb");
    while (fread(&parseSite, sizeof(parseSite), 1, fPtr) == 1) {
        
        rmWhtSpcEndStr(parseSite.sitename);
        rmWhtSpcEndStr(parseSite.username);
        rmWhtSpcEndStr(parseSite.password);
        if(parseSite.id == index) {
            // manually assign the id to index when we reach the point of insertion
            newSite.id = index;
            fwrite(&newSite, sizeof(newSite), 1, fPtr2);
        } else {
            // Otherwise, we store in temp.txt what we found in pwords.bin
            fwrite(&parseSite, sizeof(parseSite), 1, fPtr2);
        }
        
         
    };
    
    fclose(fPtr);
    fclose(fPtr2);
    remove(passFile);
    rename(tmpFile, passFile);

    getchar(); 
}

void delete(int index) {

    if(!index) {
        printf("Cannot delete master password.");
        getchar();
        return;
    }

    const char* const passFile = "pwords.bin";
    const char* const tmpFile = "temp.txt";
    struct site parseSite;
    FILE *fPtr, *fPtr2;

    fPtr = fopen(passFile, "r+b");
    fPtr2 = fopen(tmpFile, "wb");
    while (fread(&parseSite, sizeof(parseSite), 1, fPtr) == 1) {
        
        rmWhtSpcEndStr(parseSite.sitename);
        rmWhtSpcEndStr(parseSite.username);
        rmWhtSpcEndStr(parseSite.password);
        if(parseSite.id < index) {
           fwrite(&parseSite, sizeof(parseSite), 1, fPtr2);
        } else if(parseSite.id > index) {
           parseSite.id--;
           fwrite(&parseSite, sizeof(parseSite), 1, fPtr2);
        }
    };
    
    fclose(fPtr);
    fclose(fPtr2);
    remove(passFile);
    rename(tmpFile, passFile);
}

void rmWhtSpcEndStr(char str[]) {
    str[strcspn(str, "\r\n")] = 0;
}
