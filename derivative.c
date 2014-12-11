#include <stdio.h>
#include <stdlib.h>
#include "derivative.h"

struct Tree *deritive(struct Tree *orig){
    struct Tree *node = malloc(sizeof(struct Tree));
    switch(orig->current.func) {
        case '\0':
            if(orig->current.x == '\0'){
                node->current.val = 0;
            } else {
                node->current.val = 1;
            }
            break;
        case '+':
            node->left.pointer = deritive(orig->left.pointer);
            node->right.pointer = deritive(orig->right.pointer);
            break;
        case '*':
            node->current.func = '+';
            node->left.pointer = deritive(orig->left.pointer);
            node->right.pointer = deritive(orig->right.pointer);
            break;
        default:
            fprintf(stderr, "WTF is %c??\n", orig->current.func);
            exit(1);
            break;
    }
    return node;
}

/* recursivly free()'s all pointers in tree */
void free_tree(struct Tree* tree) {
    if (tree->left.pointer == NULL && tree->right.pointer == NULL) {
        free(tree);
        return;
    } else if (tree->left.pointer == NULL) {
        free_tree(tree->right.pointer);
        free(tree);
    } else if (tree->right.pointer == NULL) {
        free_tree(tree->left.pointer);
        free(tree);
    } else {
        free_tree(tree->left.pointer);
        free_tree(tree->right.pointer);
        free(tree);
    }
}

void print_tree(struct Tree *t, int depth){
    return;
}

void print_tree_format(int depth){
    for(int i = 0; i < depth; ++i){
        printf("   ");
    }
}
