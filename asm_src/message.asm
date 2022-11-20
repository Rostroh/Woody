global _start
_start:
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
	jmp 0xAAAAAAAA  ;remove this 

string:
	call code
	db '....WOODY....',0x0A
