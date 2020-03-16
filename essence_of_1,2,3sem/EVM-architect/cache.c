#include <stdio.h>

int NOD(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    int n, i, j, d, k, sum, count;
    static int A[1024][1024], B[1024][1024];
    scanf("%d %d", &n, &d);
    count = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++) {
            A[j][i] = A[i][j] = NOD(i + 1, j + 1);
            B[j][i] = B[i][j] = NOD(n - i + 1, n - j + 1);
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            sum = 0;
            for (k = 0; k < n; k++) {
                sum += A[i][k] * B[j][k];
            }
            if (sum % d == 0)
                count++;
        }
    printf("%d\n", count);
    return 0;
}
