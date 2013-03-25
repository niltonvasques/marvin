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
*	Description: I/O Library
*	Author: Nilton Vasques
*	Date: 25 - 03 - 2013
*/
#include <libio.h>
#include <screen.h>

void cls(){
      int i = 0; 
      int j = 0;
      for(i = 0; i<MAX_ROWS; i++){
	    for(j = 0; j < MAX_COLS; j++){
		  print_char(' ', j, i, 0 );
	    }
      }
      
      set_cursor( get_screen_offset(0,0) );     
}

void print_at( char* buffer, int col, int row ){
      if( col >= 0 && row >= 0 ){
	    set_cursor( get_screen_offset( col, row ) );
      }
      
      while(*buffer){
	    print_char(*buffer,col,row,0);
	    buffer++;
	    if( col >= 0 && row >= 0 ){
		  col++;
		  if( col >= MAX_COLS ){
			row++;
			col = 0;		 
		  }		  
	    }
      }
}

void print( char* buffer ){
      print_at( buffer, -1, -1 );
}

