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

#define MAX_VARS 26          /* one slot per letter a-z */

int value[MAX_VARS];         /* value[i] = value of variable ('a'+i) */
int known[MAX_VARS];         /* known[i] = 1 if that variable has been defined */

char *p;                     /* cursor into the expression string being parsed */

int expr();                  /* forward declarations for recursive descent */

/* factor = NUMBER | VARIABLE | '(' expr ')' */
int factor() {
    while (*p == ' ') p++;              /* skip spaces */

    if (isdigit(*p)) {                  /* number literal */
        int val = 0;
        while (isdigit(*p)) val = val * 10 + (*p++ - '0');
        return val;
    }
    if (isalpha(*p)) {                  /* variable reference */
        int idx = *p - 'a';
        p++;
        return value[idx];              /* substitute its known value */
    }
    if (*p == '(') {                    /* parenthesized sub-expression */
        p++;                            /* skip '(' */
        int val = expr();
        while (*p == ' ') p++;
        if (*p == ')') p++;             /* skip ')' */
        return val;
    }
    return 0;
}

/* term = factor (('*' | '/') factor)*   -- handles precedence of * / */
int term() {
    int val = factor();
    while (*p == ' ') p++;
    while (*p == '*' || *p == '/') {
        char op = *p++;
        int rhs = factor();
        val = (op == '*') ? val * rhs : val / rhs;
        while (*p == ' ') p++;
    }
    return val;
}

/* expr = term (('+' | '-') term)*       -- lowest precedence */
int expr() {
    int val = term();
    while (*p == ' ') p++;
    while (*p == '+' || *p == '-') {
        char op = *p++;
        int rhs = term();
        val = (op == '+') ? val + rhs : val - rhs;
        while (*p == ' ') p++;
    }
    return val;
}

int main() {
    int n;
    char line[200];

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();                          /* consume leftover newline */

    printf("Enter each statement as: var = expression\n");
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);

        char *eq = strchr(line, '=');
        char varName = line[0];         /* variable is the first character */
        int idx = varName - 'a';

        p = eq + 1;                     /* start parsing right after '=' */
        value[idx] = expr();            /* evaluate with constants substituted */
        known[idx] = 1;
    }

    printf("\nFinal values (after constant propagation):\n");
    for (int i = 0; i < MAX_VARS; i++) {
        if (known[i]) printf("%c = %d\n", 'a' + i, value[i]);
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

#define MAX_VARS 26          /* one slot per letter a-z */

int value[MAX_VARS];         /* value[i] = value of variable ('a'+i) */
int known[MAX_VARS];         /* known[i] = 1 if that variable has been defined */

char *p;                     /* cursor into the expression string being parsed */

int expr();                  /* forward declarations for recursive descent */

/* factor = NUMBER | VARIABLE | '(' expr ')' */
int factor() {
    while (*p == ' ') p++;              /* skip spaces */

    if (isdigit(*p)) {                  /* number literal */
        int val = 0;
        while (isdigit(*p)) val = val * 10 + (*p++ - '0');
        return val;
    }
    if (isalpha(*p)) {                  /* variable reference */
        int idx = *p - 'a';
        p++;
        return value[idx];              /* substitute its known value */
    }
    if (*p == '(') {                    /* parenthesized sub-expression */
        p++;                            /* skip '(' */
        int val = expr();
        while (*p == ' ') p++;
        if (*p == ')') p++;             /* skip ')' */
        return val;
    }
    return 0;
}

/* term = factor (('*' | '/') factor)*   -- handles precedence of * / */
int term() {
    int val = factor();
    while (*p == ' ') p++;
    while (*p == '*' || *p == '/') {
        char op = *p++;
        int rhs = factor();
        val = (op == '*') ? val * rhs : val / rhs;
        while (*p == ' ') p++;
    }
    return val;
}

/* expr = term (('+' | '-') term)*       -- lowest precedence */
int expr() {
    int val = term();
    while (*p == ' ') p++;
    while (*p == '+' || *p == '-') {
        char op = *p++;
        int rhs = term();
        val = (op == '+') ? val + rhs : val - rhs;
        while (*p == ' ') p++;
    }
    return val;
}

int main() {
    int n;
    char line[200];

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();                          /* consume leftover newline */

    printf("Enter each statement as: var = expression\n");
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);

        char *eq = strchr(line, '=');
        char varName = line[0];         /* variable is the first character */
        int idx = varName - 'a';

        p = eq + 1;                     /* start parsing right after '=' */
        value[idx] = expr();            /* evaluate with constants substituted */
        known[idx] = 1;
    }

    printf("\nFinal values (after constant propagation):\n");
    for (int i = 0; i < MAX_VARS; i++) {
        if (known[i]) printf("%c = %d\n", 'a' + i, value[i]);
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