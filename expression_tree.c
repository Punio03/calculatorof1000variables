#include "header.h"

stack* init_stack(trie* tree) {
    stack* stos = calloc(1,sizeof(stack));
    if (stos == NULL) exit(1);
    stos->val = tree;
    return stos;
}
void add_to_stack(stack* stos,trie* tree) {
    while (stos->next != NULL) {
        stos = stos->next;
    }
    stos->next = init_stack(tree);
    stack* stos_copy = stos;
    stos = stos->next;
    stos->prev = stos_copy;
}
void add_to_stack_f1(stack* stos, trie* tree) {
    while (stos->next != NULL) stos = stos->next;
    tree->right = stos->val;
    stos->val = tree;
}
void add_to_stack_f2(stack* stos, trie* tree) {
    while (stos->next != NULL) stos = stos->next;
    tree->right = stos->val;
    stos = stos->prev;
    stos->next = NULL;
    tree->left = stos->val;
    stos->val = tree;
}
trie* leaves(char* bin) {
    trie* lisc = calloc(1,sizeof(trie));
    if (strcmp(bin,"pi") == 0) {
        lisc->val = M_PI;
        return lisc;
    }
    else if (strcmp(bin,"e") == 0) {
        lisc->val = M_E;
        return lisc;
    }
    else {
        for (int i = 0; bin[i] != '\0'; i++) {
            if (bin[i] == '.') {
                lisc->val = atof(bin);
                return lisc;
            }
        }
    }
    lisc->val = atoi(bin);
    return lisc;
}
trie* function12(char* bin) {
    trie* lisc = calloc(1,sizeof(trie));
    for (int i = 0; bin[i] != '\0'; i++) {
        lisc->function[i] = bin[i];
    }
    return lisc;
}
trie* exp_tree(char* expression) {
    char* bin = strtok(expression, " ");
    trie* elem;
    stack* stos = NULL;
    while(bin != NULL) {
        if (isdigit((int)bin[0]) > 0 || strcmp(bin,"pi") == 0 || strcmp(bin,"e") == 0) {
            elem = leaves(bin);
            if (stos == NULL) stos = init_stack(elem);
            else add_to_stack(stos,elem);
        }
        else if (is_f1(bin[0],bin[1],bin[2]) == 3 || bin[0] == '~') {
            elem = function12(bin);
            add_to_stack_f1(stos,elem);
        }
        else if (is_f2(bin[0]) == 1) {
            elem = function12(bin);
            add_to_stack_f2(stos,elem);
        }

        bin = strtok( NULL, " ");
    }
    return stos->val;
}
