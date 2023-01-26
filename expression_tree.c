#include "header.h"
stack* init_stack(tree* t) {
    stack* s = calloc(1, sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "Allocation error!");
        exit(1);
    }
    s->val = t;
    return s;
}
void add_to_stack(stack* s,tree* t) {
    while (s->next != NULL) {
        s = s->next;
    }
    s->next = init_stack(t);
    stack* scp = s;
    s = s->next;
    s->prev = scp;
}
void add_to_stack_unary(stack* s, tree* t) {
    while (s->next != NULL) s = s->next;
    t->right = s->val;
    s->val = t;
}
void add_to_stack_binary(stack* s, tree* t) {
    while (s->next != NULL) s = s->next;
    t->right = s->val;
    s = s->prev;
    s->next = NULL;
    t->left = s->val;
    s->val = t;
}
tree* numbers(char* bin) {
    tree* t = calloc(1, sizeof(tree));
    if (t == NULL) {
        fprintf(stderr, "Allocation error!");
        exit(1);
    }
    if (strcmp(bin,"pi") == 0) {
        t->val = M_PI;
        return t;
    }
    else if (strcmp(bin,"e") == 0) {
        t->val = M_E;
        return t;
    }
    else {
        for (int i = 0; bin[i] != '\0'; i++) {
            if (bin[i] == '.') {
                t->val = atof(bin);
                return t;
            }
        }
    }
    t->val = atoi(bin);
    return t;
}
tree* function_variable(char* bin) {
    tree* t = calloc(1, sizeof(tree));
    if (t == NULL) {
        fprintf(stderr, "Allocation error!");
        exit(1);
    }
    for (int i = 0; bin[i] != '\0'; i++) {
        t->function[i] = bin[i];
    }
    return t;
}
tree* exp_tree(char* expression) {
    char* bin = strtok(expression, " ");
    tree* elem;
    stack* s = NULL;
    while(bin != NULL) {
        if (isdigit((int)bin[0]) > 0 || strcmp(bin,"pi") == 0 || strcmp(bin,"e") == 0) {
            elem = numbers(bin);
            if (s == NULL) s = init_stack(elem);
            else add_to_stack(s, elem);
        }
        else if (bin[0] == 'v') {
            elem = function_variable(bin);
            if (s == NULL) s = init_stack(elem);
            else add_to_stack(s, elem);
        }
        else if (is_unary(bin[0],bin[1],bin[2]) > 0) {
            elem = function_variable(bin);
            add_to_stack_unary(s, elem);
        }
        else if (is_binary(bin[0]) == 1) {
            elem = function_variable(bin);
            add_to_stack_binary(s, elem);
        }
        bin = strtok( NULL, " ");
    }
    if (s->next != NULL && s->next->val != NULL) {
        fprintf(stderr, "Wrong expression!");
        exit(2);
    }
    free(bin);
    return s->val;
}
