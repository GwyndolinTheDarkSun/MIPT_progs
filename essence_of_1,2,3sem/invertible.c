#include <stdio.h>
#include <stdlib.h>
#define cor0(x) ((x) > -1e-6 && (x) < 1e-6 ? 0 : (x))

int main() {
    int m, i, j, k, y;
    double **A, coef;
    scanf("%d", &m);
    A = (double**)malloc(m * sizeof(double*));
    for (i = 0; i < m; i++) {
        A[i] = (double*)calloc(2 * m , sizeof(double));
        A[i][i + m] = 1;
        for (j = 0; j < m; j++) {
            scanf("%lg", &A[i][j]);
        }
    }
    for (k = 0; k < m; k++) {
        for (i = 0; i < m; i++) {
            if (cor0(A[i][k]) != 0) {
                for (j = 0; j < k && cor0(A[i][j]) == 0; j++);
                if (j == k) {
                    break;
                }
            }
        }
        if (i == m)
            break;
        for (j = 0; j < m; j++) {
            if (j != i) {
                coef = A[j][k] / A[i][k];
                for (y = k; y < 2 * m; y++) {
                    A[j][y] -= coef * A[i][y];
                }
            }
        }
    }
    if (k == m) {
        for (k = 0; k < m; k++) {
            for (i = 0; cor0(A[i][k]) == 0; i++);
            for (j = m; j < 2 * m; j++) {
                printf("%lg ", cor0(A[i][j] / A[i][k]));
            }
            printf("\n");
        }
    } else {
        printf("NO\n");
    }
    for (i = 0; i < m; i++)
        free(A[i]);
    free(A);
    return 0;
}
