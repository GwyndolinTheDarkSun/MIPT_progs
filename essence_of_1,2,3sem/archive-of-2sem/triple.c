#include <stdio.h>

int main() {
    char a[12];
    unsigned long long b = 0;
    int i;
    scanf("%s", a);
    for (i = 0; a[i]; i++) {
        b = b * 3 + (a[i] - '0');
    }
    printf("%llu\n", b);
    return 0;
}
