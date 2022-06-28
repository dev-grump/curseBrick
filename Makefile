all: curseBrick

curseBrick: curseBrick.c colaCrd.o
	gcc -Wall -o -lncurses curseBrick curseBrick.c colaCrd.o

colaCrd.o: colaCrd.c colaCrd.h
	gcc -Wall -c  -lncurses colaCrd.c

clean:
	rm curseBrick colaCrd.o 