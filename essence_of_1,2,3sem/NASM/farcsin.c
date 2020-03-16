#include <stdio.h>

double a;

int main(void) {
    scanf("%lg", &a);
    __asm (
        "fldl a\n"  /*st0 = a*/
        "fldl a\n"  /*st0 = a, st1 = a*/
        "fmull a\n"  /*st0 = a^2, st1 = a*/
        "fld1\n"   /*st0 = 1, st1 = a^2, st2 = a*/
        "fsubp\n"  /*st0 = 1 - a^2, st1 = a*/
        "fsqrt\n"  /*st0 = sqrt(1 - a^2), st1 = a*/
        "fpatan\n" /*st0 = arctg(a / sqrt(1 - a^2))*/
        "fldpi\n"  /*st0 = Pi, st1 = a / arctg(a / sqrt(1 - a^2))*/
        "movl $180, a\n"
        "fidivrl a\n"  /*st0 = Pi / 180, st1 = arctg(a / sqrt(1 - a^2))*/        
        "fmulp\n"  /*st0 = (Pi / 180) * arctg(a / sqrt(1 - a^2)) = arcsin(a)*/
        "fstpl a\n"
    );
    printf("%lg\n", a);
    return 0;
}