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
*	Description: Shell
*	Author: Nilton Vasques
*	Date: 26 - 03 - 2013
*/
#include <shell.h>
#include <libio.h>
#include <libstring.h>
#include <vga.h>

#define SHELL_CMD_MAX_LENGHT		60
#define SHELL_CMD_VERSION		"version"
#define SHELL_CMD_HELP			"help"
#define SHELL_CMD_COLOR			"color"
#define SHELL_CMD_CLS			"cls"
#define SHELL_CMD_FAULT			"fault"

#define SHELL_MSG_BAD_COMMAND		": command not found\n"

typedef enum{
      RUNNING,CLOSED
}SHELL_STATUS;

SHELL_STATUS status = CLOSED;

void shell();
void shell_prompt();
void shell_read_command();

char command_buffer[SHELL_CMD_MAX_LENGHT];


void shell_init(){
      status = RUNNING;
      shell();
}

void shell_close(){
      status = CLOSED;
}

void shell_prompt(){
      print("> ");
}

void shell_read_command(){      
      gets( command_buffer, SHELL_CMD_MAX_LENGHT );
}

void shell_cmd_version( int argc ){
      char arg[SHELL_CMD_MAX_LENGHT];
      if( argc == 1 ){
	    print( "Marvin Kernel Shell v0.01\n" );
	    return;
      }
      strarg( command_buffer, arg, 1 );
      if( strcmp( arg, "-b" ) ){
	    print( "MSBB Bootloader v0.02\n" );
	    return;
      }
      
}

void shell_cmd_help(){
      print(SHELL_CMD_HELP);
      print("\n");
      print(SHELL_CMD_VERSION);
      print("\n");
      print(SHELL_CMD_COLOR);
      print("\n");
      print(SHELL_CMD_CLS);
      print("\n");
      print(SHELL_CMD_FAULT);
      print("\n");
}

char *color_list[16] = {
   "black", "blue", "green", "cyan", "red", "magenta", "brown", "light-grey",
   "dark-grey", "light-blue", "light-green", "light-cyan", "light-red", "light-magenta",
   "light-brown", "white" 
};

int colors[16] = {
      BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, LIGHT_BLUE, 
      LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, LIGHT_BROWN, WHITE
};

int cmd_color_parser( char* color_str ){
      int color = 0;
      int i = 0;
      for( i = 0; i < 16; i++){
	    if( strcmp( color_str, color_list[i] ) ){
		  color = colors[i];
		  break;
	    }
      }
      
      return color;
}

void shell_cmd_color( int argc ){
      char arg[SHELL_CMD_MAX_LENGHT];
      if( argc == 3 ){
	    int back = BLACK;
	    int fore = RED;
	    strarg( command_buffer, arg, 1 );
	    back = cmd_color_parser( arg );
	    strarg( command_buffer, arg, 2 );
	    fore = cmd_color_parser( arg );
	    if( strcmp( arg, "white" ) ){
		  fore = WHITE;
	    }
	    set_color_scheme( ATTRIBUTE_BYTE( back, fore ) );	    
      }else if( argc == 2){
	    strarg( command_buffer, arg, 1 );
	    if( strcmp( arg, "-c" ) || strcmp( arg, "--color-list" ) ){
		  int i = 0;
		  for(i = 0; i < 16; i++){
			print( color_list[i] );
			print("\n");
		  }
	    }
      }else{
	    print("Invalid params\nusage: color [ -c | --color-list ] | [<background-color> <foreground-color>]\n");
      }
}

void shell_cmd_cls(){
      cls();      
}

void shell_cmd_fault(){
	u32int *ptr = (u32int*)0xA0000000;
	u32int do_page_fault __attribute__((__unused__)) = *ptr;
}

void shell_commands_parser(){
      char arg[SHELL_CMD_MAX_LENGHT];
      int argc = strargs( command_buffer );
      if( argc == 0  ) return;
      
      strarg( command_buffer, arg, 0 );
      
      if( strcmp( arg, SHELL_CMD_VERSION ) ){
	    shell_cmd_version(argc);
	    return;
      }
      
      if( strcmp( arg, SHELL_CMD_HELP ) ){
	    shell_cmd_help();
	    return;
      }
      
      if( strcmp( arg, SHELL_CMD_COLOR ) ){
	    shell_cmd_color(argc);
	    return;
      }
      
      if( strcmp( arg, SHELL_CMD_CLS ) ){
	    shell_cmd_cls();
	    return;
      }
      
      if( strcmp( arg, SHELL_CMD_FAULT) ){
    	  shell_cmd_fault();
    	  return;
      }

      print( arg );
      print( SHELL_MSG_BAD_COMMAND );
}

void shell(){
      
      while( status == RUNNING ){
	    shell_prompt();	
	    shell_read_command();
	    shell_commands_parser();
      }      
}
