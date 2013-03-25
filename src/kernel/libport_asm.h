#ifndef LIBPORT_ASM_H
#define LIBPORT_ASM_H

#define PORT_FLOPPY_DISK 0x3F2

unsigned char port_byte_in(unsigned short port);

void port_byte_out(unsigned short port, unsigned char data );

unsigned short port_word_in(unsigned short port);

void port_word_out(unsigned short port, unsigned short data);

#endif