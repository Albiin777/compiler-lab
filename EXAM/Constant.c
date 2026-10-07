/*
 * Simple Constant Propagation
 * ----------------------------
 * Reads statements of the form:  var = expression
 * Expression can use + - * / and parentheses, and can
 * reference variables defined in earlier statements.
 *
 * Each variable's value is computed immediately using the
 * already-known values of earlier variables (this IS constant
 * propagation: known constants are substituted as we go).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int val[26], known[26];
char *p;

int expr();

int factor() {
    while (*p == ' ') p++;
    if (isdigit(*p)) {
        int v = 0;
        while (isdigit(*p)) v = v * 10 + (*p++ - '0');
        return v;
    }
    if (isalpha(*p)) return val[*p++ - 'a'];
    if (*p == '(') { p++; int v = expr(); if (*p == ')') p++; return v; }
    return 0;
}

int term() {
    int v = factor();
    while (*p == ' ') p++;
    while (*p == '*' || *p == '/') {
        char op = *p++;
        v = (op == '*') ? v * factor() : v / factor();
        while (*p == ' ') p++;
    }
    return v;
}

int expr() {
    int v = term();
    while (*p == ' ') p++;
    while (*p == '+' || *p == '-') {
        char op = *p++;
        v = (op == '+') ? v + term() : v - term();
        while (*p == ' ') p++;
    }
    return v;
}

int main() {
    int n;
    char line[100];
    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter each statement as: var = expression\n");
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        char *eq = strchr(line, '=');
        int idx = line[0] - 'a';
        p = eq ? eq + 1 : line + 2;
        val[idx] = expr();
        known[idx] = 1;
    }

    printf("\nFinal values (after constant propagation):\n");
    for (int i = 0; i < 26; i++) {
        if (known[i]) printf("%c = %d\n", 'a' + i, val[i]);
    }
    return 0;
}

/* Sample Input/Output:
Enter number of statements: 3
Enter each statement as: var = expression
a = 30
b = 20 - a /2
c = b * ( 30 / a + 2 ) -  a

Final values (after constant propagation):
a = 30
b = 5
c = -15
*/

