; /*This file is part of Marvin OS project.
; * 
; *Marvin OS is free software: you can redistribute it and/or modify
; *it under the terms of the GNU General Public License as published by
; *the Free Software Foundation, either version 3 of the License, or
; *(at your option) any later version.
; *
; *Marvin OS is distributed in the hope that it will be useful,
; *but WITHOUT ANY WARRANTY; without even the implied warranty of
; *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *GNU General Public License for more details.
; *
; *You should have received a copy of the GNU General Public License
; *along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.
; *
; *	Description: Kernel entry ṕoint
; *	Author: Nilton Vasques
; *	Date: 25 - 03 - 2013
; */
[bits 32]
[extern kmain]
[global kernel_entry] 			; making entry point visible to linker

kernel_entry:
      call kmain
      jmp $
      
; global loader                           ; making entry point visible to linker
; global magic                            ; we will use this in kmain
; global mbd                              ; we will use this in kmain
;  
; extern main                            ; kmain is defined in kmain.cpp
;  
; ; setting up the Multiboot header - see GRUB docs for details
; MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
; MEMINFO     equ  1<<1                   ; provide memory map
; FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
; MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
; CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required
;  
; section .text
;  
; align 4
;     dd MAGIC
;     dd FLAGS
;     dd CHECKSUM
;  
; ; reserve initial kernel stack space
; STACKSIZE equ 0x4000                    ; that's 16k.
;  
; loader:
;     mov  esp, stack + STACKSIZE         ; set up the stack
;     mov  [magic], eax                   ; Multiboot magic number
;     mov  [mbd], ebx                     ; Multiboot info structure
;  
;     call main                          ; call kernel proper
;  
;     cli
; .hang:
;     hlt                                 ; halt machine should kernel return
;     jmp  .hang
;  
; section .bss
;  
; align 4
; stack: resb STACKSIZE                   ; reserve 16k stack on a doubleword boundary
; magic: resd 1
; mbd:   resd 1