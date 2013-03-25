#include <libstr.h>

void byte2str( unsigned char c, char* s){
      int pos = 2;      
      for(;pos >= 0;pos--){	    
	    unsigned char remainder = (c % 10) + '0';
	    c/=10;
	    s[pos] = remainder;
      }
}