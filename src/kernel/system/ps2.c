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
*	Description: PS2 Controller
*	Author: Nilton Vasques
*	Date: 26 - 03 - 2013
*/
#include <system.h>

void (*internal_keyboard_driver)(unsigned char scancode);

/* Handles the keyboard interrupt */
void keyboard_irq_handler(registers_t *r __attribute__((__unused__)) )
{
      unsigned char scancode;

      /* Read from the keyboard's data buffer */
      scancode = inb(PS2_DATA_REGISTER); 
      if( internal_keyboard_driver ){
	    internal_keyboard_driver( scancode );
      }
}

void ps2_load_keyboard_driver( void (*driver)(unsigned char scancode) ){
      internal_keyboard_driver = driver;        
}

void ps2_unload_keyboard_driver( ){
      internal_keyboard_driver = 0;
}

void ps2_keyboard_install(){      
      irq_install_handler(1, keyboard_irq_handler);      
}
