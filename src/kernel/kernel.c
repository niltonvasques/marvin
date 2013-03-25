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

#include <libport_asm.h>
#include <libstr.h>
#include <libio.h>
#include <libbochs.h>

int main(){
      char *title 	= "Marvin Kernel 0.01";      
      char *buffer 	= "000";
      unsigned char result;
      
      cls();
      print_at( title, 0, 0 );
      
      result = port_byte_in(PORT_FLOPPY_DISK);
      byte2str( result, buffer );
      
      print_at( buffer, 0, 1 );
      
      for(;;){
// 	Testing scrolling ;)	
	    print(title);
      }
      return 0;
}
