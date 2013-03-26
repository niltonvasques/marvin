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
[extern idtp]
[extern gdtp]
[extern fault_handler]
[global kernel_entry] 			; making entry point visible to linker
[global idt_load]
[global gdt_flush]

kernel_entry:
      call kmain
      jmp $

; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
idt_load:
      lidt [idtp]
      ret

; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
gdt_flush:
      lgdt [gdtp]
      mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
      mov ds, ax
      mov es, ax
      mov fs, ax
      mov gs, ax
      mov ss, ax
      jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
      ret               ; Returns back to the C code!
      
[global isr0]
[global isr1]
[global isr2]
[global isr3]
[global isr4]
[global isr5]
[global isr6]
[global isr7]
[global isr8]
[global isr9]
[global isr10]
[global isr11]
[global isr12]
[global isr13]
[global isr14]
[global isr15]
[global isr16]
[global isr17]
[global isr18]
[global isr19]
[global isr20]
[global isr21]
[global isr22]
[global isr23]
[global isr24]
[global isr25]
[global isr26]
[global isr27]
[global isr28]
[global isr29]
[global isr30]
[global isr31]
; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!

;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0    ; A normal ISR stub that pops a dummy error code to keep a
    push byte 0    ; uniform stack frame    
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub
    
; 2	Non Maskable Interrupt Exception	No
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub   

; 3	Breakpoint Exception	No
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub
    
; 4	Into Detected Overflow Exception	No
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub
    
; 5	Out of Bounds Exception	No
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub
    
; 6	Invalid Opcode Exception	No
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub
    
; 7	No Coprocessor Exception	No
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
                   ; It pushes one already! Use this type of stub for exceptions
                   ; that pop error codes!
    jmp isr_common_stub
    
; 9	Coprocessor Segment Overrun Exception	No
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub
    
; 10	Bad TSS Exception	Yes
isr10:
    cli
    push byte 10
    jmp isr_common_stub
    
; 11	Segment Not Present Exception	Yes
isr11:
    cli
    push byte 11
    jmp isr_common_stub
    
; 12	Stack Fault Exception	Yes
isr12:
    cli
    push byte 12
    jmp isr_common_stub
    
; 13	General Protection Fault Exception	Yes
isr13:
    cli
    push byte 13
    jmp isr_common_stub
    
; 14	Page Fault Exception	Yes
isr14:
    cli
    push byte 14
    jmp isr_common_stub    

; 15	Unknown Interrupt Exception	No
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub
    
; 16	Coprocessor Fault Exception	No
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub
    
; 17	Alignment Check Exception (486+)	No
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub
    
; 18	Machine Check Exception (Pentium/586+)	No
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub    
    
; 19 to 31	Reserved Exceptions	No                   ; use the correct stubs to handle error codes and push dummies!
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub
    
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub
    
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub
    
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub
    
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub
    
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub
    
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub
    
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub
    
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub
    
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub
    
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub
    
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub
    
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!