#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned num;
    unsigned address;
    unsigned length;
} segment;

int main() {
    unsigned X, N, i, bit_per_segm_num, max_amount_segm, logical_address, segm_num, offset_segm;
    segment *A;
    scanf("%u%u", &X, &N);
    A = (segment *)malloc(N * sizeof(segment));
    bit_per_segm_num = 12; /* с 12 более ли менее очевидно , 32 - 10 - 10 ( потому что размер в MB)) */
    while (X > 1) {
        X = X >> 1;
        bit_per_segm_num--;
    }
    max_amount_segm = 1 << bit_per_segm_num;
    for (i = 0; i < N; i++) {
        scanf("%u%x%x", &A[i].num, &A[i].address, &A[i].length);
    }
    printf("%u %u\n", bit_per_segm_num, max_amount_segm);
    while (scanf("%x", &logical_address) == 1) {
        segm_num = logical_address >> (32 - bit_per_segm_num);
        offset_segm = logical_address & ((1 << (32 - bit_per_segm_num)) - 1);
        printf("%u:0x%x -> ", segm_num, offset_segm);
        for (i = 0; i < N && A[i].num != segm_num; i++);
        if (i != N && offset_segm < A[i].length) {
            printf("0x%x\n", offset_segm + A[i].address);
        } else {
            puts("error");
        }
    }
    free(A);
    return 0;
}
