#include <stdio.h>

int main() {
    int i, a;
    scanf("%d", &a);
    for (i = 7; i >= 0; i--) {
        putchar(((a >> i) & 1) + '0');
    }
    putchar('\n');
    return 0;
}
