#include <stdio.h>
#include <limits.h>

#define MAXN 10
#define INFTY INT_MAX


void TravSMan(int n, int c[MAXN][MAXN], int i, int tour[MAXN+1], int *cost) {
    int p[MAXN];
    int v, vmin;  // Si asta i a lu joldos, tot asa am procedat
    int costmin;

    for (int k = 1; k <= n; k++) {
        p[k] = 0;
    }
    *cost = 0;
    p[i] = 1;
    tour[1] = i;
    v = i;

    for (int k = 1; k < n; k++) {
        costmin = INFTY;

        for (int j = 1; j <= n; j++) {
            if (p[j] == 0 && c[v][j] < costmin) {
                costmin = c[v][j];
                vmin = j;
            }
        }

        *cost += costmin;
        tour[k+1] = vmin;
        p[vmin] = 1;
        v = vmin;
    }

    tour[n+1] = i;
    *cost += c[v][i];
}

int main() {
    int n;
    int tourCost;
    int tour[MAXN + 1];
    int c[MAXN][MAXN];

    printf("\nNo. of nodes in the graph = ");
    scanf("%d", &n);
    while (getchar() != '\n');

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] = INFTY;
        }
    }

    printf("\nInput costs for edges with tail\nat node i and head at node j > i.\n");
    printf("\nEnd input by entering 0\n");
    for (int i = 1; i <= n - 1; i++) {
        while (1) {
            printf("Node adjacent to node %d = ", i);
            int j;
            scanf("%d", &j);
            while (getchar() != '\n');
            if (j != 0) {
                printf("Cost of edge (%d,%d) = ", i, j);
                scanf("%d", &c[i][j]);
                while (getchar() != '\n');
                c[j][i] = c[i][j];
            } else {
                break;
            }
        }
    }

    TravSMan(n, c, 1, tour, &tourCost);
    printf("\nTour cost = %d\n", tourCost);
    printf("\nTour is: ");
    for (int i = 1; i <= n + 1; i++) {
        printf("%3d ", tour[i]);
    }
    printf("\n");

    while (getchar() != '\n');
    return 0;
}
