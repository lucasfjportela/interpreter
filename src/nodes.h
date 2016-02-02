/* node type */
typedef enum {
  body_t,
	constant_t,
	print_t,
	add_t,
	subtract_t
} nodeType;

/* body */
typedef struct {
	struct Node **children;
	int count;
} bodyNode;

/* constant */
typedef struct {
	int value;           /* value */
} constantNode;

/* add */
typedef struct {
	struct Node *child1; /* 1st child node */
	struct Node *child2; /* 2nd child node */
} addNode;

/* subtract */
typedef struct {
	struct Node *child1; /* 1st child node */
	struct Node *child2; /* 2nd child node */
} subtractNode;

/* print */
typedef struct {
	struct Node *child;  /* child node */
} printNode;

/* node */
typedef struct Node {
	nodeType type;       /* type from enum    */
	union {              /* struct from above */
		bodyNode body;
		constantNode con;
		addNode add;
		subtractNode sub;
		printNode print;
	};
} node;

node *body_n(node *child);
node *constant_n(int value);
node *add_n(node *child1, node *child2);
node *subtract_n(node *child1, node *child2);
node *print_n(node *child);
void body_push(node *body, node *child);
int eval(node *p);
