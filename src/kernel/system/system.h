/*This file is part of Marvin OS project.
* 
*Marvin OS is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*Marvin OS is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.
*
*	Description: System functions
*	Author: Nilton Vasques
*	Date: 26 - 03 - 2013
*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <types.h>

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};


#define PORT_FLOPPY_DISK 0x3F2

uchar 	inb(ushort port);
ushort 	inw(ushort port);
void 	outb(ushort port, uchar data );
void 	outw(ushort port, ushort data);


/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install();

/* init_pics()
 * init the PICs and remap them
 */
void init_pics(int pic1, int pic2);


/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);

/* Installs the IDT */
void idt_install();


void fault_handler(struct regs *r);

void isrs_install();

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r));

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq);

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void);

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install();

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r);

void timer_phase(int hz);

void timer_install();

void timer_wait(int ticks);


#define PS2_DATA_REGISTER 0x60
#define PS2_CTRL_REGISTER 0x64
void ps2_keyboard_install();
void ps2_load_keyboard_driver( void (*driver)(unsigned char scancode) );

void keyboard_register_listener( void (*key_listener)(unsigned char scancode) );
void keyboard_unregister_listener( );

#endif