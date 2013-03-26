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
*	Description: Screen driver
*	Author: Nilton Vasques
*	Date: 25 - 03 - 2013
*/
#include <vga.h>
#include <libport_asm.h>
#include <libstring.h>

int get_cursor(){
//       The device uses its control register as an index
//       to select its internal registers , of which we are
//       interested in :
//       
//       reg 14: which is the high byte of the cursor ’s offset
//       reg 15: which is the low byte of the cursor ’s offset
//       Once the internal register has been selected , we may read or
//       write a byte on the data register .		
      outb(REG_SCREEN_CTRL, 14);
      int offset = inb(REG_SCREEN_DATA) << 8;
      outb(REG_SCREEN_CTRL, 15);
      offset += inb(REG_SCREEN_DATA);
//       Since the cursor offset reported by the VGA hardware is the
//       number of characters , we multiply by two to convert it to
//       a character cell offset .
      return offset*2;      
}

void set_cursor( int offset ){      
      offset = offset >> 1;
      outb(REG_SCREEN_CTRL, 14);
      outb(REG_SCREEN_DATA, offset >> 8);
      outb(REG_SCREEN_CTRL, 15);
      outb(REG_SCREEN_DATA, offset & 0x00FF);      
}

void print_char( char character, int col, int row, char attribute_type ){
      
      unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY_ADDRESS;
      
      if( !attribute_type ){
	    attribute_type = WHITE_ON_BLACK;
      }
      
      int offset;
      
      if( col >= 0 && row >= 0 ){
	    offset = get_screen_offset( col, row );
      } else {
	    offset = get_cursor();
      }
      
      if( character == '\n' ){
	    int rows 	= offset / ( MAX_COLS << 1 );
	    offset	= get_screen_offset( 79, rows );
      } else {
	    vidmem[offset] 	= character;
	    vidmem[offset+1] 	= attribute_type;
      }
      
      offset += 2;
      offset = handle_scrolling( offset );
      set_cursor( offset );            
}

int handle_scrolling( int cursor_offset ){
      
      if( cursor_offset < MAX_COLS*MAX_ROWS*2 ){
	    return cursor_offset;
      }
      
      int i;
      for(i = 1; i < MAX_ROWS; i++){
	    memcpy((uchar*) VIDEO_MEMORY_ADDRESS + get_screen_offset( 0, i ),
		   (uchar*) VIDEO_MEMORY_ADDRESS + get_screen_offset( 0, i-1 ), 
		   MAX_COLS*2 
	    );    
      }
      cursor_offset = get_screen_offset( 0, MAX_ROWS-1 );
      char* last_line = (char*) VIDEO_MEMORY_ADDRESS + cursor_offset;
      for(i = 0; i < MAX_COLS*2; i++){
	    *(last_line + i) = 0;
      }      
      return cursor_offset;
}