#include <stdio.h>

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int memoizedCutRodAux(int p[], int n, int r[]) {
    if (r[n] >= 0) {
        return r[n];
    }

    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = -1;
        for (int i = 1; i <= n; i++) {
            q = max(q, p[i] + memoizedCutRodAux(p, n - i, r));
        }
    }

    r[n] = q;
    return q;
}

int memoizedCutRod(int p[], int n, int r[]) {
    for (int i = 0; i <= n; i++) {
        r[i] = -1;
    }
    return memoizedCutRodAux(p, n, r);
}

int main() {
    int arr[25];
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 4;
    printf("Max: %d", memoizedCutRod(p, n, arr));
    return 0;
}
