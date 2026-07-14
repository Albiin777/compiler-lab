%{
#include <stdio.h>
%}

DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD    (if|else|while|return|int|float)

%%

{KEYWORD} {
    printf("| %-10s | %-20s |\n", yytext, "Keyword");
}

{ID} {
    printf("| %-10s | %-20s |\n", yytext, "Identifier");
}

{DIGIT}+ {
    printf("| %-10s | %-20s |\n", yytext, "Number");
}

"+" {
    printf("| %-10s | %-20s |\n", yytext, "Plus operator");
}

"-" {
    printf("| %-10s | %-20s |\n", yytext, "Minus operator");
}

"*" {
    printf("| %-10s | %-20s |\n", yytext, "Multiply operator");
}

"/" {
    printf("| %-10s | %-20s |\n", yytext, "Divide operator");
}

"=" {
    printf("| %-10s | %-20s |\n", yytext, "Assignment operator");
}

[ \t\n]+    { /* Ignore whitespace */ }

. {
    printf("| %-10s | %-20s |\n", yytext, "Unknown character");
}

%%

int main()
{
    printf("| %-10s | %-20s |\n", "Lexeme", "Token Type");
    printf("----------------------------------------\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}