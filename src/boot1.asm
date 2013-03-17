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

;	Description: Bootloader second stage
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013
;--------------------------------------------------------------------------------
;	1- CANONICALIZING ADDRESS 0X7C00
;--------------------------------------------------------------------------------
%include "macros_io.inc"

[bits 16]
[org 0x1000]
      jmp start
;--------------------------------------------------------------------------------
;	2- LOAD SEGMENT REGISTERS
;--------------------------------------------------------------------------------
start:
      cli
      xor ax, ax	
      mov ss, ax 		; stack starts at 0
      mov ds, ax		; set to data segment where we are loader
      mov sp, 0x9c00 		; 200h past code start      
      mov sp, ax       
      sti
      
      
;       MACRO_CLEAR_SCREEN
;       MACRO_PRINT32 welcome
      MACRO_PRINT16 welcome
      
      jmp $
      
      
      welcome db 'Welcome to Marvin OS bootstage 2', 13, 10, 0
      
      times 510-($-$$) db 0
      dw 0xAA55