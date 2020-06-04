section .data

section	.text
	global asmMultiply	;multiply(int a, int b)

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
