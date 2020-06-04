section .data
;divisor equ 255
section .text
global mulSIMD 
mulSIMD: ; tell linker entry point
 
   
   ;Enter
   push ebp ; enter 0,0
   mov ebp,esp; enter 0,0
   
   ;Muevo valores a registro
   mov ebx,  [ebp+8]    ;EBX apunta al dato
   movd mm0, [ebx]      ;Metemos el dato en mm0
   psrlw mm0, 8         ; Dividimos mm0 x 256

   mov ebx,[ebp+12]     ;Lo mismo
   movd mm1, [ebx]
   psrlw mm1, 8

   pmullw mm0,mm1       ;multiplicamos

   mov ebx ,[ebp+8]     ;EBX apunta al primer vector      
   movd [ebx] , mm0     ;guardamos los resultados en el vector
  
   emms

   ;Leave
   mov ebp,esp 
   pop ebp ;ahora sp apunto a ip de sum
   
   ret 
  
