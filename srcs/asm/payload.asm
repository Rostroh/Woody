DEFAULT REL

section .text
global _start

_start:
	push rdx
;	push rax
;	push rbx
;	push rsi
;	push rcx

	mov rax,1
	mov rbx,1

	push 0x000a
	push '....'
	push 'DY'
	push 'WOO'
	push '....'
	mov rsi, rsp
	mov rdx, 33
	syscall

	pop rax
	pop rax
	pop rax
	pop rax
	pop rax

;	pop rcx
;	pop rsi
;	pop rbx
;	pop rax
	pop rdx

;	push 0x00001060

