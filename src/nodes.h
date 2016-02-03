/* node type */
typedef enum {
  body_t,
	constant_t,
	if_t,
	print_t,
	add_t,
	subtract_t,
} nodeType;

/* body */
typedef struct {
	struct Node **children;
	int count;
} bodyNode;

/* constant */
typedef struct {
	int value;
} constantNode;

/* if */
typedef struct {
	struct Node *cond;
  struct Node *body; 
} ifNode;

/* print */
typedef struct {
	struct Node *child;
} printNode;

/* add */
typedef struct {
	struct Node *child1;
	struct Node *child2;
} addNode;

/* subtract */
typedef struct {
	struct Node *child1;
	struct Node *child2;
} subtractNode;

/* node */
typedef struct Node {
	nodeType type;       /* type from enum    */
	union {              /* struct from above */
		bodyNode body;
		constantNode con;
		ifNode ifno;
		printNode print;
		addNode add;
		subtractNode sub;
	};
} node;

/* function declarations */
node *body_n(node *child);
node *constant_n(int value);
node *if_n(node *cond, node *body);
node *print_n(node *child);
node *add_n(node *child1, node *child2);
node *subtract_n(node *child1, node *child2);
void body_push(node *body, node *child);
int eval(node *p);
