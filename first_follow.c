#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];

void FIRST(char c);
void FOLLOW(char c);
void result(char c);

int main()
{
    int i, choice;
    char c;

    printf("Enter the no. of productions : ");
    scanf("%d", &nop);

    printf("\nEnter productions like E=TX and epsilon as #\n\n");

    for (i = 0; i < nop; i++)
    {
        printf("Enter production Number %d : ", i + 1);
        scanf("%s", prod[i]);
    }

    do
{
    int opt;

    m = 0;
    memset(res, '\0', sizeof(res));

    printf("\n1. Find FIRST");
    printf("\n2. Find FOLLOW");
    printf("\nEnter your choice : ");
    scanf("%d", &opt);

    printf("Enter the Non-Terminal : ");
    scanf(" %c", &c);

    if (!isupper(c))
    {
        printf("Invalid Non-Terminal\n");
        continue;
    }

    if (opt == 1)
    {
        FIRST(c);

        printf("FIRST(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", res[i]);
        printf("}\n");
    }
    else if (opt == 2)
    {
        FOLLOW(c);

        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", res[i]);
        printf("}\n");
    }
    else
    {
        printf("Invalid Choice\n");
    }

    printf("\nPress 1 to continue : ");
    scanf("%d", &choice);

} while (choice == 1);

    return 0;
}

void FOLLOW(char c)
{
    int i, j;

    if (prod[0][0] == c)
        result('$');

    for (i = 0; i < nop; i++)
    {
        for (j = 2; prod[i][j] != '\0'; j++)
        {
            if (prod[i][j] == c)
            {
                if (prod[i][j + 1] != '\0')
                {
                    if (islower(prod[i][j + 1]) || !isupper(prod[i][j + 1]))
                        result(prod[i][j + 1]);
                    else
                        FIRST(prod[i][j + 1]);
                }

                if (prod[i][j + 1] == '\0' && c != prod[i][0])
                    FOLLOW(prod[i][0]);
            }
        }
    }
}

void FIRST(char c)
{
    int k;

    if (!isupper(c))
    {
        result(c);
        return;
    }

    for (k = 0; k < nop; k++)
    {
        if (prod[k][0] == c)
        {
            if (prod[k][2] == '#')
                result('#');
            else if (islower(prod[k][2]) || !isupper(prod[k][2]))
                result(prod[k][2]);
            else
                FIRST(prod[k][2]);
        }
    }
}

void result(char c)
{
    int i;
    for (i = 0; i < m; i++)
        if (res[i] == c)
            return;

    res[m++] = c;
}


/*
 ./a.out
Enter the no. of productions : 4

Enter productions like E=TX and epsilon as #

Enter production Number 1 : S=AB
Enter production Number 2 : A=a
Enter production Number 3 : B=b
Enter production Number 4 : A=#

1. Find FIRST
2. Find FOLLOW
Enter your choice : 1
Enter the Non-Terminal : S
FIRST(S) = { a # }

Press 1 to continue : 1

1. Find FIRST
2. Find FOLLOW
Enter your choice : 1
Enter the Non-Terminal : A
FIRST(A) = { a # }

Press 1 to continue : 1

1. Find FIRST
2. Find FOLLOW
Enter your choice : 1
Enter the Non-Terminal : B
FIRST(B) = { b }

Press 1 to continue : 1

1. Find FIRST
2. Find FOLLOW
Enter your choice : 2
Enter the Non-Terminal : S
FOLLOW(S) = { $ }

Press 1 to continue : a

1. Find FIRST
2. Find FOLLOW
Enter your choice : Enter the Non-Terminal : Invalid Non-Terminal

1. Find FIRST
2. Find FOLLOW
Enter your choice : 2
Enter the Non-Terminal : A
FOLLOW(A) = { b }

Press 1 to continue : 1

1. Find FIRST
2. Find FOLLOW
Enter your choice : 2
Enter the Non-Terminal : B
FOLLOW(B) = { $ }

Press 1 to continue : 0
s7d09@cc1-H110M-S2:~/compilerlab$ 

*/
