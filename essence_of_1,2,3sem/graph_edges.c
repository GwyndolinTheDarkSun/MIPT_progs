#include <stdio.h>

int main() {
    int A[100][100] = {{0}};
    int i, j, N, M, sum;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    sum = 0;
    for (i = 0; i < N; i++) {
        for (j = i; j < N; j++) {
            if (A[i][j] == A[j][i]) {
                sum += A[i][j];
            } else {
                printf("-1\n");
                return 0;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}