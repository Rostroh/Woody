DEFAULT REL
	global rc4
	extern malloc
	section .text
;                         RDI        RSI                 RDX      RCX           R8
;uint8_t *rc4(const char *plain, int plain_len, uint8_t *key, int klen, uint8_t *cyph)
rc4:
	push rbx
	push rdi
	push rsi
	sub rsp, 0x208

	mov r8, rdx						;save key in r8
	mov	r9, rcx						;save klen in r9
	mov r12, 256
	xor ebx, ebx
	xor ecx, ecx
	jmp init_array

init_array:
	mov rbx, rcx
	mov [rsp - 0x208 + rbx], cx			;S[i] = i

	xor edx, edx
	mov rax, rcx					;set eax for div (i)
	div r9							;i % klen

	mov al, [r8 + rdx]
	mov rbx, rcx
	mov [rsp - 0x100 + rbx], al			;T[i] = key[i%klen]

	inc rcx							;i++
	cmp rcx, r12
	jl init_array

prep_key_schedule:
	xor ecx, ecx
	xor r10, r10					;j = 0
	xor r8, r8
	xor r9, r9
key_schedule:
	mov rbx, rcx
	mov al, BYTE [rsp - 0x208 + rbx]			;r8 = s[i]
	mov dl, [rsp - 0x100 + rbx]			;r9 = s[i]
	mov r8, rax
	mov r9, rdx
	add r10, r8
	add r10, r9

	xor edx, edx
	mov rax, r10
	div r12
	mov r10, rdx					;r10 = j + s[i] + t[i] % 256

swap_1:
	xor rax, rax
	xor rdx, rdx
	mov rbx, rcx
	mov dl, [rsp - 0x208 + rbx]
	mov rbx, r10
	mov al, [rsp - 0x208 + rbx]
	mov rbx, rcx
	mov [rsp - 0x208 + rbx], al
	mov rbx, r10
	mov [rsp - 0x208 + rbx], dl

	inc rcx
	cmp rcx, r12
	jl key_schedule

prep_algo:
	xor ecx, ecx					;set rcx to 0 for next loop
	xor r8, r8						;key is useless now
	xor r9, r9						;r9 = j
algo:
	inc r8							;r8 = i
	xor edx, edx
	mov rax, r8
	div r12
	mov r8, rdx						;r8 = i % 256

	mov rbx, rdx
	mov dl, [rsp - 0x208 + rbx]				;rdx = S[i]
	add r9, rdx
	xor edx, edx
	mov rax, r9
	div r12
	mov r9, rdx						;r9 = j + S[i] % 256

swap_2:
	xor eax, eax
	xor edx, edx
	mov rbx, r8
	mov dl, [rsp - 0x208 + rbx]				;edx = s[i]
	mov rbx, r9
	mov	al, [rsp - 0x208 + rbx]				;rax = s[j]
	mov rbx, r8
	mov [rsp - 0x208 + rbx], al
	mov rbx, r9
	mov [rsp - 0x208 + rbx], dl

cont:
	mov r10, rdx
	add r10, rax					;r10 = s[i] + s[j]
	xor rdx, rdx
	mov rax, r10
	div r12
	mov r10, rdx					;r10 = s[i] + s[j] % 256

	xor edx, edx
	mov rbx, r10
	mov dl, [rsp - 0x208 + rbx]			;rdx = s[t]
	mov rbx, rcx
	xor dl, [rdi + rbx]				;k ^ txt[idx]
	mov rax, rdi
	mov [rax + rcx], dl
	nop

end_algo:
	inc rcx
	cmp rcx, rsi
	jl algo

end:
	add rsp, 0x208
	pop rsi
	pop rdi
	pop rbx
	;mov rax, r11
	ret
