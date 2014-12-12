#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivative.h"

struct Tree *derivative(struct Tree *tree){
    if(tree == NULL){
        return NULL;
    }
    struct Tree *node = calloc(1, sizeof(struct Tree));
    if(!tree->node_type){
        switch(tree->this.func){
        case '+':
            set_func(node, '+');
            node->left = derivative(tree->left);
            node->right = derivative(tree->right);
            break;
        case '-':
            set_func(node, '-');
            node->left = derivative(tree->left);
            node->right = derivative(tree->right);
        case '*':
            set_func(node, '+');
            node->left = calloc(1, sizeof(struct Tree));
            node->right = calloc(1, sizeof(struct Tree));
            set_func(node->left, '*');
            set_func(node->right, '*');
            node->left->left = derivative(tree->left);
            node->left->right = copy_tree(tree->right);
            node->right->left = derivative(tree->right);
            node->right->right = copy_tree(tree->left);
            break;
        case '^':
            if(!is_defx(tree->right)){
                node->left = calloc(1, sizeof(struct Tree));
                node->right = calloc(1, sizeof(struct Tree));
                node->right->left = calloc(1, sizeof(struct Tree));
                node->right->right = calloc(1, sizeof(struct Tree));
                node->right->right->left = calloc(1, sizeof(struct Tree));
                node->right->right->right = calloc(1, sizeof(struct Tree));
                set_func(node, '*');
                set_func(node->right, '^');
                set_func(node->right->right, '+');
                node->left = copy_tree(tree->right);
                node->right->left = copy_tree(tree->left);
                node->right->right->left = copy_tree(tree->right);
                node->right->right->right->node_type = NUM;
                node->right->right->right->this.num = -1;
        } else {
            fprintf(stderr, "expodentials arn't defined yet!\n");
            exit(1);
        }
            break;
        case '/':
            node->left = calloc(1, sizeof(struct Tree));
            node->left->left = calloc(1, sizeof(struct Tree));
            node->left->left->left = calloc(1, sizeof(struct Tree));
            node->left->left->right = calloc(1, sizeof(struct Tree));
            node->left->right = calloc(1, sizeof(struct Tree));
            node->left->right->left = calloc(1, sizeof(struct Tree));
            node->left->right->right = calloc(1, sizeof(struct Tree));
            node->right = calloc(1, sizeof(struct Tree));
            node->right->left = calloc(1, sizeof(struct Tree));
            node->right->right = calloc(1, sizeof(struct Tree));
            set_func(node, '/');
            set_func(node->left, '-');
            set_func(node->left->left, '*');
            set_func(node->left->right, '*');
            set_func(node->right, '^');
            node->left->left->left = derivative(tree->left);
            node->left->left->right = copy_tree(tree->right);
            node->left->right->left = derivative(tree->right);
            node->left->right->right = copy_tree(tree->left);
            node->right->left = copy_tree(tree->right);
            node->right->right->node_type = NUM;
            node->right->right->this.num = 2;
            break;
        default:
            fprintf(stderr, "WTF is '%c'??\n", tree->this.func);
            exit(1);
        }
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
    struct Tree *node = calloc(1, sizeof(struct Tree));
    node->node_type = tree->node_type;
    node->this = tree->this;
    node->left = copy_tree(tree->left);
    node->right = copy_tree(tree->right);
    return node;
}

void simplify_AST(struct Tree *AST){
    if(AST == NULL){
        return;
    }
    if(AST->node_type == FUNC){
        switch(AST->this.func){
        case '+':
            if(AST->left->node_type == NUM && AST->left->this.num == 0){
                switch_up(AST, 0);
            } else if(AST->right->node_type == NUM && AST->right->this.num == 0){
                switch_up(AST, 1);
            }
            if(AST->left->node_type == NUM && AST->right->node_type == NUM){
                eval_node(AST);
            }
            break;
        case '*':
            if(AST->left->node_type == NUM && AST->right->node_type == NUM){
                eval_node(AST);
            } else if(AST->left->node_type == NUM && AST->left->this.num == 1){
                switch_up(AST, 0);
            } else if(AST->right->node_type == NUM && AST->right->this.num == 1){
                switch_up(AST, 1);
            } else if((AST->right->node_type == NUM && AST->right->this.num == 0)
                      || (AST->left->node_type == NUM && AST->left->this.num == 0)){
                free(AST->left);
                free(AST->right);
                AST->right = NULL;
                AST->left = NULL;
                AST->node_type = NUM;
                AST->this.num = 0;
            }
            break;
        case '^':
//            if(AST->left->node_type == NUM && AST->right->node_type == NUM){
//                eval_node(AST);
//            }
            break;
        case '-':
            if(AST->left->node_type == NUM && AST->right->node_type == NUM){
                eval_node(AST);
            }
            break;
        }
    }
    simplify_AST(AST->left);
    simplify_AST(AST->right);
}

void eval_node(struct Tree *AST){
    float l = AST->left->this.num;
    float r = AST->right->this.num;
    char func = AST->this.func;
    AST->node_type = NUM;

    free(AST->left);
    free(AST->right);
    AST->left = NULL;
    AST->right = NULL;
    switch(func){
    case '*':
        AST->this.num = l * r;
        break;
    case '+':
        AST->this.num = l + r;
        break;
    case '-':
        AST->this.num = l - r;
        break;
//    case '^':
//        AST->this.num = pow(l, r);
//        break;
    default:
        fprintf(stderr, "WTF is %c?? (derivative.c: eval_node())\n", func);
        exit(1);
        break;
    }
}

void switch_up(struct Tree *AST, int is_left){
            if(!is_left){
                switch(AST->right->node_type){
                case NUM:
                    AST->node_type = NUM;
                    AST->this.num = AST->right->this.num;
                    break;
                case VAR:
                    AST->node_type = VAR;
                    AST->this.var = AST->right->this.var;
                    break;
                case FUNC:
                    AST->node_type = FUNC;
                    AST->this.func = AST->right->this.func;
                    break;
                }
                struct Tree *tmp1 = AST->right;
                struct Tree *tmp2 = AST->left;
                AST->left = tmp1->left;
                AST->right = tmp1->right;
                free(tmp1);
                free(tmp2);
            } else {
                switch(AST->left->node_type){
                case NUM:
                    AST->node_type = NUM;
                    AST->this.num = AST->left->this.num;
                    break;
                case VAR:
                    AST->node_type = VAR;
                    AST->this.var = AST->left->this.var;
                    break;
                case FUNC:
                    AST->node_type = FUNC;
                    AST->this.func = AST->left->this.func;
                    break;
                }
                struct Tree *tmp1 = AST->left;
                struct Tree *tmp2 = AST->right;
                AST->left = tmp1->left;
                AST->right = tmp1->right;
                free(tmp1);
                free(tmp2);
            }
}

/* sets the markers on the parts of the tree that are defined in terms of x */
int is_defx(struct Tree *tree){
    if(tree == NULL){
        return 0;
    } else if(tree->node_type == VAR){
        return 1;
    } else if(is_defx(tree->left) || is_defx(tree->right)){
        return 1;
    } else {
        return 0;
    }
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
        printf("%.0f", AST->this.num);
        break;
    case VAR:
        printf("x");
        break;
    }
    if(AST->right != NULL){
        print_AST(AST->right);
    }
}
