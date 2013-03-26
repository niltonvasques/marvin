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
#ifndef VGA_H
#define VGA_H

#define VIDEO_MEMORY_ADDRESS 	0xB8000

#define MAX_ROWS 		25
#define MAX_COLS 		80

#define WHITE_ON_BLACK		0x0F

#define BLACK			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED			0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0A
#define LIGHT_CYAN		0x0B
#define LIGHT_RED		0x0C
#define LIGHT_MAGENTA		0X0D
#define LIGHT_BROWN		0x0E
#define WHITE			0x0F

#define ATTRIBUTE_BYTE( back, fore ) ( (back<<4)+(fore) )

#define REG_SCREEN_CTRL		0x3D4
#define REG_SCREEN_DATA		0x3D5



#define get_screen_offset(col,row) ( ((row)*MAX_COLS+(col))*2 )

int 	get_cursor();
void 	set_cursor( int offset );
void	print_char( char character, int col, int row, char attribute_type );
int 	handle_scrolling( int cursor_offset );

#endif