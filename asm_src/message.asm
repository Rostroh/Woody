global _start
_start:
	nop
	nop
	nop
	nop
;	push rcx
;	push rax
	push rdx
	jmp short string

code:
	pop rsi

	xor rax, rax
	mov al, 1
	mov rdi, rax
	mov rdx, rdi
	add rdx, 13
	syscall

	pop rdx
	jmp 0xAAAAAAAA

string:
	call code
	db '....WOODY....',0x0A

