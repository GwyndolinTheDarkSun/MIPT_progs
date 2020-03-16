#include <stdio.h>
#include <stdlib.h>
#define cor0(x) ((x) > -1e-6 && (x) < 1e-6 ? 0 : (x))

int main() {
    int m, i, j, k, y, countrang, n;
    double **A, coef;
    scanf("%d %d", &m, &n);
    A = (double**)malloc(m * sizeof(double*));
    for (i = 0; i < m; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
        for (j = 0; j < n; j++) {
            scanf("%lg", &A[i][j]);
        }
    }
    for (k = 0; k < n; k++) {
        for (i = 0; i < m; i++) {
            if (cor0(A[i][k]) != 0) {
                for (j = 0; j < k && cor0(A[i][j]) == 0; j++);
                if (j == k) {
                    break;
                }
            }
        }
        if (i != m) {
            for (j = 0; j < m; j++) {
                if (j != i) {
                    coef = A[j][k] / A[i][k];
                    for (y = k; y < n; y++) {
                        A[j][y] -= coef * A[i][y];
                    }
                }
            }
        }
    }
    countrang = 0;
    for (i = 0; i < m; i++) {
        for (j = 0;  j < n && cor0(A[i][j]) == 0; j++);
        if (j != n)
            countrang++;
    }
    printf("%d\n", countrang);
    for (i = 0; i < m; i++)
        free(A[i]);
    free(A);
    return 0;
}
