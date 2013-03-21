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

;	Description: Bootloader first stage
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013

%define SECOND_STAGE_ADRESS 0x1000
;--------------------------------------------------------------------------------
;	1- CANONICALIZING ADDRESS 0X7C00
;--------------------------------------------------------------------------------
[bits 16]
[ORG 0x7c00] 		

      jmp start 
      
      

;--------------------------------------------------------------------------------
;	2- LOAD SEGMENT REGISTERS
;--------------------------------------------------------------------------------

      
start:

      cli      			; disable interrupts
      xor ax, ax 		; make it zero
      mov ds, ax 		; set DS zero
      mov es, ax
;--------------------------------------------------------------------------------
;	3- SET THE STACK POINTER
;--------------------------------------------------------------------------------      
      mov ss, ax 		; stack starts at 0
      mov ax, 0x9c00
      mov sp, ax 		; 200h past code start      
      sti			; enable interrupts
      
      mov byte [s_drive], dl	; store drive type
      mov si, welcome
      call print_string
      
      jmp reset_floppy
  
;	PRINT DRIVE BOOTED 
;	0x00 = Floppy Disk 1, 0x01 = Floppy Disk 2, 0x80 = Hard Disk
;       xor ax, ax
;       mov al, dl
;       mov word [reg16], ax
;       call printreg16      
      
;--------------------------------------------------------------------------------
;	4- Enable interrupts.
;--------------------------------------------------------------------------------         

;--------------------------------------------------------------------------------
;	5- Reset the floppy disk controller.
;--------------------------------------------------------------------------------   

reset_floppy:
      mov ah, 0
      int 0x13      
      jc read_error
      
;--------------------------------------------------------------------------------
;	6- Read boot1 sectors from the floppy.
;--------------------------------------------------------------------------------   
; INT 0x13
; AH = 02h
; AL = number of sectors to read (must be nonzero)
; CH = low eight bits of cylinder number
; CL = sector number 1-63 (bits 0-5) high two bits of cylinder (bits 6-7, hard disk only)
; DH = head number
; DL = drive number (bit 7 set for hard disk)
; ES:BX -> data buffer      
; INT 0x13 RETURNS      
; AH	Return Code 0x00 = sucess
; AL	Actual Sectors Read Count
; CF = Carry Flag  IF CF is set an error occurred

      xor bx, bx
      mov es, bx 
      mov bx, SECOND_STAGE_ADRESS	;boot1 must load in 0x1000 address
      
      mov al, 0x04
      mov ch, 0x00
      mov cl, 0x02
      mov dh, 0x00
      mov ah, 0x02
      int 0x13
      jc read_error       ;handled error if carry flag
      jmp read_done       ;done if carry flag is not set		
      
read_error: ;Handled error      
      mov al, ah	;check in AH error type
      xor ah, ah
      mov word [reg16], ax
      call printreg16    
      
      mov si, read_error_msg
      call print_string
      mov cx, word [read_count]
      dec cx
      mov word [read_count], cx
      cmp cx, 0x00
      jg reset_floppy	;try read 3 times because the problem in motor of floppy device
      jmp $
      
read_done:      
;       mov si, read_sucess_msg
;       call print_string
      

;--------------------------------------------------------------------------------
;	7- Jump to boot1 code.
;--------------------------------------------------------------------------------   
      cli
      xor ax, ax
      mov ds, ax
      mov es, ax
      mov ax, 0x9000
      mov ss, ax
      mov sp, 0xffff 
      sti
      
      mov si, s_jumping
      call print_string
      
      call word 0x0:SECOND_STAGE_ADRESS

      jmp $

;       mov cx, 10
;       
; print_buffer:
;       mov ax, word [es:bx]
;       mov word[reg16], ax      
;       push cx
;       push bx
;       call printreg16    
;       pop bx
;       pop cx
;       
;       dec cx
;       add bx, 2
;       cmp cx, 0
;       jg print_buffer
      
;--------------------------------------------------------------------------------
;	8- Functions
;--------------------------------------------------------------------------------   

print_string:
      lodsb        ; grab a byte from SI      
      or al, al  ; logical or AL by itself
      jz .done   ; if the result is zero, get out      
      mov ah, 0x0E
      int 0x10      ; otherwise, print out the character!      
      jmp print_string
 .done:
      ret
      
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
      
      mov si, outstr16
      call print_string
      ret
      
   
      hexstr	db '0123456789ABCDEF'
      outstr16	db '0000',13,10, 0	;register value string
      reg16	dw	0	; pass values to printreg16
      new_line 	db '',13,10,0
      read_count dw 3
      
      welcome db 'Marvin OS first stage...',13,10,0
      register db '0000',13,10,0
      read_error_msg	db ' Error: INT 0x13 error read sectors', 13,10, 0
      read_sucess_msg	db 'Read sucess!', 0
      s_drive db 0
      s_jumping    db 'Passing control to Stage2.',10,13,0
      
; gdt:                    ; Address for the GDT
; 
; gdt_null:               ; Null Segment
;         dd 0
;         dd 0
; gdt_code:               ; Code segment, read/execute, nonconforming
;         dw 0FFFFh
;         dw 0
;         db 0
;         db 10011010b
;         db 11001111b
;         db 0
; 
; gdt_data:               ; Data segment, read/write, expand down
;         dw 0FFFFh
;         dw 0
;         db 0
;         db 10010010b
;         db 11001111b
;         db 0
; gdt_end:                ; Used to calculate the size of the GDT
; gdt_desc:                       ; The GDT descriptor
;         dw gdt_end - gdt - 1    ; Limit (size)
;         dd gdt                  ; Address of the GDT
      
      times 510-($-$$) db 0
      dw 0xAA55
      
