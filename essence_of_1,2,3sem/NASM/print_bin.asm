%include "io.asm"

section .bss use32 class=BSS
	
section .text use32 class=CODE

global _start
_start:
	getn ebx
	mov ecx, 32
cycle:
	rol ebx, 1
	jc if
	putc '0'
	jmp if1
	if:
	putc '1'
	if1:
	loop cycle
exit_cycle:
	exit 0