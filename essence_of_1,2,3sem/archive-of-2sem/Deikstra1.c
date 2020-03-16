#include <stdio.h>

int main() {
    int A[100][100] = {{0}};
    int B[100] = {0};
    int i, j, N;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
            if (i != j)
                B[i] += A[i][j];
        }
    }
    for (i = 0; i < N; i++) {
        if (B[i] % 2 != 0) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
