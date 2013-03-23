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
      
;--------------------------------------------------------------------------------
;	3- MAIN LOOP - PROMPT
;--------------------------------------------------------------------------------
      
mainloop:
      mov bx, PROMPT
      call print_string_16
      
      mov di, BUFFER
      call get_string16
      
      mov si, BUFFER
      cmp byte [si], 0  ; blank line?
      je mainloop       ; yes, ignore it
      
      mov si, BUFFER
      mov di, CMD_VERSION
      call strcmp
      jc .cmd_version_triggered
      
      mov si, BUFFER
      mov di, CMD_PMODE
      call strcmp
      jc .cmd_pmode_triggered      
      
      mov si, BUFFER
      mov di, CMD_HELP
      call strcmp
      jc .cmd_help_triggered
      
      mov si, BUFFER
      mov di, CMD_SUICIDE
      call strcmp
      jc .cmd_suicide_triggered
      
      mov si, BUFFER
      mov di, CMD_DIE
      call strcmp
      jc .cmd_die_triggered      
      
      mov si, BUFFER
      mov di, CMD_RAM
      call strcmp
      jc .cmd_ram_triggered
      
      mov si, BUFFER
      mov di, CMD_A20
      call strcmp
      jc .cmd_a20_switch_triggered
      
      call .cmd_bad_input_triggered
      
      jmp mainloop     

;--------------------------------------------------------------------------------
;	HANDLERS FOR COMMANDS TRIGGERED
;--------------------------------------------------------------------------------
.cmd_version_triggered:
      mov bx, CMD_VERSION_msg
      call print_string_16 
      jmp mainloop
      
.cmd_pmode_triggered:
      call switch_to_pm		; This functions only returns if erros occurrs
      
      mov bx, CMD_PMODE_ERROR
      call print_string_16
      
      jmp $
      
.cmd_bad_input_triggered:
      mov bx, BUFFER      
      call print_string_16 
      mov bx, CMD_BAD_INPUT_MSG
      call print_string_16 
      jmp mainloop
      
.cmd_help_triggered:
      mov bx, CMD_HELP_MSG
      call print_string_16 
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
      mov bx, CMD_APM_ERROR
      call print_string_16 
      jmp mainloop

.cmd_ram_triggered:
      int 12h      
      call bin2ascii
      mov bx, outbin2ascii
      call print_string_16 
      mov bx, CMD_RAM_MSG
      call print_string_16 
      jmp mainloop
      
.cmd_a20_switch_triggered:
      call a20_status
      jc .error_a20_gate
      cmp al, 1
      jne .enable
      .disable:
	    call a20_disable
	    jc .error_a20_gate
	    mov bx, CMD_A20_DISABLED 
	    jmp .cmd_a20_done
      .enable:
	    call a20_enable
	    jc .error_a20_gate
	    mov bx, CMD_A20_ENABLED
	    jmp .cmd_a20_done
      .error_a20_gate:
	    mov bx, CMD_A20_ERROR
      .cmd_a20_done:	    
	    call print_string_16
	    jmp mainloop

;--------------------------------------------------------------------------------
;	INCLUDES
;--------------------------------------------------------------------------------
%include "libio16.inc"
%include "libstr.inc"
%include "liba20.inc"
%include "libmode.inc"
%include "libgdt.inc"
%include "libio32.inc"

;--------------------------------------------------------------------------------
;	INIT 32-BIT CODE IN PROTECTED MODE
;--------------------------------------------------------------------------------
[bits 32]
      
BEGIN_PM:
      call clear_screen_32
      mov ebx, MSG_PROT_MODE
      call print_string_32   
      
      jmp $
      
;--------------------------------------------------------------------------------
;	GLOBAL VARIABLES
;--------------------------------------------------------------------------------

      MSG_PROT_MODE		db "Sucessfully landed in 32-bit Protected Mode", 0
      BOOT_DRIVE 		db 0
      WELCOME_MSBB_STAGE_2	db 'Welcome to Marvin OS bootstage 2', 13, 10, 0
      PROMPT 			db '>', 0
      BUFFER 			times 64 db 0
      CMD_VERSION 		db 'version', 0
      CMD_VERSION_msg 		db 'Marvin OS v0.01',13,10,'License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.',13,10, 'This is free software: you are free to change and redistribute it.',13,10, 'There is NO WARRANTY, to the extent permitted by law.',13,10, 'Written by Nilton Vasques<niltonvasques@gmail.com>',13,10,0      
      CMD_HELP			db 'help', 0
      CMD_HELP_MSG		db 'MSBB - Marvin Sad Bootloader Bash, version 0.01',13,10,'The bash more sadder of world!',13,10,'These commands are defined internally.',13,10,13,10,'Commands list:',13,10,'die',13,10,'suicide',13,10,'ram',13,10,'a20',13,10,'init',13,10,'version',13,10,'pmode',13,10,'help',13,10,0
      CMD_PMODE 		db 'pmode', 0
      CMD_PMODE_MSG 		db 'Switching to protected mode', 13,10,0
      CMD_PMODE_ERROR	 	db 'Error: A20 Gate switch for BIOS not supported',13,10,0
      CMD_BAD_INPUT_MSG		db ': command not found',13,10,0      
      CMD_SUICIDE 		db 'suicide', 0
      CMD_DIE 			db 'die', 0
      CMD_INIT			db 'init',0
      CMD_RAM			db 'ram',0
      CMD_RAM_MSG		db ' KB of lower memory ram!',13,10,0
      CMD_APM_ERROR	 	db 'Error: BIOS not supported APM (Advanced Power Management)',13,10,0
      CMD_A20 			db 'a20', 0
      CMD_A20_ENABLED		db 'A20 Gate enabled', 13,10,0
      CMD_A20_DISABLED		db 'A20 Gate disabled', 13,10,0
      CMD_A20_ERROR	 	db 'Error: A20 Gate switch for BIOS not supported',13,10,0

;--------------------------------------------------------------------------------
;	FILL FILE IN 2 KB 
;	Because each sector of floppy disk contains 512 bytes
;	Thus confident that all bytes will be writed on image
;--------------------------------------------------------------------------------
      
      times 2048-($-$$) db 0