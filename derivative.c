#include <stdio.h>
#include <stdlib.h>
#include "derivative.h"

struct Tree *derivative(struct Tree *tree){
    struct Tree *node = malloc(sizeof(struct Tree));
    if(!tree->node_type){
        switch(tree->this.func){
        case '+':
            set_func(node, '+');
            node->left = derivative(tree->left);
            node->right = derivative(tree->right);
            break;
        case '*':
            set_func(node, '+');
            node->left = malloc(sizeof(struct Tree));
            node->right = malloc(sizeof(struct Tree));
            set_func(node->left, '*');
            set_func(node->right, '*');
            node->left->left = derivative(tree->left);
            node->left->right = copy_tree(tree->right);
            node->right->left = derivative(tree->right);
            node->right->right = copy_tree(tree->left);
            break;
        }
        return node;
    } else if(tree->node_type == 1) {
        node->node_type = NUM;
        node->this.num = 0;
    } else { //ddx of x is 1
        node->node_type = NUM;
        node->this.num = 1;
    }
    return node;
}
    
void set_func(struct Tree *node, char f){
    node->node_type = FUNC;
    node->this.func = f;
}

struct Tree *copy_tree(struct Tree *tree){
    if(tree == NULL){
        return NULL;
    }
    struct Tree *node = malloc(sizeof(struct Tree));
    node->node_type = tree->node_type;
    node->this = tree->this;
    node->left = copy_tree(tree->left);
    node->right = copy_tree(tree->right);
    return node;
}

/* recursivly free()'s all pointers in a tree */
void free_tree(struct Tree *tree){
    if(tree->left == NULL && tree->right == NULL){
        free(tree);
    } else if(tree->left == NULL){
        free_tree(tree->right);
        free(tree);
    } else if(tree->right == NULL){
        free_tree(tree->left);
        free(tree);
    } else {
        free_tree(tree->right);
        free_tree(tree->left);
        free(tree);
    }
}

void print_AST(struct Tree *AST){
    if(AST->left != NULL){
        print_AST(AST->left);
    }
    switch (AST->node_type){
    case FUNC:
        printf("%c", AST->this.func);
        break;
    case NUM:
        printf("%f", AST->this.num);
        break;
    case VAR:
        printf("x");
        break;
    }
    if(AST->right != NULL){
        print_AST(AST->right);
    }
}
