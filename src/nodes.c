#include <stdlib.h>
#include <stdio.h>
#include "nodes.h"

/* create node: CONSTANT */
node *constant_n(int value) {
	node *p;

	/* allocate size of the node */
	if ((p = malloc(sizeof(node))) == NULL)
		printf("out of memory");

	/* store information */
	p->type = constant_t;
	p->con.value = value;
	return p;
}

/* create node: ADD */
node *add_n(node *child1, node *child2) {
	node *p;

	/* allocate size of the node */
	if ((p = malloc(sizeof(node))) == NULL)
		printf("out of memory");

	/* store information */
	p->type = add_t;
	p->add.child1 = child1;
	p->add.child2 = child2;
	return p;
}

/* create node: PRINT */
node *print_n(node *child) {
	node *p;

	/* allocate size of the node */
	if ((p = malloc(sizeof(node))) == NULL)
		printf("out of memory");

	/* store information */
	p->type = print_t;
	p->print.child = child;
	return p;
}
