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
*	Description: String utils
*	Author: Nilton Vasques
*	Date: 25 - 03 - 2013
*/
#ifndef LIBSTR_H
#define LIBSTR_H

#include <types.h>

extern uchar 	*memcpy( uchar* source, uchar* dest, uint n_bytes );
extern uchar 	*memset( uchar *dest, uchar val, int count );
extern ushort 	*memsetw( ushort *dest, ushort val, int count );
extern void 	byte2str( uchar c, char* s);

#endif
