section .data
section	.text
    global asmPrint	;must be declared for linker (ld)
asmPrint: ;tell linker entry point
	push ebp ;enter 0,0
	mov ebp,esp ;enter 0,0
	mov	ecx, [EBP+8];message
	mov	edx, [EBP+12];message length
	mov	ebx,1	;file descriptor (stdout)
	mov	eax,4	;system call number (sys_write)
	int	0x80	;call kernel
	mov ebp,esp ;Reset Stack  (leave)
	pop ebp ;Restore old EBP  (leave)	
	ret
	
asmMultiply:
	push	ebp			;enter 0,0
	mov		ebp, esp 	;enter 0,0

	mov		eax, [EBP + 8]	;valor a
	mov		ecx, [EBP + 12]	;valor b

	mul 	ecx

	mov		edx, 0			;(edx:eax)
	mov		ecx, 255	;para dividir por 255

	div		ecx

	mov		ebp, esp 	;reinicio el EBP a su posicion de partida
	pop		ebp			;restauro el EBP0 viejo

	ret
