all : main

main : cminus.tab.o lex.yy.o main.o util.o buildSymtab.o symtab.o analyze.o cgen.o code.o
	gcc -o project4_6 cminus.tab.o lex.yy.o main.o util.o buildSymtab.o symtab.o analyze.o cgen.o code.o -ly -lfl

cminus.tab.c cminus.tab.h cminus.output: cminus.y
	bison -d -v cminus.y

lex.yy.c: cminus.l
	lex cminus.l

main.o : main.c
	gcc -c main.c -Wall

util.o: util.c
	gcc -c util.c -Wall

buildSymtab.o: buildSymtab.c
	gcc -c buildSymtab.c -Wall

symtab.o: symtab.c
	gcc -c symtab.c -Wall

lex.yy.o: cminus.tab.c cminus.tab.h lex.yy.c
	gcc -c cminus.tab.c lex.yy.c -ly -ll

analyze.o: analyze.c analyze.h
	gcc -c analyze.c -Wall

code.h: code.c code.h
	gcc -c code.c -Wall

cgen.o: cgen.c cgen.h
	gcc -c cgen.c -Wall

clean : 
	rm -f *.o lex.yy.c cminus.tab.c cminus.tab.h cminus.output project4_6

