DEFAULT REL
	global rc4

	section .text
;uint8_t *rc4(const char *plain, int plain_len, uint8_t *key, int klen)
rc4:
	push ebx
	push ecx
	;mov ebx, stab

init_s:
	mov ecx, 0
	;mov ebx, ecx
	;add ebx, 2
	cmp ecx, 256
	jne init_s

	pop ecx
	pop ebx
	ret

	section .bss
stab: resb 256
