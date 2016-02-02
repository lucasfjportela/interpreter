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
	int i;

	if (!p) return 0;
	switch(p->type) {

		/* body node */
		case body_t:
			for (i = 0; i <= p->body.count; i++)
				eval(p->body.children[i]);
			break;

		/* constant node */
		case constant_t:
			return p->con.value;

		/* if node */
		case if_t:
			if (eval(p->ifno.cond))
				eval(p->ifno.body);
			break;

		/* print node */
		case print_t:
			printf("%d\n", eval(p->print.child));
			break;

		/* add node */
		case add_t:
			return eval(p->add.child1) + eval(p->add.child2);

		/* subtract node */
		case subtract_t:
			return eval(p->sub.child1) - eval(p->sub.child2);
	}
}

void yyerror(char* error) {
	printf("Parser ERROR: %s\n", error);
}
int yywrap(void) {}
