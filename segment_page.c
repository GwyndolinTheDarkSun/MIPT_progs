#include <stdio.h>
#include <stdlib.h>
#define const1 32

typedef struct {
    unsigned numpage;
    unsigned mempage;
} page;

typedef struct {
    unsigned numsegm;
    unsigned lengthsegm;
    unsigned amount_page;
    page * pointarrpage;
} segment;

unsigned number1 (unsigned X) {
    unsigned k;
    k = 12; /* с 12 более ли менее очевидно , 32 - 10 - 10 ( потому что размер в MB)) */
    while (X > 1) {
        X >>= 1;
        k--;
    }
    return k;
}

unsigned number2 (unsigned X, unsigned a) {
    while (X > 1) {
        X >>= 1;
        a--;
    }
    return a;
}

int main() {
    unsigned X, Y, bit_num_segm, bit_num_page, logical_address, offset_segm, segm_num, bit_offset_page, page_num, offset_page, start_phys_memory_address, N, i, j;
    segment *A;
    scanf("%u%u%u", &X, &Y, &N);
    A = (segment *)malloc(N * sizeof(segment));
    bit_num_segm = number1(X); /* вычисляем количество бит под номер сегмента */
    bit_num_page = number2(Y, const1 - bit_num_segm - 10); /* число 10 получается аналогично объяснению , почему при вычислении другого размера используется 12 , но теперь у нас размер
                                      страницы в KB , поэтому от 32 мы отнимаем количество бит под сегмент и отнимаем 10 , а не 20 , как в случае с вычислением количества бит под номер сегмента ( 12 = 32 - 20 ) */
    for (i = 0; i < N; i++) {
        scanf("%u%x", &A[i].numsegm, &A[i].lengthsegm);
    }
    for (i = 0; i < N; i++) {
        scanf("%u", &A[i].amount_page);
        A[i].pointarrpage = (page *)malloc(A[i].amount_page * sizeof(page));
        for (j = 0; j < A[i].amount_page; j++) {
            scanf("%u%u", &A[i].pointarrpage[j].numpage, &A[i].pointarrpage[j].mempage);
        }
    }
    bit_offset_page = const1 - bit_num_segm - bit_num_page;
    printf("%u %u %u\n", bit_num_segm, bit_num_page, bit_offset_page);
    while (scanf("%x", &logical_address) == 1) {
        segm_num = logical_address >> (const1 - bit_num_segm);
        offset_segm = logical_address & ((1 << (const1 - bit_num_segm)) - 1);
        printf("%u:0x%x -> ", segm_num, offset_segm);
        for (i = 0; i < N && A[i].numsegm != segm_num; i++);
        if (i != N && offset_segm < A[i].lengthsegm) {
            page_num = offset_segm >> bit_offset_page;
            offset_page = logical_address & ((1 << bit_offset_page) - 1);
            printf("%u:%u.0x%x -> ", segm_num, page_num, offset_page);
            for (j = 0; j < A[i].amount_page && A[i].pointarrpage[j].numpage != page_num; j++);
            if (j != A[i].amount_page) {
                start_phys_memory_address = 1024 * Y * A[i].pointarrpage[j].mempage; /* умножаем на 1024 , потому что Y в KB */
                printf("0x%x+0x%x -> 0x%x\n", start_phys_memory_address, offset_page, start_phys_memory_address + offset_page);
            } else {
                puts("page fault");
            }
        } else
            puts("segmentation fault");
    }
    for (i = 0; i < N; i++)
        free(A[i].pointarrpage);
    free(A);
    return 0;
}
