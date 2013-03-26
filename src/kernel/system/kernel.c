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
*	Description: Kernel Main
*	Author: Nilton Vasques
*	Date: 21 - 03 - 2013
*/

#include <system.h>
#include <libport_asm.h>
#include <libstring.h>
#include <libio.h>
#include <libbochs.h>

/*
 *  Drivers
 */
#include <pic.h>
#include <vga.h>

void k_init();

char *title 	= "Marvin Kernel v0.01";

int kmain(){      
      int var = 10;
      k_init();    
      
      for(;;){
      }
      return 0;
}

void k_init(){
      gdt_install();      
//       So, this call will remap the PICs so that IRQ0 starts at 0x20 and IRQ8 starts at 0x28:      
      init_pics( 0x20, 0x28 );
      
      idt_install();
      
      set_color_scheme( ATTRIBUTE_BYTE( BLACK, GREEN ) );
      
      cls();
      
      print_at( title, 0, 0 );
      
      set_color_scheme( ATTRIBUTE_BYTE( BLACK, RED ) );
      
      print_at( title, 0, 1 );
}
