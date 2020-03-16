#include <stdio.h>
#define const1 1000000

int main () {
    static char A[const1 + 1], B[4 * const1 + 1];
    int i, j, a, k;
    scanf("%s", A);
    for (i = 0; A[i]; i++) {
        if (A[i] > '9')
            a = (A[i] - 'A') + 10;
        else
            a = A[i] - '0';
        for (j = 0; j < 4; j++)
            B[4 * i + j] = ((a >> (3 - j)) & 1) + '0';
    }
    B[4 * i] = '\0';
    for (k = 0; B[k] == '0' && B[k + 1]; k++);
    puts(B + k);
    return 0;
}
