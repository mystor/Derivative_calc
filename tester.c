#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"

struct Tree *make_tree();

int main(){
    struct Tree *tree = make_tree();
    struct Tree *foo = derivative(tree);
    free_tree(foo);
    free_tree(tree);
    return 0;
}

/* Makes the AST of f(x) = 2x +3 */
struct Tree *make_tree(){
    struct Tree *node = malloc(sizeof(struct Tree));
    set_func(node, '+');
    node->left = malloc(sizeof(struct Tree));
    node->right = malloc(sizeof(struct Tree));
    node->left->left = malloc(sizeof(struct Tree));
    node->left->right = malloc(sizeof(struct Tree));
    node->right->node_type = NUM;
    node->right->this.num = 3;
    set_func(node->left, '*');
    node->left->left->node_type = NUM;
    node->left->left->this.num = 2;
    node->left->right->node_type = VAR;
    node->left->right->this.var = 1;
    return node;
}
