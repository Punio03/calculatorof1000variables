#include "header.h"

int is_unary(char c1, char c2, char c3) {
    if (c1 == '~') return 1;
    for (int i = 0; i < 7; i++) if (unary[i][0] == c1 && unary[i][1] == c2 && unary[i][2] == c3) return 3;
    return 0;
}
int is_binary(char c) {
    for (int i = 0; i < 5; i++) if (c == binary[i]) return 1;
    return 0;
}
int priority(char c) {
    if (c == '(') return 0;
    else if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return 4;
}
void RPN(char* bin) {
    int index = 0, iexp = 0, is = 0, ifun = 0, lexp = 50, ls = 25, lfun = 25,priobef, prionow, cd, val;
    char* exp = malloc(lexp*sizeof(char));
    char* s = malloc(ls * sizeof(char));
    char* function = malloc(lfun * sizeof(char));
    if (exp == NULL || s == NULL || function == NULL) {
        fprintf(stderr, "Allocation error!");
        exit(1);
    }
    while (bin[index] != '\0') {
        if (bin[index] == ' ') index++;
        else if (bin[index] == 'v') {
            exp[iexp] = 'v';
            for (int i = 1; i < 4; i++) {
                if (!isdigit(bin[index + i])) {
                    fprintf(stderr, "Wrong expression!");
                    exit(2);
                }
                else exp[iexp + i] = bin[index + i];
            }
            exp[iexp + 4] = ' ';
            iexp += 5;
            index += 4;
        }
        else if (isdigit(bin[index]) > 0) {
            cd = 0;
            for (int i = index; isdigit(bin[i]) > 0 || bin[i] == ',' || bin[i] == '.'; i++) {
                if (cd == 0 && (bin[i] == ',' || bin[i] == '.')) {
                    cd++;
                    exp[iexp] = '.';
                } else if (isdigit(bin[i]) > 0) exp[iexp] = bin[i];
                else {
                    fprintf(stderr, "Wrong expression!");
                    exit(2);
                }
                iexp++;
                index++;
            }
            exp[iexp] = ' ';
            iexp++;
        }
        else if (bin[index] == 'e' && bin[index + 1] != 'x') {
            exp[iexp] = 'e';
            exp[iexp + 1] = ' ';
            index++;
            iexp += 2;
        }
        else if (bin[index] == 'p' && bin[index + 1] == 'i') {
            exp[iexp] = 'p';
            exp[iexp + 1] = 'i';
            exp[iexp + 2] = ' ';
            index += 2;
            iexp += 3;
        }
        else if (bin[index] == '(') {
            s[is] = '(';
            is++;
            index++;
        }
        else if (is_binary(bin[index]) == 1) {
            if (is - 1 >= 0) priobef = priority(s[is - 1]);
            else priobef = 0;
            prionow = priority(bin[index]);
            while (priobef > prionow) {
                is--;
                if (s[is] == 'f') {
                    ifun--;
                    if (function[ifun] == '~') {
                        exp[iexp] = function[ifun];
                        exp[iexp+1] = ' ';
                        iexp += 2;
                    }
                    else {
                        for (int i = ifun - 2; i <= ifun; i++) {
                            exp[iexp] = function[i];
                            function[i] = '\0';
                            iexp++;
                        }
                        exp[iexp] = ' ';
                        iexp++;
                        ifun -= 2;
                    }
                }
                else {
                    exp[iexp] = s[is];
                    exp[iexp + 1] = ' ';
                    iexp += 2;
                    s[is] = '\0';
                }
                if (is - 1 >= 0) priobef = priority(s[is - 1]);
                else priobef = 0;
            }
            s[is] = bin[index];
            is++;
            index++;
        }
        else if (bin[index] == ')') {
            for (int i = is - 1;; i--) {
                if (s[i] == '(') {
                    s[i] = '\0';
                    is = i;
                    break;
                }
                else {
                    if (s[i] == 'f') {
                        ifun --;
                        if (function[ifun] == '~') {
                            exp[iexp] = function[ifun];
                            function[ifun] = '\0';
                            exp[iexp+1] = ' ';
                            iexp += 2;
                        }
                        else {
                            for (int j = ifun - 2; j <= ifun; j++) {
                                exp[iexp] = function[j];
                                function[j] = '\0';
                                iexp++;
                            }
                            exp[iexp] = ' ';
                            iexp++;
                            ifun -= 2;
                        }
                    }
                    else {
                        exp[iexp] = s[i];
                        exp[iexp + 1] = ' ';
                        iexp += 2;
                        s[is] = '\0';
                    }
                }
            }
            if (s[is - 1] == 'f') {
                is --;
                s[is] = '\0';
                ifun --;
                if (function[ifun] == '~') {
                    exp[iexp] = function[ifun];
                    function[ifun] = '\0';
                    exp[iexp+1] = ' ';
                    iexp += 2;
                }
                else {
                    for (int i = ifun - 2; i <= ifun; i++) {
                        exp[iexp] = function[i];
                        function[i] = '\0';
                        iexp++;
                    }
                    exp[iexp] = ' ';
                    iexp++;
                    ifun -= 2;
                }
            }
            index++;
        }
        else if ((val = is_unary(bin[index], bin[index + 1], bin[index + 2])) > 0) {
            s[is] = 'f';
            is++;
            for (int i = index; i < index + val; i++) {
                function[ifun] = bin[i];
                ifun++;
            }
            index += val;
        }
        else {
            fprintf(stderr, "Wrong expression!");
            exit(2);
        }
        if (lexp/2 <= iexp) {
            lexp *= 2;
            exp = realloc(exp,lexp*sizeof(char));
        }
        if (ls / 2 <= is) {
            ls *= 2;
            s = realloc(s, ls * sizeof(char));
        }
        if (lfun / 2 <= ifun) {
            lfun *= 2;
            function = realloc(function, lfun * sizeof(char));
        }
        if (exp == NULL || s == NULL || function == NULL) {
            fprintf(stderr, "Allocation error!");
            exit(1);
        }
    }
    while (is > 0) {
        is--;
        if (s[is] == '(') {
            fprintf(stderr, "Wrong expression!");
            exit(2);
        }
        else if (s[is] == 'f') {
            s[is] = '\0';
            ifun --;
            if (function[ifun] == '~') {
                exp[iexp] = function[ifun];
                function[ifun] = '\0';
                exp[iexp+1] = ' ';
                iexp += 2;
            }
            else {
                for (int i = ifun - 2; i <= ifun; i++) {
                    exp[iexp] = function[i];
                    function[i] = '\0';
                    iexp++;
                }
                exp[iexp] = ' ';
                iexp++;
                ifun -= 2;
            }
        }
        else {
            exp[iexp] = s[is];
            exp[iexp + 1] = ' ';
            iexp += 2;
        }
    }
    bin = memset(bin, 0, strlen(bin));
    for (int i = 0; i < iexp; i++) bin[i] = exp[i];
    free(exp);
    free(s);
    free(function);
}
