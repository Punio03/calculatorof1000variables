#include "header.h"
long double evaluate(tree* t, int len,bool* check, tree** arr) {
    if (t == NULL) return 0;
    if (t->left == NULL && t->right == NULL && t->function[0] == 'v') {
        char num[3];
        bool* check2 = calloc(len,sizeof(bool));
        if (check2 == NULL) {
            fprintf(stderr,"Allocation error!");
            exit(1);
        }
        for (int i = 0; i < len; i++) check2[i] = check[i];
        num[0] = t->function[1];
        num[1] = t->function[2];
        num[2] = t->function[3];
        int v = atoi(num);
        if (arr[v] == NULL || v >= len) {
            fprintf(stderr, "Undefined variable!");
            exit(5);
        }
        if (check2[v] == true) {
            fprintf(stderr, "Circular references!");
            exit(4);
        }
        else check2[v] = true;
        return evaluate(arr[v], len, check2, arr);
    }
    if (t->left == NULL && t->right == NULL) return t->val;
    long double left_sum = evaluate(t->left, len, check, arr);
    long double right_sum = evaluate(t->right, len, check, arr);
    if (t->function[0] == '+') {
        if (isnan(left_sum + right_sum) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return left_sum + right_sum;
    }
    else if (t->function[0] == '-') {
        if (isnan(left_sum - right_sum) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return left_sum - right_sum;
    }
    else if (t->function[0] == '*') {
        if (isnan(left_sum * right_sum) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return left_sum * right_sum;
    }
    else if (t->function[0] == '/') {
        if (isnan(left_sum / right_sum) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return left_sum / right_sum;
    }
    else if (t->function[0] == '^') {
        if (isnan(powl(left_sum, right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return powl(left_sum, right_sum);
    }
    else if (t->function[0] == '~') {
        if (isnan(-1 * (left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return -1 * (left_sum + right_sum);
    }
    else if (t->function[0] == 'a') {
        if (left_sum + right_sum >= 0) {
            if (isnan(left_sum + right_sum) == 1) {
                fprintf(stderr, "One of the values from the expressions is nan!");
                exit(3);
            }
            return left_sum + right_sum;
        }
        else if (left_sum + right_sum < 0) {
            if (isnan((-1) * (left_sum + right_sum)) == 1) {
                fprintf(stderr, "One of the values from the expressions is nan!");
                exit(3);
            }
            return (-1) * (left_sum + right_sum);
        }
    }
    else if (t->function[0] == 't') {
        if (isnan(tanl(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return tanl(left_sum + right_sum);
    }
    else if (t->function[0] == 'c') {
        if (isnan(cosl(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return cosl(left_sum + right_sum);
    }
    else if (t->function[0] == 'e') {
        if (isnan(expl(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return expl(left_sum + right_sum);
    }
    else if (t->function[0] == 'l') {
        if (isnan(log10l(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return log10l(left_sum + right_sum);
    }
    else if (t->function[0] == 's' && t->function[1] == 'i') {
        if (isnan(sinl(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return sinl(left_sum + right_sum);
    }
    else if (t->function[0] == 's' && t->function[1] == 'q') {
        if (isnan(sqrtl(left_sum + right_sum)) == 1) {
            fprintf(stderr, "One of the values from the expressions is nan!");
            exit(3);
        }
        return sqrtl(left_sum + right_sum);
    }
    return 0;
}
