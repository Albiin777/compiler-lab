#include <stdio.h>
#include <string.h>

char input[30], stack[30];
int top = 0, pos = 0;           // top = stack size, pos = input position

void show(char *action) {
    printf("$%s\t%s$\t%s\n", stack, input + pos, action);
}

void reduce() {
    int found = 1;
    while (found) {
        found = 0;
        // E -> id
        if (top >= 2 && stack[top-2]=='i' && stack[top-1]=='d') {
            top -= 2; stack[top++] = 'E'; stack[top] = '\0';
            show("REDUCE E->id"); found = 1;
        }
        // E -> E+E
        else if (top >= 3 && stack[top-3]=='E' && stack[top-2]=='+' && stack[top-1]=='E') {
            top -= 3; stack[top++] = 'E'; stack[top] = '\0';
            show("REDUCE E->E+E"); found = 1;
        }
        // E -> E*E
        else if (top >= 3 && stack[top-3]=='E' && stack[top-2]=='*' && stack[top-1]=='E') {
            top -= 3; stack[top++] = 'E'; stack[top] = '\0';
            show("REDUCE E->E*E"); found = 1;
        }
        // E -> (E)
        else if (top >= 3 && stack[top-3]=='(' && stack[top-2]=='E' && stack[top-1]==')') {
            top -= 3; stack[top++] = 'E'; stack[top] = '\0';
            show("REDUCE E->(E)"); found = 1;
        }
    }
}

int main() {
    puts("GRAMMAR: E->E+E | E*E | (E) | id");
    printf("Enter input string: ");
    scanf("%29s", input);

    printf("stack\tinput\taction\n");
    while (input[pos] != '\0') {
        if (input[pos] == 'i' && input[pos+1] == 'd') {
            stack[top++] = 'i';          // shift "id" as ONE token
            stack[top++] = 'd';
            pos += 2;
            stack[top] = '\0';
            show("SHIFT id");
        } else {
            char message[20];
            sprintf(message, "SHIFT %c", input[pos]);   
            stack[top++] = input[pos++]; // shift + * ( )
            stack[top] = '\0';
            show(message);
        }
        reduce();
    }

    if (top == 1 && stack[0] == 'E')
        puts("\nString ACCEPTED");
    else
        puts("\nString REJECTED");
    return 0;
}