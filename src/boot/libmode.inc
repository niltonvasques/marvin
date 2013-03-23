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

;	Description: Library for switch Real Mode to Protected Mode
;	Author: Nilton Vasques
;	Date: 22 - 03 - 2013


[bits 16]
switch_to_pm:
      cli 					; We must switch of interrupts until we have
						; set - up the protected mode interrupt vector
						; otherwise interrupts will run riot.
      
      lgdt[gdt_descriptor]			; Load GDT (Global Descriptor Table)
						; whiche defines the protected mode segments ( e.g. for code and data )
      mov eax , cr0				; Switching to protected mode
      or eax , 0x1	      			; To make the switch to protected mode , we set
      mov cr0 , eax    				; the first bit of CR0 , a control register
						; Update the control register
      
      jmp CODE_SEG:start_protected_mode 	; Because the processors implementing pipeline
						; When we are switch to protected mode, some instructions in pipeline can
						; performed wrong. 

						; So solution is execute a far jump, for flush pipeline      
[bits 32]
      
start_protected_mode:
      mov ax, DATA_SEG	; Now in PM , our old segments are meaningless ,
      mov ds, ax		; so we point our segment registers to the
      mov ss, ax		; data selector we defined in our GDT
      mov es, ax
      mov fs, ax
      mov fs, ax
      
      mov ebp, 0x90000	; Update our stack position so it is right
      mov esp, ebp	; at the top of the free space.      

      call BEGIN_PM
