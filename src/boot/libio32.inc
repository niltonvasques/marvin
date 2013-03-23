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

;	Description: Library for 32-bit Protected mode functions
;	Author: Nilton Vasques
;	Date: 22 - 03 - 2013
[ bits 32]
      ; Define some constants
      VIDEO_MEMORY 	equ 0xB8000 
      WHITE_ON_BLACK 	equ 0x0F
      
print_string_32:
      pusha			; Stores registers in stack
      mov edx , VIDEO_MEMORY 	; Set edx to the start of vid mem.
      print_string_32_loop:
	    mov al, [ebx]
				        ; Store the char at EBX in AL
	    mov ah, WHITE_ON_BLACK 	; Store the attributes in AH
	    cmp al, 0 			; if ( al == 0) , at end of string , so
	    je print_string_32_done	; jump to done
	    
	    mov [edx], ax 		; Store char and attributes at current
					; character cell.	     			
	    add ebx, 1			; Increment EBX to the next char in string.	    
	    add edx, 2			; Move to next character cell in vid mem.
	    
	    
	    jmp print_string_32_loop	; loop around to print the next char.	    
      print_string_32_done:
	    popa			; Restore registers 
	    ret	    			; Return from the function
	    
print_char_32:
      pusha			; Stores registers in stack
      mov edx , VIDEO_MEMORY 	; Set edx to the start of vid mem.
      mov al, [ebx]
				    ; Store the char at EBX in AL
      mov ah, WHITE_ON_BLACK 	; Store the attributes in AH
      cmp al, 0 			; if ( al == 0) , at end of string , so
      je print_string_32_done	; jump to done
      
      mov [edx], ax 		; Store char and attributes at current
				    ; character cell.	     			
      add ebx, 1			; Increment EBX to the next char in string.	    
      add edx, 2			; Move to next character cell in vid mem.
      popa			; Restore registers 
      ret	    			; Return from the function
	    
clear_screen_32:      
      mov cx,2000 ;Word count of whole screen
      mov edx, VIDEO_MEMORY
      clear:
      mov ax, ' '
      mov [edx], ax
      dec cx
      add edx, 2
      cmp cx, 0
      jnz clear
      ret

