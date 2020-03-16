#include <stdio.h>

int main() {
    int a, i;
    char S[] = "---------";
    scanf("%o", &a);
    for (i = 6; i >= 0 ; i -= 3) {
        if ((a >> i) & 4)
            S[6 - i] = 'r';
        if ((a >> i) & 2)
            S[7 - i] = 'w';
        if ((a >> i) & 1)
            S[8 - i] = 'x';
    }
    puts(S);
    return 0;
}
