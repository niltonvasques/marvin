#include <libio.h>

void cls(){
      char* video_memory = (char*) VIDEO_MEMORY_ADDRESS;
      int i = 0; 
      //Clear Screen
      for(; i< 2000; video_memory+=2, i++){
	    *video_memory = ' ';
      }
}

void print( char* buffer, int x, int y ){
      char *video_memory = (char*) VIDEO_MEMORY_ADDRESS;
      video_memory+= y*80+x;
      while(*buffer){
	    *video_memory = *buffer;
	    video_memory+=2;
	    buffer++;
      }
}