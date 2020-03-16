#include <stdio.h>

int main() {
    int i, j, N, s, a;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        s = 0;
        for (j = 0; j < N; j++) {
            scanf("%d", &a);
            if (i != j)
                s += a;
        }
        if (s % 2 != 0) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
