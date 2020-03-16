#include <stdio.h>

double a;

int main(void) {
	scanf("%lg", &a);
	__asm (
		"fldpi\n"
		"fmull a\n"
		"movl $180, a\n"
		"fidivl a\n"
		"fsin\n"
		"fstpl a\n"
	);
	printf("%lg\n", a);
	return 0;
} 
