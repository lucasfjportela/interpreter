#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

void yyerror(char*);
int yyparse(void);
int eval(node *p);

int main(int argc, char** argv) {

	extern FILE *yyin; 
	extern FILE *yyout; 
	extern int yyparse(void);

	/* check for file parameter */
	if (argc != 2) {
		printf("Usage: parser FILENAME\n");
		return 1;
	}

	/* open file stream */
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Could not open file.");
		return 1;
	}

	/* parse from stream */
	yyin = file;
	yyparse();
	fclose(file);

	return 0;
}

/* evaluate node */
int eval(node *p) {

	if (!p) return 0;
	switch(p->type) {
		case constant_t: return p->con.value; break;
		case print_t: printf("%d\n", eval(p->print.child)); break;
		case add_t: return eval(p->add.child1) + eval(p->add.child2); break;
	}
}

void yyerror(char* error) {
	printf("Parser ERROR: %s\n", error);
}
int yywrap(void) {}
