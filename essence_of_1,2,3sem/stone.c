#include <stdio.h>

int main() {
    unsigned a, b, c;
    scanf("%u", &a);
    b = 1;
    c = 1;
    while (!(a & 1) && a) {
        a >>= 1;
        b <<= 1;
    }
    if (a)
        a--;
    while (!(a & 1) && a) {
        a >>= 1;
        c <<= 1;
    }
    if (a == 1) {
        printf("%u %u\n", c, b);
    } else {
        printf("-1\n");
    }
    return 0;
}