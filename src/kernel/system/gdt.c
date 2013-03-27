/*
Pr: Present bit. This must be 1 for all valid selectors.
Privl: Privilege, 2 bits. Contains the ring level, 0 = highest (kernel), 3 = lowest (user applications).
Ex: Executable bit. If 1 code in this segment can be executed, ie. a code selector. If 0 it is a data selector.
DC: Direction bit/Conforming bit.
Direction bit for data selectors: Tells the direction. 0 the segment grows up. 1 the segment grows down, ie. the offset has to be greater than the base.
Conforming bit for code selectors:
If 1 code in this segment can be executed from an equal or lower privilege level. For example, code in ring 3 can far-jump to conforming code in a ring 2 segment. The privl-bits represent the highest privilege level that is allowed to execute the segment. For example, code in ring 0 cannot far-jump to a conforming code segment with privl==0x2, while code in ring 2 and 3 can. Note that the privilege level remains the same, ie. a far-jump form ring 3 to a privl==2-segment remains in ring 3 after the jump.
If 0 code in this segment can only be executed from the ring set in privl.
RW: Readable bit/Writable bit.
Readable bit for code selectors: Whether read access for this segment is allowed. Write access is never allowed for code segments.
Writable bit for data selectors: Whether write access for this segment is allowed. Read access is always allowed for data segments.
Ac: Accessed bit. Just set to 0. The CPU sets this to 1 when the segment is accessed.
Gr: Granularity bit. If 0 the limit is in 1 B blocks (byte granularity), if 1 the limit is in 4 KiB blocks (page granularity).
Sz: Size bit. If 0 the selector defines 16 bit protected mode. If 1 it defines 32 bit protected mode. You can have both 16 bit and 32 bit selectors at once.*/
// http://wiki.osdev.org/GDT

#include <system.h>

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
__native__ void gdt_flush();

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char limit_high_and_flags;
    unsigned char base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low 		= (unsigned short) (base & 0xFFFF);
    gdt[num].base_middle 	= (char) (base >> 16) & 0xFF;
    gdt[num].base_high 		= (char) (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low 			= (unsigned short) (limit & 0xFFFF);
    gdt[num].limit_high_and_flags 	= (char)((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].limit_high_and_flags 	|= (char)(gran & 0xF0);
    gdt[num].access 			= access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install()
{
    /* Setup the GDT pointer and limit */
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = (unsigned int)&gdt;

    /* Our NULL descriptor */
    gdt_set_entry(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_entry(1, 0, 0xFFFFFFFF, BYTE(1001,1010), BYTE(1100,1111) );

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_entry(2, 0, 0xFFFFFFFF, BYTE(1001,0010), BYTE(1100,1111) );

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();
}

