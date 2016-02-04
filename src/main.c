#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

void yyerror(char*);
int yyparse(void);
int eval(node *p);
void free_body(node *p);


int main(int argc, char** argv) {

	extern FILE *yyin; 
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
	int i, a, b;

	if (!p) return 0;
	switch(p->type) {

		/* body node */
		case body_t:
			for (i = 0; i < p->body.count; i++)
				eval(p->body.children[i]);
			free(p->body.children);
			free(p);
			break;

		/* constant node */ 
		case constant_t:
			return p->con.value;

		/* if node */
		case if_t:
			if (eval(p->ifno.cond))
				eval(p->ifno.body);
			else
				free_body(p->ifno.body);
			free(p->ifno.cond);
			free(p);
			break;

		/* print node */ 
		case print_t:
			printf("%d\n", eval(p->print.child));
			free(p->print.child);
			free(p);
			break;

		/* add node */ 
		case add_t:
			a = eval(p->add.child1); 
			b = eval(p->add.child2);
			free(p->add.child1);
			free(p->add.child2);
			return a + b;

		/* subtract node */ 
		case subtract_t:
			a = eval(p->sub.child1); 
			b = eval(p->sub.child2);
			free(p->sub.child1);
			free(p->sub.child2);
			return a - b;
	}

	return 0;
}

/* free body */
void free_body(node *p) {
	int i;
	node *cp;

	if (!p) return;

	/* literate over children */
	for (i = 0; i < p->body.count; i++) {
		cp = p->body.children[i];
		switch(cp->type) {
			case print_t:
				free(cp->print.child);
				free(cp);
				free(p);
				break;
			case if_t:
			case body_t:
			case constant_t:
			case add_t:
			case subtract_t: break;
		}
	}
}

void yyerror(char* error) {
	printf("Parser ERROR: %s\n", error);
}
