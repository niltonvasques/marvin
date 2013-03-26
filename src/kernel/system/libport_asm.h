#ifndef LIBPORT_ASM_H
#define LIBPORT_ASM_H

#include <types.h>

#define PORT_FLOPPY_DISK 0x3F2

uchar 	inb(ushort port);
ushort 	inw(ushort port);
void 	outb(ushort port, uchar data );
void 	outw(ushort port, ushort data);

#endif