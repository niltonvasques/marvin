;This file is part of Marvin OS project.
; 
;Marvin OS is free software: you can redistribute it and/or modify
;it under the terms of the GNU General Public License as published by
;the Free Software Foundation, either version 3 of the License, or
;(at your option) any later version.

;Marvin OS is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.

;You should have received a copy of the GNU General Public License
;along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.

;	Description: Library of string manipulation functions
;	Author: Nilton Vasques
;	Date: 15 - 03 - 2013
strcmp:
.loop:
      mov al, [si]   ; grab a byte from SI
      mov bl, [di]   ; grab a byte from DI
      cmp al, bl     ; are they equal?
      jne .notequal  ; nope, we're done.

      cmp al, 0  ; are both bytes (they were equal before) null?
      je .done   ; yes, we're done.

      inc di     ; increment DI
      inc si     ; increment SI
      jmp .loop  ; loop!

.notequal:
      clc  ; not equal, clear the carry flag
      ret

.done: 	
      stc  ; equal, set the carry flag
      ret
      
hex2str:
      mov di, outhex2str
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
      
      ret
      
bin2ascii:
      mov di, outbin2ascii
      mov si, hexstr
      add di, 4
      mov cx, 5
      
binloop:
      cmp ax, 0
      jle .done
      xor dx, dx
      mov bx, 10
      div bx
      mov bx, dx
      mov bl, [si + bx]
      mov [di], bl
      dec di
      dec cx
      jnz binloop
.done:
      ret
      
      hexstr		db '0123456789ABCDEF'
      outhex2str	db '0000',13,10, 0	;register value string
      reg16		dw	0	; pass values to printreg16
      outbin2ascii	db '     ', 0