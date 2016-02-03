#include <stdlib.h>
#include <stdio.h>
#include "nodes.h"

/* allocate memory for node */
node *nalloc() {
	node *p;
	if ((p = malloc(sizeof(node))) == NULL)
		printf("out of memory");
	return p;
}

/* create node: BODY */
node *body_n(node *child) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* allocate size of new child */
	if ((p->body.children = malloc(sizeof(child))) == NULL)
		printf("out of memory");

	/* store information */
	p->type = body_t;
	p->body.children[0] = child;
	p->body.count = 1;
	return p;
}

/* push new node to body */
void body_push(node *p, node *child) {

	/* reallocate size of pointer array */
	if ((p->body.children = realloc(p->body.children, 
	  (p->body.count + 1) * sizeof(child))) == NULL)
		printf("out of memory");

	/* append new child */
	p->body.children[p->body.count++] = child;
}

/* create node: CONSTANT */
node *constant_n(int value) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* store information */
	p->type = constant_t;
	p->con.value = value;
	return p;
}

/* create node: IF */
node *if_n(node *cond, node *body) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* store information */
	p->type = if_t;
	p->ifno.cond = cond;
	p->ifno.body = body;
	return p;
}

/* create node: PRINT */
node *print_n(node *child) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* store information */
	p->type = print_t;
	p->print.child = child;
	return p;
}

/* create node: ADD */
node *add_n(node *child1, node *child2) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* store information */
	p->type = add_t;
	p->add.child1 = child1;
	p->add.child2 = child2;
	return p;
}

/* create node: SUBTRACT */
node *subtract_n(node *child1, node *child2) {
	node *p;

	/* allocate size of the node */
	p = nalloc();

	/* store information */
	p->type = subtract_t;
	p->sub.child1 = child1;
	p->sub.child2 = child2;
	return p;
}

