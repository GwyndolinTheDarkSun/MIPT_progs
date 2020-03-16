#include <stdio.h>
#define const1 12500000
#define BIT1(x) ((x) >> 3)
#define BIT2(x) ((x) & 7)

int main() {
    static char A[const1 + 1] = {0};
    unsigned a, n, b, i, j, count, curr, num;
    scanf("%u %u", &a, &n);
    count = 0;
    for (i = 0; i < a; i++) {
        scanf("%u", &b);
        for (j = b; j < n; j += b, b++) {
            curr = BIT1(j);
            num = BIT2(j);
            if (!((A[curr] >> num) & 1)) {
                A[curr] |= 1 << num;
                count++;
            }
        }
    }
    printf("%u\n", count);
    return 0;
}
