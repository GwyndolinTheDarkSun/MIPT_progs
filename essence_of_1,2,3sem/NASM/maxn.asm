%include "io.asm"
section .bss use32 class=BSS
	num resd 1
section .text use32 class=CODE
global_start
_start:
	getn[num]
	mov edi, 0
	mov ebx, 0
	mov ecx, 0
cycle:  cmp edi, [num]
	jae exit_cycle
	getn eax
	mov edx, eax
	e: neg edx
		jl e
	neg edx
	cmp edx, ebx
	jge if_cycle
	mov ecx, eax
	mov ebx, edx
	if_cycle:
	inc edi
	jmp cycle
exit_cycle:
	putn ecx
	exit 0