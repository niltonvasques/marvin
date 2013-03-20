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

;	Description: Hardware interrups handlers
;	Author: Nilton Vasques
;	Date: 12 - 03 - 2013


;-----------------------------------------------------
;	This Handler manage interrupt of keyboard
;-----------------------------------------------------
  
handler_keyboard:
      in al, 0x60	;get key data
      mov bl, al	;save it
      mov byte [port60], al
      
      in al, 0x61	;keyboard control
      mov ah, al
      or al, 0x80	;disable bit7 	; Why he disable bit 7? I don't know :
      out 0x61, al	;send it back
      xchg ah, al	;get original
      out 0x61, al	;send that back
      
      mov al, 0x20	;end of interrupt
      out 0x20, al	;
      
      and bl, 0x80	;key released
      jnz done
      
      mov ax, [port60]
      mov word[reg16], ax
      cmp ax, 0x000E	;check if user pressed backspace
      je backspace
printkey:
      call printreg16
      jmp done
backspace:
      MACRO_DRAW_SCREEN
done:
      iret