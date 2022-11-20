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

;	xor rax, rax
;	add rax, 60
;	xor rdi, rdi
	pop rdx
	;push 0x60100000
	jmp 0xAAAAAAAA
	;jmp $-412
;	syscall

string:
	call code
	db '....WOODY....',0x0A
