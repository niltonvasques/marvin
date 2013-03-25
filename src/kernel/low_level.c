#include <low_level.h>

unsigned char port_byte_in(unsigned short port){
      // A handy C wrapper function that reads a byte from the specified port
      // "= a " ( result ) means : put AL register in variable RESULT when finished
      // " d " ( port ) means : load EDX with port
      unsigned char result;
      __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
      return result;
}