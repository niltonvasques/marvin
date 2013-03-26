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
*	Description: PIC driver
*	Author: Nilton Vasques
*	Date: 26 - 03 - 2013
*/
#include <pic.h>
#include <libport_asm.h>

// send ICW1 to PIC1 (20h) and PIC2 (A0h)
// send ICW2 to 21h for the first PIC and 0A1h for the second PIC
// send ICW3 to 21h for the first PIC and 0A1h for the second PIC
// finally, send ICW4 to 21h for the first PIC and 0A1h for the second PIC

/* init_pics()
 * init the PICs and remap them
 */
void init_pics(int pic1, int pic2){
      
      /* send ICW1 */
	outb(PIC1, ICW1);
	outb(PIC2, ICW1);

	/* send ICW2 */
	outb(PIC1 + 1, pic1);	/* remap */
	outb(PIC2 + 1, pic2);	/*  pics */

	/* send ICW3 */
	outb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
	outb(PIC2 + 1, 2);

	/* send ICW4 */
	outb(PIC1 + 1, ICW4);
	outb(PIC2 + 1, ICW4);

	/* disable all IRQs */
	outb(PIC1 + 1, 0xFF);
}