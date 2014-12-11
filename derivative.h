/* 
   Header for derivative calculator
 */

enum this_node_type {
    FUNC = 0,
    NUM = 1,
    VAR = 2
};

struct Tree {
    enum this_node_type node_type;
    union this_node {
        char func;
        float num;
        int var; // acts as bool; only one variable
    } this;
    struct Tree * left;
    struct Tree * right;
};

/* core functions */
struct Tree *derivative(struct Tree *orig);
void free_tree(struct Tree *tree);

/* helper functions */
void set_func(struct Tree *node, char f);
struct Tree *copy_tree(struct Tree *tree);
    
/* tester functions */
void print_AST(struct Tree *AST);

