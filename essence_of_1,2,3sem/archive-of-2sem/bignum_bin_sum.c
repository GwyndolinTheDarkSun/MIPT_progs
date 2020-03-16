#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char C[1002], D[1002], *A, *B;
    int c, d, i;
    scanf("%s%s", C, D);
    c = strlen(C);
    d = strlen(D);
    for (i = d; i > 0; i--) {
        D[i] = D[i - 1] - '0';
    }
    D[0] = 0;
    D[d + 1] = '\0';
    for (i = c; i > 0; i--) {
        C[i] = C[i - 1] - '0';
    }
    C[0] = 0;
    C[c + 1] = '\0';
    if (c < d) {
        A = D;
        B = C;
        i = c;
        c = d;
        d = i;
    } else {
        A = C;
        B = D;
    }
    for (i = c; i > 0; i--) {
        if (i > c - d) {
            A[i - 1] += (A[i] + B[d - c + i]) / 2;
            A[i] = (A[i] + B[d - c + i]) % 2 + '0';
        } else {
            A[i - 1] += A[i] / 2;
            A[i] = A[i] % 2 + '0';
        }
    }
    A[0] += '0';
    for (i = 0; i < c && A[i] == '0'; i++);
    puts(A + i);
    return 0;
}
