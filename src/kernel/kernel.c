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

#include <low_level.h>
#include <libio.h>

void char2string( unsigned char c, char* s);


int main(){
      // Create a pointer to a char , and point it to the first text cell of
      // video memory ( i . e . the top - left of the screen )
      char *text 	= "Marvin Kernel 0.01";
      unsigned char result;
      char *buffer 	= "000";
      
      cls();
      // At the address pointed to by video_memory , store the character ’X ’
      // ( i . e . display ’X ’ in the top - left of the screen ).
      print( text, 0, 0 );
      
      result = port_byte_in(0x300);
      char2string( result, buffer );
      
//       print( buffer, 0, 1 );
      

      
      return 0;
}

void char2string( unsigned char c, char* s){
      int pos = 2;      
//       for(;pos >= 0;pos--){	    
	    unsigned char remainder = (c % 10) + '0';
	    c/=10;
	    s[pos] = remainder;
//       }
}


