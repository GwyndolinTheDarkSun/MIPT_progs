%include "io.asm"
	
section .text use32 class=CODE

global _start
_start:
	getn ebx
cycle:
	shr ebx, 1
	jc if
	putc '0'
	jmp if1
	if:
	putc '1'
	if1:
	cmp ebx, 0
	jne cycle
	exit 0