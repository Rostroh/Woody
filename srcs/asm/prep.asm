DEFAULT REL

section .text
global _start

_start:
	push rdi
	push rsi
	push rdx
	push rcx

	mov rdi, 0xAAAAAAAA
	mov rsi, 0xBBBBBBBB
	mov rdx, 0xCCCCCCCC
	mov rcx, 0xDDDDDDDD

	pop rcx
	pop rdx
	pop rsi
	pop rdi

