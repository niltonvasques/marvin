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

;--------------------------------------------------------------------------------
;	Load Macros
;--------------------------------------------------------------------------------
      %include "macros_io.inc"
      
%macro MACRO_DRAW_SCREEN 0
      MACRO_CLEAR_SCREEN 

      mov byte [ypos], 2	; parameters is a offset of screen the msg will display
      mov byte [xpos], 10
      MACRO_PRINT msg		; show text string
%endmacro

;--------------------------------------------------------------------------------
;	Init of Program
;--------------------------------------------------------------------------------
    
[ORG 0x7c00] 		; add to offsets

      jmp start
      
      %include "handlers_hw.inc"
 
start:
      xor ax, ax 		; make it zero
      mov ds, ax 		; set DS zero
      mov ss, ax 		; stack starts at 0
      mov sp, 0x9c00 	; 200h past code start
      
      MACRO_DRAW_SCREEN

;--------------------------------------------------------------------------------
;	This register an callback code for take interrupt hardware of keyboard
;--------------------------------------------------------------------------------
      cli		;no interruptions
      mov bx, 0x09	;hardware interrupt #
      shl bx, 2		;I guess this is same instructions in C code like: b>>2 = b*4
      xor ax, ax	;zero it
      mov gs, ax	;start memory
      mov [gs:bx], word handler_keyboard
      mov [gs:bx+2], ds	;segment
      sti

;-------------------------------------------------------------------------
;	Switching to Protected Mode
;-------------------------------------------------------------------------
      cli	; no interrupt
      push ds	; save real mode
      
      lgdt [gdtinfo]	;load gdt register
      
      mov eax, cr0	;switch to protected mode
      or al, 1		;set protected mode
      mov cr0, eax
      
      mov bx, 0x08	;select descriptor 1
      mov ds, bx	;8h = 1000b
      
;-------------------------------------------------------------------------
;	Switching to Real Mode With a Trick for can use register of 32bits 
;-------------------------------------------------------------------------
      mov al, 0xFE
      mov cr0, eax	;by toggling bit again
      
      pop ds
      sti
      
      
      mov bx, 0x0F01		;attrib/char of smiley
      mov eax, 0x0B8000		; note 32 bit offset
      mov word [ds:eax], bx      
      
      
      jmp $	;loop forever          
    
  
;-------------------------------------------------------
;	This print an hexadecimal in ASCII 
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
  
      MACRO_PRINT outstr16
  
      ret
  
;-------------------------------------------------------------------------
;	Data Section
;-------------------------------------------------------------------------
      ypos 		db 0
      xpos 		db 0
      hexstr	db '0123456789ABCDEF'
      outstr16	db '0000', 0	;register value string
      reg16		dw	0	; pass values to printreg16
      msg		db "Bootloader of Marvin OS v0.02", 0    
      DebugMsg	db "Debug Memory >", 0
      space		db ' ', 0
      port60	dw 0
      
gdtinfo:
      dw gdt_end - gdt - 1   ;last byte in table
      dd gdt         ;start of table
      gdt        dd 0,0  ; entry 0 is always unused
      flatdesc   db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0

gdt_end:
    
;-------------------------------------------------------------------------
;	 End of bootloader
;-------------------------------------------------------------------------
  
      times 510-($-$$) db 0		;Say for NASM fill binary until 510 bytes 
      dw 0xAA55		;Bytes 510 and 511 are sign of bootsector and need has this values - This is required for some BIOses

  