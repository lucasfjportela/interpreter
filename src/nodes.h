/* node type */
typedef enum {
	constant_t,
	print_t,
	add_t
} nodeType;

/* constant */
typedef struct {
	int value;           /* value */
} constantNode;

/* add */
typedef struct {
	struct Node *child1; /* 1st child node */
	struct Node *child2; /* 2nd child node */
} addNode;

/* print */
typedef struct {
	struct Node *child;  /* child node */
} printNode;

/* node */
typedef struct Node {
	nodeType type;       /* type from enum    */
	union {              /* struct from above */
		constantNode con;
		addNode add;
		printNode print;
	};
} node;

node *constant_n(int value);
node *add_n(node *child1, node *child2);
node *print_n(node *child);
int eval(node *p);
