#include <system.h>

void (*internal_keyboard_driver)(unsigned char scancode);

/* Handles the keyboard interrupt */
void keyboard_irq_handler(struct regs *r __attribute__((__unused__)) )
{
      unsigned char scancode;

      /* Read from the keyboard's data buffer */
      scancode = inb(PS2_DATA_REGISTER); 
      if( internal_keyboard_driver ){
	    internal_keyboard_driver( scancode );
      }
}

void ps2_load_keyboard_driver( void (*driver)(unsigned char scancode) ){
      internal_keyboard_driver = driver;        
}

void ps2_unload_keyboard_driver( ){
      internal_keyboard_driver = 0;
}

void ps2_keyboard_install(){      
      irq_install_handler(1, keyboard_irq_handler);      
}
