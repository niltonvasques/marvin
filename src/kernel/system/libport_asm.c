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
*	Description: Ports low level device communication library
*	Author: Nilton Vasques
*	Date: 25 - 03 - 2013
*/
#include <libport_asm.h>

uchar inb(ushort port){
      // A handy C wrapper function that reads a byte from the specified port
      // "= a " ( result ) means : put AL register in variable RESULT when finished
      // " d " ( port ) means : load EDX with port
      uchar result;
      __asm__ __volatile__ ("in %%dx, %%al" : "=a"(result) : "d"(port));
      return result;
}

ushort inw(ushort port){
      ushort result;
      __asm__ __volatile__ ("in %%dx, %%ax" : "=a"(result) : "d"(port));
      return result;
}

void outb(ushort port, uchar data ){
      __asm__ __volatile__ ("out %%al, %%dx" : :"a" (data), "d"(port) );
}

void outw(ushort port, ushort data){
      __asm__ __volatile__ ("out %%ax, %%dx" : :"a"(data), "d"(port) );      
}
