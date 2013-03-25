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
#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_MEMORY_ADDRESS 	0xB8000

#define MAX_ROWS 		25
#define MAX_COLS 		80

#define WHITE_ON_BLACK		0x0F

#define REG_SCREEN_CTRL		0x3D4
#define REG_SCREEN_DATA		0x3D5

#define get_screen_offset(col,row) ( ((row)*MAX_COLS+(col))*2 )

int 	get_cursor();
void 	set_cursor( int offset );
void	print_char( char character, int col, int row, char attribute_type );
int 	handle_scrolling( int cursor_offset );

#endif