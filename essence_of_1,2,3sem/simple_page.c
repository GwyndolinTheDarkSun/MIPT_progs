#include <stdio.h>
#include <stdlib.h>
#define const1 6

int main() {
    unsigned N, i, *A, t, j;
    scanf("%u", &N);
    A = (unsigned *)malloc(N * sizeof(unsigned));
    for (i = 0; i < N; i++)
        scanf("%X", &A[i]);
    scanf("%X", &t);
    j = t >> (32 - const1);
    if (j < N) {
        t = t & ((1 << (32 - const1)) - 1);
        printf("%X\n", A[j] + t);
    } else {
        puts("error");
    }
    free(A);
    return 0;
}
