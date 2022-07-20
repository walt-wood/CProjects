PasswordManager: PasswordManager.o menuFunctions.o
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra PasswordManager.o menuFunctions.o -o PasswordManager

PasswordManager.o: main.c menuFunctions.h
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra -c main.c -o PasswordManager.o

menuFunctions.o: menuFunctions.c
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra -c menuFunctions.c -o menuFunctions.o

launch: PasswordManager
	./PasswordManager

clean:
	rm *.o PasswordManager