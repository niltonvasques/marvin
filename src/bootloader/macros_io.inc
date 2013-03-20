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

;	Description: Macros usefuls for handled Input/Output
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013

  ;;This macro print a text on screen
  ;; Arg 1 is a text string
%macro MACRO_PRINT32 1

	    mov si, word %1  
	    mov ax, 0xb800	; text video memory
	    mov es, ax	; this say where start the segment memory video
	    jmp %%sprint ;; When you use macros, labels and variables needed declared with %%, otherwise error: symbol redefined occured
      %%dochar:
	    call %%cprint	;print one character  
      %%sprint:	
	    lodsb		; string char to AL
	    cmp al, 0
	    jne %%dochar	; else we're don
	    add byte [ypos], 1
	    mov byte [xpos], 0
	    jmp %%print_done

      %%cprint:		
	    mov ah, 0x0F	; attrib = white on black
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
	    add byte [xpos], 1	; adv32ance to right
	    
	    ret
      %%print_done:
%endmacro

%macro MACRO_PRINT16 1
	    mov si, word %1
      %%print_string:
	    lodsb       ; grab a byte from SI
	    
	    or al, al  ; logical or AL by itself
	    jz %%done   ; if the result is zero, get out
	    
	    mov ah, 0x0E
	    int 0x10      ; otherwise, print out the character!
	    
	    jmp %%print_string
      %%done:
%endmacro

      ypos 		db 0
      xpos 		db 0
  
  ;;This macro clear all characters on screen
%macro MACRO_CLEAR_SCREEN 0   

	    mov ax, 0xb800	; text video memory
	    mov es, ax	; this say where start the segment memory video
	    
	    mov cx,2000 ;Word count of whole screen
	    mov ax,0 ;Zero pattern for the screen
	    mov di,ax ;Set starting address
	    cld ;Go in forward direction
	    rep stosw ;Clear the screen with a single string operation

%endmacro


;       mov ax, 0xb800	; look at video memory
;       mov gs, ax
;       mov bx, 0x0000	; 'W'=57 attrib=OF
;       mov ax, [gs:bx]
; 
;       mov word [reg16], ax ;look at register
;       call printreg16