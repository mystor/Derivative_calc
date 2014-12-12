#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"

struct Tree *make_tree();

int main(){
    struct Tree *tree = make_tree();
    struct Tree *foo = derivative(tree);
    printf("Original Equation:     ");
    print_AST(tree);
    printf("\nRaw from derivative:   ");

    print_AST(foo);
    printf("\nAfter Simplify:        ");
    simplify_AST(foo);
    simplify_AST(foo);
    simplify_AST(foo);
    print_AST(foo);
    printf("\n");

    free_tree(foo);
    free_tree(tree);
    return 0;
}

/* Makes the AST of f(x) = 2x +3 */
struct Tree *make_tree(){
    struct Tree *node = calloc(1, sizeof(struct Tree));
    set_func(node, '+');
    node->left = calloc(1, sizeof(struct Tree));
    node->right = calloc(1, sizeof(struct Tree));
    node->left->left = calloc(1, sizeof(struct Tree));
    node->left->right = calloc(1, sizeof(struct Tree));
    node->right->node_type = NUM;
    node->right->this.num = 3;
    set_func(node->left, '^');
    node->left->left->node_type = VAR;
    node->left->left->this.num = 1;
    node->left->right->node_type = NUM;
    node->left->right->this.num = 3;
    return node;
}
