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
#include <libstring.h>

uchar *memcpy( uchar* source, uchar* dest, uint n_bytes ){
      uint count = 0;
      for(; count < n_bytes; count++){
	    *(dest + count) = *(source + count);
      }      
      return dest;
}

uchar *memset( uchar *dest, uchar val, int count ){
      int i;
      while(count--){
	    *(dest + i++) = val;
      }
      return dest;
}

ushort 	*memsetw( ushort *dest, ushort val, int count ){
      int i;
      while(count--){
	    *(dest + i++) = val;
      }
      return dest;
}

void byte2str( uchar c, char* s){
      int pos = 2;      
      for(;pos >= 0;pos--){	    
	    unsigned char remainder = (c % 10) + '0';
	    c/=10;
	    s[pos] = remainder;
      }
}

void uint2str( uint c, char* s){
      int pos = 10;      
      for(;pos >= 0;pos--){	    
	    unsigned char remainder = (c % 10) + '0';
	    c/=10;
	    s[pos] = remainder;
      }
}

/* Return 0 if equals
 * Return any value if not equals
 */
int strcmp( char* str1, char* str2 ){
      while(1){
	    if(*str1 == *str2){
		  if( *str1 == END_STRING )	return 1;
		  str1++;
		  str2++;
	    }else{
		  return 0;
	    }
      }
      return 0;
}

/*
 * Count numbers of params
 */
int strargs( char* args ){
      int count = 0;
      if( *args ) count++;
      while(*args ){
	    if(*args == ' ' && *(args + 1) != END_STRING ) count++;
	    args++;
      }
      return count;
}

/*
 * Count numbers of params
 */
int strarg( char* args, char* dest,  int arg ){
      int count = 0;
      while(*args){	    
	    if(*args == ' ' ){
		  if( *(args + 1) != END_STRING )  count++;
	    } else if ( count == arg ){
		  *dest = *args;		  
		  dest++;
	    }
	    if( count > arg ) break;	    
	    args++;
      }
      *dest = END_STRING;
      return count;
}