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
void simplify_AST(struct Tree *AST);

/* helper functions */
void set_func(struct Tree *node, char f);
struct Tree *copy_tree(struct Tree *tree);
void switch_up(struct Tree *AST, int is_left);
void eval_node(struct Tree *AST);
int is_defx(struct Tree *AST);
void set_node(struct Tree *AST, float val);

/* tester functions */
void print_AST(struct Tree *AST);

