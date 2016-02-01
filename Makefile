run all: parser

parser: grammar lex
	gcc -c lex.yy.c grammar.tab.c
	gcc -o interpreter src/main.c src/nodes.c grammar.tab.o lex.yy.o 
	@echo "================================================================";
	@rm grammar.tab.c grammar.tab.h lex.yy.c
	@rm grammar.tab.o lex.yy.o
	@./interpreter example.source

grammar:
	bison -d ./src/grammar.y

lex:
	flex ./src/lex.l
