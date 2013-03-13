;	Bootloader of operating system InsanityOS
;	Writed by Nilton Vasques
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
