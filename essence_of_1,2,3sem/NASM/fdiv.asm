section .data

t db "%lg%lg", 0 
t1 db "%lg", 0xA, 0 
a dq 0 
b dq 0 

section .text

extern scanf 
extern printf 
extern exit 

global main
main: 
	; scanf(t, &a, &b);
	push b
	push a
	push t
	call scanf
	add esp, 12

	; a = a / b;
	sub esp, 8
	fld qword [a]
	fdiv qword [b]
	fstp qword [esp]

	; printf(t1, a);
	push t1
	call printf 
	add esp, 12 

	; return 0;
	mov eax, 0
	ret