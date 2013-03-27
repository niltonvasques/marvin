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
#ifndef STDIO_H
#define STDIO_H
#include <system.h>

void print_at( char* buffer, int x, int y );
void print( char* buffer );
void putch( char c );
void cls();
void set_color_scheme( char attr_byte );
void gets( char* buffer, uint lenght );

#endif