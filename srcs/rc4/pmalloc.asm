DEFAULT REL
	global asmalloc
	extern malloc
	section .text

;void *asmalloc(int nb)
asmalloc:
	push rbx
	push rbp
	push rsp

	call malloc
	test eax, eax
	jz end
	mov word [rax], 0x39

end:
	pop rsp
	pop rbp
	pop rbx
	ret
