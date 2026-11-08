#include <stdio.h>
#include <string.h>

#define MAX 10

int n;
int eps[MAX][MAX];          // eps[i][j] = 1 only if q_i --e--> q_j
int visited[MAX];

void epsilon_closure(int s) {
    visited[s] = 1;
    for (int t = 0; t < n; t++)
        if (eps[s][t] && !visited[t])
            epsilon_closure(t);
}

int main() {
    int i, j;
    char entry[10];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("\nEnter transition matrix.\n");
    printf("Type 1 for epsilon transition. Anything else (0, 2, a, b...) is ignored.\n\n");

    for (i = 0; i < n; i++) {
        printf("q%d -> ", i);
        for (j = 0; j < n; j++) {
            scanf("%9s", entry);                    // read as text, never fails
            eps[i][j] = (strcmp(entry, "1") == 0);  // only "1" means epsilon
        }
    }

    printf("\n----- Epsilon Closures -----\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) visited[j] = 0;
        epsilon_closure(i);

        printf("e-closure(q%d) = { ", i);
        for (j = 0; j < n; j++)
            if (visited[j]) printf("q%d ", j);
        printf("}\n");
    }
    return 0;
}