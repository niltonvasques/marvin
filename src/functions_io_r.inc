
print_string_r:
      lodsb        ; grab a byte from SI      
      or al, al  ; logical or AL by itself
      jz .done   ; if the result is zero, get out      
      mov ah, 0x0E
      int 0x10      ; otherwise, print out the character!      
      jmp print_string_r
 .done:
      ret
      
;-------------------------------------------------------
;	This print an hexadecimal in ASCII 
;-------------------------------------------------------
  
printreg16_r:
      mov di, outstr16
      mov ax, [reg16]
      mov si, hexstr
      mov cx, 4		; four places
hexloop:
      rol ax, 4		; leftmost will
      mov bx, ax		; become
      and bx, 0x0F		; rightmost
      mov bl, [si + bx]	; index into hexstr
      mov [di], bl		
      inc di
      dec cx
      jnz hexloop  
      
      mov si, outstr16
      call print_string_r
      ret
      
      hexstr	db '0123456789ABCDEF'
      outstr16	db '0000',13,10, 0	;register value string
      reg16	dw	0	; pass values to printreg16