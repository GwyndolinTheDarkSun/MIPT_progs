#include <stdio.h>
#include <stdlib.h>

void getMinor (int **A, int **D, int m, int last) {
    int i, j, l;
    for (i = 1; i <= m; i++) {
        l = 0;
        for (j = 0; j <= m; j++) {
            if (j != last) {
                D[i - 1][l] = A[i][j];
                l++;
            }
        }
    }
}
int Determinant (int **A, int m) {
    int i, znak;
    int **D, sum;
    if (m == 1) {
        return A[0][0];
    }
    sum = 0;
    znak = 1;
    D = (int**)malloc((m - 1) * sizeof(int*));
    for (i = 0; i < m - 1; i++) {
        D[i] = (int*)malloc((m - 1) * sizeof(int));
    }
    for (i = 0; i < m; i++) {
        getMinor(A, D, m - 1, i);
        sum += znak * A[0][i] * Determinant(D, m - 1);
        znak = -znak;
    }
    for (i = 0; i < m - 1; i++)
        free(D[i]);
    free(D);
    return sum;
}

int main() {
    int m, i, j;
    int **A;
    scanf("%d", &m);
    A = (int**)malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) {
        A[i] = (int*)malloc(m * sizeof(int));
        for (j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("%d\n", Determinant(A, m));
    for (i = 0; i < m; i++)
        free(A[i]);
    free(A);
    return 0;
}
