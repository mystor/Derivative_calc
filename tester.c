#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"

int main() {
    struct Tree *t = (struct Tree *) malloc(sizeof(struct Tree));
    t->current.func = '+';
    t->left.pointer = (struct Tree *) malloc(sizeof(struct Tree));
    t->right.val = 3;
    t->left.val = 2;
//    t->left.pointer->right.variable = 'x';
//    struct Tree *f = deritive(t);
//    free_tree(f);
//  free_tree(t);*/
    return 0;
}
