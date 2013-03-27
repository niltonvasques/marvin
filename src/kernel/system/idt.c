#include <system.h>
#include <libstring.h>
#include <libio.h>
/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo; 	// offset bits 0..15
    unsigned short selector;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi; 	// offset bits 16..31
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
__native__ void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags)
{
    idt[num].base_lo 	= (unsigned short) base & 0xFFFF;
    idt[num].selector	= selector;
    idt[num].always0	= 0;
    idt[num].flags	= flags;
    idt[num].base_hi 	= (unsigned short) (base >> 16) & 0xFFFF;
}

/* Installs the IDT */
void idt_install()
{
      /* Sets the special IDT pointer up, just like in 'gdt.c' */
      idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
      idtp.base = (uint)&idt;

      /* Clear out the entire IDT, initializing it to zeros */
      memset((uchar*)&idt, 0, sizeof(struct idt_entry) * 256);

      /* Add any new ISRs to the IDT here using idt_set_gate */      
//       char *ret = "0000000000";
//       uint2str((uint)&idtp,ret);
//       print(ret);
//       BOCHS_BREAKPOINT();
      /* Points the processor's internal register to the new IDT */	
      idt_load();
}