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
      
      mov byte [BOOT_DRIVE], dl	; store drive type
      mov bx, WELCOME_MSBB_STAGE_1
      call print_string_16           

;--------------------------------------------------------------------------------
;	5- Reset the floppy disk controller.
;--------------------------------------------------------------------------------   
;Function DISK LOAD - Load sectors of disk and transfer to memory
;	params:
;	BX = offset of memory address
;	dh = number of sectors of disk to be load
;	dl = disk drive number
      mov dl, [BOOT_DRIVE]
      mov dh, 4
      mov bx, SECOND_STAGE_ADRESS
      call disk_load
      

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
      
      mov bx, JUMP_SECOND_STAGE
      call print_string_16
      
      call word 0x0:SECOND_STAGE_ADRESS

      jmp $
      
;--------------------------------------------------------------------------------
;	INCLUDES
;--------------------------------------------------------------------------------   

%include "libio16.inc"   

;--------------------------------------------------------------------------------
;	GLOBAL VARIABLES
;--------------------------------------------------------------------------------   
      
      WELCOME_MSBB_STAGE_1	db 'Started MSBB - Marvin Sad Bootloader Bash in 16-bit stage one',13,10,0
      BOOT_DRIVE 		db 0
      JUMP_SECOND_STAGE    	db 'Passing control to Stage2.',10,13,0
      
;--------------------------------------------------------------------------------
;	FILL FILE AT 512 BYTES
;	SIGN OF BOOTABLE: 0XAA55 
;--------------------------------------------------------------------------------      
      
      times 510-($-$$) db 0
      dw 0xAA55
      
