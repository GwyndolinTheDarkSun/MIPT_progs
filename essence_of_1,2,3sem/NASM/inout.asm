section .bss

buf	resb 10
max	equ $ - buf
len	resd 1

section .text

global _start
_start:
	; ssize_t read(int fd, void *buf, size_t count);
	mov eax, 3		; read
	mov ebx, 0		; stdin
	mov ecx, buf
	mov edx, max
	int 0x80
	mov [len], eax

	; ssize_t write(int fd, const void *buf, size_t count);
	mov eax, 4		; write
	mov ebx, 1		; stdout
;	mov ecx, buf
	mov edx, [len]
	int 0x80

	; void _exit(int status);
	mov eax, 1		; _exit
	mov ebx, 0
	int 0x80
