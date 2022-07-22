#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char * genRandPwd(int length) {
    char * randStr;
	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.-_+=':;?!@$^&*/%<>~`";

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

void rmWhtSpcEndStr(char str[]) {
    str[strcspn(str, "\r\n")] = 0;
}