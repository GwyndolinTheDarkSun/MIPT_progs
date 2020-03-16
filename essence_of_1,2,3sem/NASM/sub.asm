section .data use32 class=DATA

t db "%d%d", 0
t1 db "%d", 0xA, 0
a dd 0
b dd 0

section .text use32 class=CODE

extern scanf
extern printf
extern exit

global _start
_start:
	call main
	push eax
	call exit

main: 
        ; scanf(t, &a, &b);
	push b
	push a
	push t
	call scanf
	add esp, 12 ; чистим стек ( (количество вызовов push) * (4 байта - машинное слово в 32-х битной системе ) )

	mov eax, [a]
	sub eax, [b]

	; printf(t1, a - b);
	push eax
	push t1
	call printf
	add esp, 8 ; чистим стек ( (количество вызовов push) * (4 байта - машинное слово в 32-х битной системе ) ) 

	; return 0;
	mov eax, 0
	ret