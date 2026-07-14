#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *input, *output;
    char ch, word[20];
    int line = 1, token = 1, i, isKeyword;

    // List of keywords
    char keywords[6][10] = {
        "int", "main", "if", "else", "do", "while"
    };

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(output, "Line No.\tToken No.\tToken Type\tLexeme\n\n");

    while ((ch = fgetc(input)) != EOF) {

        // Skip spaces and tabs
        if (ch == ' ' || ch == '\t')
            continue;

        // New line
        if (ch == '\n') {
            line++;
            continue;
        }

        // Operators
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '=') {
            fprintf(output, "%d\t\t%d\t\tOperator\t%c\n",
                    line, token++, ch);
            continue;
        }

        // Special symbols
        if (ch == ';' || ch == '{' || ch == '}' ||
            ch == '(' || ch == ')' || ch == '%' ||
            ch == '!') {
            fprintf(output, "%d\t\t%d\t\tSpecial\t\t%c\n",
                    line, token++, ch);
            continue;
        }

        // Numbers
        if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(input)) != EOF && isdigit(ch))
                word[i++] = ch;

            word[i] = '\0';

            fprintf(output, "%d\t\t%d\t\tNumber\t\t%s\n",
                    line, token++, word);

            if (ch != EOF)
                fseek(input, -1, SEEK_CUR);

            continue;
        }

        // Identifiers or Keywords
        if (isalpha(ch) || ch == '_') {
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(input)) != EOF &&
                   (isalnum(ch) || ch == '_'))
                word[i++] = ch;

            word[i] = '\0';

            isKeyword = 0;

            for (int k = 0; k < 6; k++) {
                if (strcmp(word, keywords[k]) == 0) {
                    isKeyword = 1;
                    break;
                }
            }

            if (isKeyword)
                fprintf(output, "%d\t\t%d\t\tKeyword\t\t%s\n",
                        line, token++, word);
            else
                fprintf(output, "%d\t\t%d\t\tIdentifier\t%s\n",
                        line, token++, word);

            if (ch != EOF)
                fseek(input, -1, SEEK_CUR);
        }
    }

    fclose(input);
    fclose(output);

    printf("Lexical analysis completed.\n");
    return 0;
}