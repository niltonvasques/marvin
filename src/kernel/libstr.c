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
*	Description: String library
*	Author: Nilton Vasques
*	Date: 25 - 03 - 2013
*/
#include <libstr.h>

void byte2str( unsigned char c, char* s){
      int pos = 2;      
      for(;pos >= 0;pos--){	    
	    unsigned char remainder = (c % 10) + '0';
	    c/=10;
	    s[pos] = remainder;
      }
}