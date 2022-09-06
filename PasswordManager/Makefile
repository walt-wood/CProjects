PassMan: PassMan.o menu.o
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra PassMan.o menu.o -o PassMan

PassMan.o: main.c menu.h
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra -c main.c -o PassMan.o

menu.o: menu.c
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra -c menu.c -o menu.o

launch: PassMan
	./PassMan

debug:
	gdb -q PassMan

clean:
	rm *.o PassMan

git:
	git add .
	git commit -m "$m"
	git push
