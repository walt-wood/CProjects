# If next line commented, use make debug G="-ggdb" for line numbers in GDB.
#G=-ggdb
CFLAGS=-std=c11 $G -Wall -fmax-errors=10 -Wextra

PassMan: PassMan.o menu.o
	gcc $G $(CFLAGS) PassMan.o menu.o -o PassMan

PassMan.o: main.c menu.h
	gcc $G $(CFLAGS) -c main.c -o PassMan.o

menu.o: menu.c
	gcc $G $(CFLAGS) -c menu.c -o menu.o

launch: PassMan	
	./PassMan

debug: PassMan	
	gdb -q PassMan

clean:
	rm *.o PassMan

git:
	git add .
	git commit -m "$m"
	git push
