#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];
int i = 0;

int E(), EP(), T(), TP(), F();

int main() {
    printf("Recursive descent parsing for the grammar\nHere the '@' is use for Epsilon:\n");
    printf("E->TE'\nE'->+TE'/@\nT->FT'\nT'->*FT'/@\nF->(E)/id\n\n");
    printf("Enter string: ");
    scanf("%s", input);

    if (E() && input[i] == '\0')
        printf("String is accepted\n");
    else
        printf("String is not accepted\n");

    return 0;
}

int E()  { return T() && EP(); }

int EP() { 
    if (input[i] == '+') { i++; return T() && EP(); }
    return 1; 
}

int T()  { return F() && TP(); }

int TP() { 
    if (input[i] == '*') { i++; return F() && TP(); }
    return 1; 
}

int F()  { 
    if (input[i] == '(') {
        i++;
        if (E() && input[i] == ')') { i++; return 1; }
        return 0;
    }
    if (isalpha(input[i])) { i++; return 1; }
    return 0;
}

/*
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];
int i = 0;

int E(), EP(), T(), TP(), F();

int main() {
    printf("ENTER EXPRESSION: ");
    scanf("%99s", input);
    printf("\n");

    if (E() && input[i] == '\0')
        printf("\nParsing Successful.\n");
    else
        printf("\nParsing Failed.\n");

    return 0;
}

int E() {
    printf("E -> T EP\n");
    return T() && EP();
}

int EP() {
    if (input[i] == '+') {
        printf("EP -> + T EP\n");
        i++;
        return T() && EP();
    }
    printf("EP -> ε\n");
    return 1;
}

int T() {
    printf("T -> F TP\n");
    return F() && TP();
}

int TP() {
    if (input[i] == '*') {
        printf("TP -> * F TP\n");
        i++;
        return F() && TP();
    }
    printf("TP -> ε\n");
    return 1;
}

int F() {
    if (input[i] == '(') {
        printf("F -> ( E )\n");
        i++;
        if (E() && input[i] == ')') { i++; return 1; }
        return 0;
    }
    if (isalpha(input[i])) {
        printf("F -> id\n");
        i++;
        return 1;
    }
    return 0;
}
    */