#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//parsing
int is_f1(char c1, char c2, char c3);
int is_f2(char c);
int priority(char c);
void RPN(char* s);

//expression_tree
typedef struct trie {
    char function[3];
    long double val;
    struct trie* left;
    struct trie* right;
} trie;
typedef struct stack {
    struct stack* prev;
    struct stack* next;
    struct trie* val;
} stack;
stack* init_stack(trie* tree);
void add_to_stack(stack* stos,trie* tree);
void add_to_stack_f1(stack* stos,trie* tree);
void add_to_stack_f2(stack* stos,trie* tree);
trie* leaves(char* bin);
trie* function12(char* bin);
trie* exp_tree(char* expression);

long double count(trie* tree);