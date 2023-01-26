#include "header.h"

int main(void) {
    int index = 0, i, v, lexp = 10, lbin = 10, larr = 10;
    char c,number[3];
    char* bin = calloc(lbin, sizeof(char)), *exp = calloc(lexp, sizeof(char));
    tree** arr = calloc(larr, sizeof(tree*));
    bool* check = calloc(larr, sizeof(bool));
    if (bin == NULL || arr == NULL || check == NULL || exp == NULL) {
        fprintf(stderr, "Allocation error!");
        exit(1);
    }
    while (1) {
        c = (char)fgetc(stdin);
        if ((c == '\n' || c==EOF) && bin[0] == '\0') break;
        if (c == '\n' || c == EOF) {
            v = -1;
            for (i = 0; bin[i] != '=' && bin[i] != '\0'; i++) {
                if (bin[i] == 'v' && isdigit(bin[i+1]) > 0 && isdigit(bin[i+2]) > 0 && isdigit(bin[i+3]) > 0 && v == -1) {
                    number[0] = bin[i + 1];
                    number[1] = bin[i + 2];
                    number[2] = bin[i + 3];
                    v = atoi(number);
                    i += 3;
                }
                else if (bin[i] == ' ') {}
                else {
                    fprintf(stderr, "Wrong variable assignment!");
                    exit(6);
                }
            }
            if (bin[i] != '=' || v == -1) {
                fprintf(stderr, "Wrong variable assignment!");
                exit(6);
            }
            if (v + 1 > larr) {
                larr = v + 1;
                arr = realloc(arr, larr * sizeof(tree*));
                check = realloc(check, larr * sizeof(bool));
                if (arr == NULL || check == NULL) {
                    fprintf(stderr, "Allocation error!");
                    exit(1);
                }
            }
            if (arr[v] != NULL) {
                fprintf(stderr, "Redeclaration of a variable!");
                exit(7);
            }
            for (int k = i+1, j = 0; bin[k] != '\0'; k++, j++) {
                if (j >= lexp / 2) {
                    lexp *= 2;
                    exp = realloc(exp, lexp * sizeof(char));
                    if (exp == NULL) {
                        fprintf(stderr, "Allocation error!");
                        exit(1);
                    }
                }
                exp[j] = bin[k];
            }
            RPN(exp);
            arr[v] = exp_tree(exp);
            memset(bin, 0, lbin);
            memset(exp, 0, lexp);
            index = 0;
            if (c==EOF) break;
        }
        else {
            if (index >= lbin / 2) {
                lbin *= 2;
                bin = realloc(bin, lbin * sizeof(char));
                if (bin == NULL) {
                    fprintf(stderr, "Allocation error!");
                    exit(1);
                }
            }
            bin[index] = c;
            index++;
        }
    }
    for (i = 0; i < larr; i++) {
        if (arr[i] != NULL) {
            printf("v%03d = %Lf\n", i, evaluate(arr[i], larr, check, arr));
            memset(check, 0, larr);
        }
    }
    free(bin);
    free(exp);
    free(arr);
    free(check);
}
