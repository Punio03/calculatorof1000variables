#include "header.h"

long double count(trie* tree) {
    if (tree == NULL) return 0;
    if (tree->left == NULL && tree->right == NULL) return tree->val;
    long double lewa_suma = count(tree->left);
    long double prawa_suma = count(tree->right);
    if (tree->function[0] == '+') return lewa_suma+prawa_suma;
    else if (tree->function[0] == '-') return lewa_suma-prawa_suma;
    else if (tree->function[0] == '*') return lewa_suma*prawa_suma;
    else if (tree->function[0] == '/') return lewa_suma/prawa_suma;
    else if (tree->function[0] == '^') return powl(lewa_suma,prawa_suma);
    else if (tree->function[0] == '~') return -1*(lewa_suma+prawa_suma);
    else if (tree->function[0] == 'a') {
        if (lewa_suma+prawa_suma >= 0) return lewa_suma+prawa_suma;
        else if (lewa_suma+prawa_suma < 0) return (-1)*(lewa_suma+prawa_suma);
    }
    else if (tree->function[0] == 't') return tanl(lewa_suma+prawa_suma);
    else if (tree->function[0] == 'c') return cosl(lewa_suma+prawa_suma);
    else if (tree->function[0] == 'e') return expl(lewa_suma+prawa_suma);
    else if (tree->function[0] == 'l') return log10l(lewa_suma+prawa_suma);
    else if (tree->function[0] == 's' && tree->function[1] == 'i') return sinl(lewa_suma+prawa_suma);
    else if (tree->function[0] == 's' && tree->function[1] == 'q') return sqrtl(lewa_suma+prawa_suma);
    return 0;
}