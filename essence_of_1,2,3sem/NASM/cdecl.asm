section .data

a11_ equ 8
a12_ equ 12
a13_ equ 16
a21_ equ 20
a22_ equ 24
a23_ equ 28
a31_ equ 32
a32_ equ 36
a33_ equ 40

section .text

;parameters: %1, %2, %3
%macro det3_macro 3
        mov ecx, [ebp + %1]
        imul ecx, [ebp + %2]
        imul ecx, [ebp + %3]
%endmacro

global det3
det3: 
        push ebp ; пролог
	mov ebp, esp

        det3_macro a11_, a22_, a33_ ; в ecx храним наш ответ , считаем     ;определитель как сумму диагоналей , наклоненных под 3Pi/4 , из ;которых вычитаем сумму диагоналей , наклоненных под Pi/4 , сейчас ;считаем первую диагональ под 3Pi/4 ; a[1][1]
        mov eax, ecx

        det3_macro a12_, a23_, a31_
        add eax, ecx

        det3_macro a13_, a21_, a32_; третья диагональ 
        add eax, ecx

        det3_macro a13_, a22_, a31_ ; первая диагональ под Pi/4 , вычитаем из ;посчитанной ранее суммы диагоналей под 3Pi/4
        sub eax, ecx

        det3_macro a11_, a23_, a32_ ; вычитаем вторую диагональ 
        sub eax, ecx

        det3_macro a33_, a21_, a12_ ; вычитаем третью диагональ 
        sub eax, ecx

        mov esp, ebp ; эпилог
	pop ebp
        ret ; предполагаем , что стек очищается в основной программе 