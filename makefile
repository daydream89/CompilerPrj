all : main

main : cminus.tab.o lex.yy.o main.o util.o
	gcc -o 20121590 cminus.tab.o lex.yy.o main.o util.o -ly -lfl

cminus.tab.c cminus.tab.h cminus.output: cminus.y
	bison -d -v cminus.y

lex.yy.c: cminus.l
	lex cminus.l

main.o : main.c
	gcc -c main.c -Wall

util.o: util.c
	gcc -c util.c -Wall


lex.yy.o: cminus.tab.c cminus.tab.h lex.yy.c
	gcc -c cminus.tab.c lex.yy.c -ly -ll

clean : 
	rm -f *.o lex.yy.c cminus.tab.c cminus.tab.h cminus.output 20121590

