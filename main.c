#include "header.h"

int main(void) {
    int counter = 1, len = 50, indeks = 0;
    char c;
    char* expression = calloc(len,sizeof (char));
    if (expression == NULL) exit(1);
    while (1) {
        if (counter == 1000) exit(3);
        printf("v%03d = ", counter);
        counter ++;
        while ((c=(char)getchar()) != '\n') {
            expression[indeks] = c;
            indeks ++;
            if (indeks > len/2) {
                len *= 2;
                expression = realloc(expression, len*sizeof(char));
                if (expression == NULL) exit(1);
            }
        }
        RPN(expression);
        for (int i = 0; expression[i] != '\0'; i++) {
            putchar(expression[i]);
        }
        putchar('\n');
        trie* treeee = exp_tree(expression);
        printf("%Lf\n", count(treeee));
        expression = memset(expression,0, len);
        indeks = 0;
        len = 50;
        expression = realloc(expression, sizeof(char)*len);
        if (expression == NULL) exit(1);
    }
}
