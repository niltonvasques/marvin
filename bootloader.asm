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

BITS 16

mov ax, 07C0h
mov ss, ax
mov ds, ax

mov si, Msg
mov ah, 0Eh
jmp repetir

Msg db 'Marvin OS v0.1!', 0

repetir:
lodsb
cmp al, 0
je fim
int 10h
jmp repetir

fim:
jmp $
times 510-($-$$) db 0
dw 0xAA55
