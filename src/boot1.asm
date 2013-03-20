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
      
%include "libio16.inc"
%include "libstr.inc"
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
;       MACRO_PRINT32 welcome
mainloop:
      MACRO_PRINT16 prompt
      
      mov di, buffer
      call get_string16
      
      mov si, buffer
      cmp byte [si], 0  ; blank line?
      je mainloop       ; yes, ignore it
      
      mov si, buffer
      mov di, cmd_version
      call strcmp
      jc .cmd_version_triggered
      
      mov si, buffer
      mov di, cmd_pmode
      call strcmp
      jc .cmd_pmode_triggered      
      
      mov si, buffer
      mov di, cmd_help
      call strcmp
      jc .cmd_help_triggered
      
      mov si, buffer
      mov di, cmd_suicide
      call strcmp
      jc .cmd_suicide_triggered
      
      mov si, buffer
      mov di, cmd_die
      call strcmp
      jc .cmd_die_triggered
      
      mov si, buffer
      mov di, cmd_ram
      call strcmp
      jc .cmd_ram_triggered
      
      call .cmd_bad_input_triggered
      
      jmp mainloop     
      
.cmd_version_triggered:
      MACRO_PRINT16 cmd_version_msg
      jmp mainloop
      
.cmd_pmode_triggered:
      MACRO_PRINT16 cmd_pmode_msg
      jmp mainloop
      
.cmd_bad_input_triggered:
      MACRO_PRINT16 buffer
      MACRO_PRINT16 cmd_bad_input_msg
      jmp mainloop
      
.cmd_help_triggered:
      MACRO_PRINT16 cmd_help_msg
      jmp mainloop

.cmd_suicide_triggered:
      mov al, 0xFE
      out 0x64, al
      jc .cmd_apm_error_triggered
      
.cmd_die_triggered:
      mov ah, 0x53
      mov al, 0x07
      mov bx, 0x01
      mov cx, 0x03
      int 15h
      jc .cmd_apm_error_triggered
      
.cmd_apm_error_triggered:
      MACRO_PRINT16 cmd_apm_error
      jmp mainloop

.cmd_ram_triggered:
      int 12h      
      call bin2ascii
      MACRO_PRINT16 outbin2ascii
      MACRO_PRINT16 cmd_ram_msg
      jmp mainloop
      
      
      welcome 			db 'Welcome to Marvin OS bootstage 2', 13, 10, 0
      prompt 			db '>', 0
      buffer 			times 64 db 0
      cmd_version 		db 'version', 0
      cmd_version_msg 		db 'Marvin OS v0.01',13,10,'License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.',13,10, 'This is free software: you are free to change and redistribute it.',13,10, 'There is NO WARRANTY, to the extent permitted by law.',13,10, 'Written by Nilton Vasques<niltonvasques@gmail.com>',13,10,0      
      cmd_help			db 'help', 0
      cmd_help_msg		db 'MSBB - Marvin Sad Bootloader Bash, version 0.01',13,10,'The bash more sadder of world!',13,10,'These commands are defined internally.',13,10,13,10,'Commands list:',13,10,'die',13,10,'suicide',13,10,'ram',13,10,'init',13,10,'version',13,10,'pmode',13,10,'help',13,10,0
      cmd_pmode 		db 'pmode', 0
      cmd_pmode_msg 		db 'Switching to protected mode', 13,10,0
      cmd_bad_input_msg		db ': command not found',13,10,0      
      cmd_suicide 		db 'suicide', 0
      cmd_die 			db 'die', 0
      cmd_init			db 'init',0
      cmd_ram			db 'ram',0
      cmd_ram_msg		db ' KB of lower memory ram!',13,10,0
      cmd_apm_error	 	db 'Error: BIOS not supported APM (Advanced Power Management)',13,10,0
      
      
      times 2048-($-$$) db 0