%include "io.asm"
section .data use32 class=DATA
s1 db "All right!", 0
s2 db " > ", 0
s3 db " + ", 0
s4 db " = ", 0

section .text use32 class=CODE
; процедура принимает значения через регистры ebx, ecx, edx , которые выступают сторонами треугольника , 
; edx сравнивается с суммой ebx и ecx возвращает через регистр eax 0 в случае ошибки или 1 в случае успеха 

proc: 
	mov eax, ebx
	add eax, ecx ; получаем сумму 2-х сторон
	cmp edx, eax ; сравниваем сумму двух сторон с третьей стороной 
	jbe where ; если сумма меньше третьей , то идем дальше , иначе прыгаем в конец функции 
		  ; eax - маркер наличия ошибки при какой-либо комбинации сторон
	putn edx ; далее выводим сообщение об ошибке , предварительно упорядочив слагаемые по неубыванию 
	puts s2
	cmp ebx, ecx
	jbe where1
	xchg ebx, ecx
where1:
	putn ebx
	puts s3
	putn ecx
	puts s4
	putn eax
	mov eax, 0
	ret
where:
	mov eax, 1
	ret
	
global _start
_start:
	getn ebx
	getn ecx
	getn edx
	call proc ; стороны a + b ? c
	cmp eax, 0
	je exit1
	xchg ebx, edx
	call proc ; стороны c +  b ? a
	cmp eax, 0
	je exit1
	xchg ecx, edx
	call proc ; стороны c + a ? b
	cmp eax, 0
	je exit1
	puts s1 ; выводим сообщение о том , что все в порядке , если после всех возможных сравнений через регистр eax функция не вернула 0
exit1:
	exit 0