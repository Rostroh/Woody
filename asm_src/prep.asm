DEFAULT REL

section .text
global _start

_start:
;	push rdi	;sussy asm
;	push rsi	;sussy asm

	push rdi
	push rsi
	push rdx	;dis guy
	push rcx

	mov rdi, 0xAAAAAAAA			;prepare register for rc4
	mov rsi, 0xBBBBBBBB
	mov rdx, 0xCCCCCCCC
	mov rcx, 0xDDDDDDDD
