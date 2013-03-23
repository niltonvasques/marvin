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

;	Description: Library Input/Output for 16-bit Real Mode
;	Author: Nilton Vasques
;	Date: 15 - 03 - 2013


;--------------------------------------------------------------------------------
;	Function GET STRING - Get an string from keyboard
;	params:
;	DI = Memory address of string buffer
;--------------------------------------------------------------------------------   
get_string16:
      xor cl, cl
      
.loop:
      mov ah, 0
      int 0x16   ; wait for keypress
      
      cmp al, 0x08    ; backspace pressed?
      je .backspace   ; yes, handle it
      
      cmp al, 0x0D  ; enter pressed?
      je .done      ; yes, we're done
      
      cmp cl, 0x3F  ; 63 chars inputted?
      je .loop      ; yes, only let in backspace and enter
      
      mov ah, 0x0E
      int 0x10      ; print out character
      
      stosb  ; put character in buffer
      inc cl
      jmp .loop
      
.backspace:
      cmp cl, 0	; beginning of string?
      je .loop	; yes, ignore the key
      
      dec di
      mov byte [di], 0	; delete character
      dec cl		; decrement counter as well
      
      mov ah, 0x0E
      mov al, 0x08
      int 10h		; backspace on the screen
      
      mov al, ' '
      int 10h		; blank character out
      
      mov al, 0x08
      int 10h		; backspace again
      
      jmp .loop	; go to the main loop
      
.done:
      mov al, 0	; null terminator
      stosb
      
      mov ah, 0x0E
      mov al, 0x0D
      int 0x10
      mov al, 0x0A
      int 0x10		; newline
      
      ret

;--------------------------------------------------------------------------------
;	Function PRINT STRING - Print an string on the screen
;	params:
;	BX = Memory address of string
;--------------------------------------------------------------------------------   
print_string_16:
      mov si, bx
print_string:
      lodsb       ; grab a byte from SI	    
      or al, al  ; logical or AL by itself
      jz .done   ; if the result is zero, get out
      
      mov ah, 0x0E
      int 0x10      ; otherwise, print out the character!
      
      jmp print_string
.done:
      ret
      
      
;--------------------------------------------------------------------------------
;	Function DISK LOAD - Load sectors of disk and transfer to memory
;	params:
;	BX = offset of memory address
;	dh = number of sectors of disk to be load
;	dl = disk drive number
;-------------------------------------------------------------------------------- 
disk_load:
      push dx
      disk_reset:
	    mov ah, 0
	    int 0x13      
	    jc disk_error
      
	    ;Setup memory address
	    push bx
	    xor bx, bx
	    mov es, bx
	    pop bx
	    
	    mov al, dh
	    mov ch, 0x00
	    mov cl, 0x02
	    mov dh, 0x00
	    mov ah, 0x02
	    
	    int 0x13
	    
	    jc disk_error       ; Handled error if carry flag
	    
	    pop dx		; Restore DX from stack
	    cmp dh, al		; if AL (sectors read ) != DH (sectors expected)
	    jne disk_error	; Handled error
	    ret
	    
      disk_error: ;Handled error      
; 	    mov al, ah	;check in AH error type
; 	    xor ah, ah
; 	    mov word [reg16], ax
; 	    call printreg16    
	    
	    mov si, DISK_ERROR_MSG
	    call print_string_16
; 	    mov cx, word [read_count]
; 	    dec cx
; 	    mov word [read_count], cx
; 	    cmp cx, 0x00
; 	    jg reset_floppy	;try read 3 times because the problem in motor of floppy device
	    jmp $
	    
      DISK_ERROR_MSG	db ' Error: INT 0x13 error read sectors', 13,10, 0
