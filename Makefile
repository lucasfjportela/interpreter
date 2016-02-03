debug: all
	valgrind --leak-check=full ./interpreter example/example.source

run: all 
	@./interpreter ./example/example.source

all: parser

parser: grammar lex
	gcc -Wall -c lex.yy.c grammar.tab.c
	gcc -Wall -g -o interpreter src/main.c src/nodes.c grammar.tab.o lex.yy.o 
	@echo "================================================================";
	@rm grammar.tab.c grammar.tab.h lex.yy.c
	@rm grammar.tab.o lex.yy.o


grammar:
	bison -d ./src/grammar.y

lex:
	flex ./src/lex.l
