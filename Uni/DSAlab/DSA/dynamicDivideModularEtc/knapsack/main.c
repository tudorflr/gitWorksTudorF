#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;   // e codu lui joldi, dar l am studiat si asa rescris unele parti sa retin
} ItemT;

enum { DONT_TAKE = 0, TAKE = 1 };

int max(int a, int b) {
    return (a > b) ? a : b;
}

int **allocMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix) {
        matrix[0] = (int *)malloc(rows * cols * sizeof(int));
        for (int i = 1; i < rows; ++i) {
            matrix[i] = matrix[i - 1] + cols;
        }
    }
    return matrix;
}

void printMatrix(const char *msg, int **m, const int r, const int c) {
    printf("%s\n", msg);
    for (int i = 0; i <= r; i++) {
        for (int j = 0; j <= c; j++) {
            printf("%02d ", m[i][j]);
        }
        printf("\n");
    }
}

int solveKnapsack(int W, int n, ItemT item[], int **taken) {
    int **K = allocMatrix(n + 1, W + 1);

    for (int w = 0; w <= W; w++) {
        K[0][w] = 0;
        taken[0][w] = 0;
    }
    for (int i = 0; i <= n; i++) {
        K[i][0] = 0;
        taken[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (item[i].weight <= w) {
                K[i][w] = max(K[i - 1][w], item[i].value + K[i - 1][w - item[i].weight]);
                if (K[i - 1][w] >= K[i][w])
                    taken[i][w] = DONT_TAKE;
                else
                    taken[i][w] = TAKE;
            } else {
                K[i][w] = K[i - 1][w];
                taken[i][w] = DONT_TAKE;
            }
        }
    }

    int optimum = K[n][W];
    return optimum;
}

int main() {
    int W = 50;
    int n = 3;

    ItemT items[] = {
        {0, 0},
        {60, 10},
        {100, 20},
        {120, 30}
    };

    int **taken = allocMatrix(n + 1, W + 1);

    int max_value = solveKnapsack(W, n, items, taken);

    // Print the result
    printf("Maximum value in knapsack = %d\n", max_value);

    free(taken[0]);
    free(taken);

    return 0;
}
