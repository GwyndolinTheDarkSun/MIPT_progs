section .data

Message	db "Hell, Word!",0xA
Length	equ $ - Message

section .text

global _start
_start:
	; ssize_t write(int fd, const void *buf, size_t count);
	mov eax, 4		; write
	mov ebx, 1		; stdout
	mov ecx, Message
	mov edx, Length
	int 0x80

	; void _exit(int status);
	mov eax, 1		; _exit
	mov ebx, 0
	int 0x80
