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

;	Description: Bootloader of operating system InsanityOS
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013


;   mov ax, 0x07C0
;Functions
  %macro BiosPrint 1
    mov si, word %1
  bios_print:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E ;Parameter of Interruption 10h, 0x0E print an character on screen.
    int 0x10
    jmp bios_print  
  done:
  %endmacro
  
    
  [ORG 0x7c00]
  
  xor ax, ax
  mov ds, ax
  
  BiosPrint msg

  ;Loop 
  hang:
    jmp hang
  
  msg	db '>>> Welcome to Marvin <<<', 13, 10, 0
    
    
  ;Say for NASM fill binary until 510 bytes
  times 510-($-$$) db 0
  ;Bytes 510 and 511 are sign of bootsector and need has this values
  db 0x55
  db 0xAA
  
  