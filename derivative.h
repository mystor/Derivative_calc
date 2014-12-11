/* 
   Header for derivative calculator
 */

typedef enum {
    true = 1,
    false = 0,
} bool;

struct Tree {
    int f;
    union cur {
        char func;
        float val;
        char x;
    } current;
    union branch {
        struct Tree *pointer;
        float val;
        char variable;
    } left, right;
};

/* core functions */
struct Tree *deritive(struct Tree *orig);
void free_tree(struct Tree *tree);

/* tester functions */
void print_tree(struct Tree *t, int depth);
void print_tree_format(int depth);
struct Tree *test_tree();
