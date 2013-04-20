/*
 * panic.c
 *
 *  Created on: Apr 20, 2013
 *      Author: niltonvasques
 */

#include <system.h>
#include <libio.h>

extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    print("PANIC(");
    print((char*)message);
    print(") at ");
    print((char*)file);
    print(":");
    print_dec(line);
    print("\n");
    // Halt by going into an infinite loop.
    for(;;);
}


