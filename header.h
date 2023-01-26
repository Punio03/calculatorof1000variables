#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*errors
1 - Allocation error!
2 - Wrong expression!
3 - One of the values from the expressions is nan!
4 - Circular references!
5 - Undefined variable!
6 - Wrong variable assignment!
7 - Redeclaration of a variable!
*/

static char unary[8][3] = {"sin","cos","abs","tan","log","exp","sqr", "~"};
static char binary[5] = {'+', '-', '/', '*', '^'};

//parsing
int is_unary(char c1, char c2, char c3);
int is_binary(char c);
int priority(char c);
void RPN(char* bin);

//expression_tree
typedef struct tree {
    char function[4];
    long double val;
    struct tree* left;
    struct tree* right;
} tree;
typedef struct stack {
    struct stack* prev;
    struct stack* next;
    struct tree* val;
} stack;
stack* init_stack(tree* t);
void add_to_stack(stack* s,tree* t);
void add_to_stack_unary(stack* s,tree* t);
void add_to_stack_binary(stack* s,tree* t);
tree* numbers(char* bin);
tree* function_variable(char* bin);
tree* exp_tree(char* expression);

//evaluate_expression
long double evaluate(tree* t, int len, bool* check, struct tree** arr);
