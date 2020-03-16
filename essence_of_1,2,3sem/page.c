#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned num;
    unsigned address;
} page;

int main() {
    unsigned X, N, i, bit_per_page, max_amount_page, virtual_address, page_num, offset_page;
    page *A;
    scanf("%u%u", &X, &N);
    A = (page *)malloc(N * sizeof(page));
    bit_per_page = 12; /* с 12 более ли менее очевидно , 32 - 10 - 10 ( потому что размер в MB)) */
    while (X > 1) {
        X = X >> 1;
        bit_per_page--;
    }
    max_amount_page = 1 << bit_per_page;
    for (i = 0; i < N; i++) {
        scanf("%u%x", &A[i].num, &A[i].address);
    }
    printf("%u %u\n", bit_per_page, max_amount_page);
    while (scanf("%x", &virtual_address) == 1) {
        page_num = virtual_address >> (32 - bit_per_page); /* находим номер страницы */
        offset_page = virtual_address & ((1 << (32 - bit_per_page)) - 1); /* находим смещение внутри страницы */
        printf("%u.0x%x -> ", page_num, offset_page);
        for (i = 0; i < N && A[i].num != page_num; i++);
        if (i != N) {
            printf("0x%x\n", offset_page + A[i].address);
        } else {
            puts("error");
        }
    }
    free(A);
    return 0;
}
