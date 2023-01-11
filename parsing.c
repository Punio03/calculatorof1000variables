#include "header.h"
char f1[7][3] = {"sin","cos","abs","tan","log","exp","sqr"};
char f2[6] = {'+', '-', '/', '*', '^', '~'};

int is_f1(char c1, char c2, char c3) {
    for (int i = 0; i < 6; i++) if (f1[i][0] == c1 && f1[i][1] == c2 && f1[i][2] == c3) return 3;
    return 0;
} //funkcja do sprawdzenia jest to funkcja z f1
int is_f2(char c) {
    for (int i = 0; i < 6; i++) {
        if (c == f2[i]) return 1;
    }
    return 0;
}//funkcja do sprawdzania czy znak jest w f2
int priority(char c) {
    if (c == '(' || c == 'f') return 0;
    else if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else return 3;
} //funkcja zwrcajac prioryte znaków
void RPN(char* s) {
    int is = 0, iexp = 0, istack = 0, ifunction = 0, lexp = 50, lstack = 25, lfunction = 25,prio_before, prio_new, pk, ifun;
    char* exp = malloc(lexp*sizeof(char));
    char* stack = malloc(lstack*sizeof (char));
    char* function = malloc(lfunction*sizeof(char));
    if (exp == NULL || stack == NULL || function == NULL) exit(1);
    while (s[is] != '\0') {
        if (s[is] == ' ') is++; //spacja
        else if (s[is] == 'v') {
            exp[iexp] = 'v';
            for (int i = 1; i < 4; i++) {
                if (!isdigit(s[is + i])) exit(2);
                else exp[iexp + i] = s[is + i];
            }
            exp[iexp + 4] = ' ';
            iexp += 5;
            is += 4;
        } //zmienna
        else if (isdigit(s[is]) > 0) {
            pk = 0;
            for (int i = is; isdigit(s[i]) > 0 || s[i] == ',' || s[i] == '.'; i++) {
                if (pk == 0 && (s[i] == ',' || s[i] == '.')) {
                    pk++;
                    exp[iexp] = '.';
                } else if (isdigit(s[i]) > 0) exp[iexp] = s[i];
                else exit(2);
                iexp++;
                is++;
            }
            exp[iexp] = ' ';
            iexp++;
        } //liczba
        else if (s[is] == 'e' && s[is + 1] != 'x') {
            exp[iexp] = 'e';
            exp[iexp + 1] = ' ';
            is++;
            iexp += 2;
        } //stała e
        else if (s[is] == 'p' && s[is + 1] == 'i') {
            exp[iexp] = 'p';
            exp[iexp + 1] = 'i';
            exp[iexp + 2] = ' ';
            is += 2;
            iexp += 3;
        } //stała pi
        else if (s[is] == '(') {
            stack[istack] = '(';
            istack++;
            is++;
        } //otwarcie wyrazenia w nawiasie/funkcji 1-arg
        else if (is_f2(s[is]) == 1) {
            if (istack-1 >= 0) prio_before = priority(stack[istack-1]);
            else prio_before = 0;
            prio_new = priority(s[is]);
            while (prio_before > prio_new) {
                istack--;
                exp[iexp] = stack[istack];
                exp[iexp + 1] = ' ';
                iexp += 2;
                stack[istack] = '\0';
                if (istack - 1 >= 0) prio_before = priority(stack[istack - 1]);
                else prio_before = 0;
            }
            stack[istack] = s[is];
            istack++;
            is++;
        } //znak na stos + ewentualne zwolnienie miejsca na stosie
        else if (s[is] == ')') {
            for (int i = istack - 1;; i--) {
                if (stack[i] == '(') {
                    stack[i] = '\0';
                    istack = i;
                    break;
                } else {
                    exp[iexp] = stack[i];
                    exp[iexp + 1] = ' ';
                    iexp += 2;
                    stack[istack] = '\0';
                }
            }
            if (stack[istack-1] == 'f') {
                istack --;
                stack[istack] = '\0';
                ifunction --;
                for (int i = ifunction-2; i <= ifunction; i++) {
                    exp[iexp] = function[i];
                    function[i] = '\0';
                    iexp ++;
                }
                exp[iexp] = ' ';
                iexp ++;
                ifunction -= 2;
            }
            is++;
        }//zamkniecie wyrazenia w nawiasie/funkcji 1-arg
        else if ((ifun = is_f1(s[is],s[is+1],s[is+2]))>0) {
            stack[istack] = 'f';
            istack++;
            for (int i = is; i < is+ifun; i++) {
                function[ifunction] = s[i];
                ifunction++;
            }
            is += ifun;
        } //dodawanie funkcji 1-arg do stosu
        else exit(2);
        if (lexp/2 <= iexp) {
            lexp *= 2;
            exp = realloc(exp,lexp*sizeof(char));
        }
        if (lstack/2 <= istack) {
            lstack *= 2;
            stack = realloc(stack,lstack*sizeof(char));
        }
        if (lfunction/2 <= ifunction) {
            lfunction *= 2;
            function = realloc(function,lfunction*sizeof(char));
        }
        if (exp == NULL || stack == NULL || function == NULL) exit(1);
    }
    istack--;
    while (istack >= 0) {
        if (stack[istack] == 'f' || stack[istack] == '(') exit(2);
        exp[iexp] = stack[istack];
        exp[iexp+1] = ' ';
        iexp += 2;
        istack--;
    }//wypisanie znaków pozostałych na stosie
    s = realloc(s,lexp*sizeof(char));
    s = memset(s,0,strlen(s));
    for (int i = 0; i < iexp; i++) s[i] = exp[i];
    free(exp);
    free(stack);
    free(function);
}