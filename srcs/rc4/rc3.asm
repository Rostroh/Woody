DEFAULT REL
	global rc4
	extern malloc
	section .data
sz DW 256

	section .text
;                        RDI         RSI                 RDX      RCX
;uint8_t *rc4(const char *plain, int plain_len, uint8_t *key, int klen)
rc4:
	push rbx
	push rdi
	push rsi

	mov r8, rdx						;save key in r8
	mov	r9, rcx						;save klen in r9
	mov rbx, 256
	xor ecx, ecx

alloc:
	push rsi
	push rdi
	push rcx
	push rdx
	push r9

	mov rdi, rsi
	call malloc
	test eax, eax

	pop r9
	pop rdx
	pop rcx
	pop rdi
	pop rsi
	jz end
	mov r11, rax
	xor ecx, ecx

init_array:
	mov [stab + ecx], cx			;S[i] = i

	xor edx, edx
	mov rax, rcx					;set eax for div (i)
	div r9							;i % klen

	mov al, [r8 + rdx]
	mov [ttab + ecx], al			;T[i] = key[i%klen]

	inc rcx							;i++
	cmp rcx, sz
	jl init_array

prep_key_schedule:
	xor ecx, ecx
	xor r10, r10					;j = 0
	xor r8, r8
	xor r9, r9
key_schedule:
	mov al, [stab + ecx]			;r8 = s[i]
	mov dl, [ttab + ecx]			;r9 = s[i]
	mov r8, rax
	mov r9, rdx
	add r10, r8
	add r10, r9

	xor edx, edx
	mov rax, r10
	div rbx
	mov r10, rdx					;r10 = j + s[i] + t[i] % 256

swap_1:
	xor rax, rax
	xor rdx, rdx
	mov dl, [stab + ecx]
	mov al, [stab + r10]
	mov [stab + ecx], al
	mov [stab + r10], dl

	inc rcx
	cmp rcx, sz
	jl key_schedule

prep_algo:
	xor ecx, ecx					;set rcx to 0 for next loop
	xor r8, r8						;key is useless now
	xor r9, r9						;r9 = j
algo:
	inc r8							;r8 = i
	xor edx, edx
	mov rax, r8
	mov rbx, sz
	div rbx
	mov r8, rdx						;r8 = i % 256

	mov dl, [stab + r8]				;rdx = S[i]
	add r9, rdx
	xor edx, edx
	mov rax, r9
	div rbx
	mov r9, rdx						;r9 = j + S[i] % 256

swap_2:
	xor eax, eax
	xor edx, edx
	mov dl, [stab + r8]				;edx = s[i]
	mov	al, [stab + r9]				;rax = s[j]
	mov [stab + r8], al
	mov [stab + r9], dl

cont:
	mov r10, rdx
	add r10, rax					;r10 = s[i] + s[j]
	xor rdx, rdx
	mov rax, r10
	div rbx
	mov r10, rdx					;r10 = s[i] + s[j] % 256

	xor edx, edx
	mov dl, [stab + r10]			;rdx = s[t]
	xor dl, [edi + ecx]				;k ^ txt[idx]

	mov rbx, r11
	mov [rbx + rcx], dl
	;mov rax, r15
	;mov [rax + rcx], dl
	nop

end_algo:
	inc rcx
	cmp rcx, rsi
	jl algo

end:
	pop rsi
	pop rdi
	pop rbx
	mov rax, r11
	ret

	section .bss
stab: resb 264						;256 bytes are actually use, 8 bytes for memory controle
ttab: resb 256
