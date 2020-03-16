%include "io.asm"

section .text use32 class=CODE

global _start
_start:
	mov ecx, 1
cycle:  mov ebx, 0
	mov edx, 1
	cycle1: 
		add ebx, ecx
		cmp ebx, 9
		ja if_cycle
		putc ' '
		if_cycle:
		putn ebx
		putc ' '
		inc edx
		cmp edx, 11
		jb cycle1
	inc ecx
	newln
	cmp ecx, 11
	jb cycle
	exit 0