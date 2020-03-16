#include <stdio.h>

int main() {
    char A[31];
    int i, s;
    double sum = 0;
    scanf("%s", A);
    for (i = 0; A[i] && A[i] != '.'; i++) {
        sum = sum * 2 + (A[i] - '0');
    }
    s = 1;
    if (A[i])
        for (++i; A[i]; i++) {
            s *= 2;
            sum += (double) (A[i] - '0') / s;
        }
    printf("%.12lg\n", sum);
    return 0;
}
