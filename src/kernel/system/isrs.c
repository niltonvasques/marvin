#include <system.h>
#include <libio.h>

/* These are function prototypes for all of the exception
*  handlers: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */
__native__ void isr0();
__native__ void isr1();
__native__ void isr2();
__native__ void isr3();
__native__ void isr4();
__native__ void isr5();
__native__ void isr6();
__native__ void isr7();
__native__ void isr8();
__native__ void isr9();
__native__ void isr10();
__native__ void isr11();
__native__ void isr12();
__native__ void isr13();
__native__ void isr14();
__native__ void isr15();
__native__ void isr16();
__native__ void isr17();
__native__ void isr18();
__native__ void isr19();
__native__ void isr20();
__native__ void isr21();
__native__ void isr22();
__native__ void isr23();
__native__ void isr24();
__native__ void isr25();
__native__ void isr26();
__native__ void isr27();
__native__ void isr28();
__native__ void isr29();
__native__ void isr30();
__native__ void isr31();

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void isrs_install()
{
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
{
      (uchar*) "Division By Zero",
      (uchar*) "Debug",
      (uchar*) "Non Maskable Interrupt",
      (uchar*) "Breakpoint Exception",
      (uchar*) "Into Detected Overflow Exception",
      (uchar*) "Out of Bounds Exception",
      (uchar*) "Invalid Opcode Exception",
      (uchar*) "No Coprocessor Exception",
      (uchar*) "Double Fault Exception",
      (uchar*) "Coprocessor Segment Overrun Exception",
      (uchar*) "Bad TSS Exception",
      (uchar*) "Segment Not Present Exception",
      (uchar*) "Stack Fault Exception",
      (uchar*) "General Protection Fault Exception",
      (uchar*) "Page Fault Exception",
      (uchar*) "Unknown Interrupt Exception",
      (uchar*) "Coprocessor Fault Exception",
      (uchar*) "Alignment Check Exception (486+)",
      (uchar*) "Machine Check Exception (Pentium/586+)",    
      (uchar*) "Reserved",
      (uchar*) "Reserved" ,
      (uchar*) "Reserved" ,
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved",
      (uchar*) "Reserved"
};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void fault_handler(registers_t *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
        print((char*) exception_messages[r->int_no]);
        print(" Exception. System Halted!\n");
        // A page fault has occurred.
		// The faulting address is stored in the CR2 register.
		u32int faulting_address;
		asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

		// The error code gives us details of what happened.

		int present   = !(r->err_code & 0x1); // Page not present
		int rw = r->err_code & 0x2;           // Write operation?
		int us = r->err_code & 0x4;           // Processor was in user-mode?
		int reserved = r->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
//		int id = r->err_code & 0x10;          // Caused by an instruction fetch?

		// Output an error message.
		print("Page fault! ( ");
		if (present) {print("present ");}
		if (rw) {print("read-only ");}
		if (us) {print("user-mode ");}
		if (reserved) {print("reserved ");}
		print(") at 0x");
		print_hex(faulting_address);
		print("\n");
		PANIC("Page fault");
        for (;;);
    }
}
