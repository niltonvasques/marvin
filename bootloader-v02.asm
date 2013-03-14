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

;	Description: Bootloader of operating system InsanityOS
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013
  
    
[ORG 0x7c00] 		; add to offsets
  xor ax, ax 		; make it zero
  mov ds, ax 		; set DS zero
  mov ss, ax 		; stack starts at 0
  mov sp, 0x9c00 	; 200h past code start
  
  mov ax, 0xb800	; text video memory
  mov es, ax
  
  mov si, msg		; show text string
  call sprint
  
  mov ax, 0xb800	; look at video memory
  mov gs, ax
  mov bx, 0x0000	; 'W'=57 attrib=OF
  mov ax, [gs:bx]
  
  mov word [reg16], ax ;look at register
  call printreg16
  

hang:	; loop
    jmp hang
    
;------------------------------------------------------
dochar:		call cprint	;print one character
sprint:		lodsb		; string char to AL
  cmp al, 0
  jne dochar	; else we're don
  add byte [ypos], 1
  mov byte [xpos], 0
  ret
  
cprint:		mov ah, 0x0F	; attrib = white on black
  mov cx, ax		; save char/attribute
  movzx ax, byte [ypos]	
  mov dx, 160		; 2 bytes (char/attrib)
  mul dx		; for 80 columns
  movzx bx, byte [xpos] 
  shl bx, 1 		; times 2 to skip attrib
  
  mov di, 0		; start of video memory
  add di, ax		; add y offset
  add di, bx		; add x offset
  
  mov ax, cx		; restore char/attribute
  stosw			; write char/attribute
  add byte [xpos], 1	; advance to right
  
  ret
  
  ;-------------------------------------------------------
  
printreg16:
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
  call sprint
  
  ret
  
  ;-------------------------------------------------------
  
  ypos 		db 0
  xpos 		db 0
  hexstr	db '0123456789ABCDEF'
  outstr16	db '0000', 0	;register value string
  reg16		dw	0	; pass values to printreg16
  msg		db "Marvin OS", 0    
    
  
  times 510-($-$$) db 0		;Say for NASM fill binary until 510 bytes 
  db 0x55		;Bytes 510 and 511 are sign of bootsector and need has this values
  db 0xAA

  