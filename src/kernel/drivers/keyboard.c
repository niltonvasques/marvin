#include <system.h>
#include <keyboard.h>
#include <libio.h>

void keyboard_turn_on_lights();

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   
 KEY_LSHIFT,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   
  KEY_RSHIFT,				/* Right shift */
  '*',
    KEY_ALT,	/* Alt */
  ' ',	/* Space bar */
    KEY_CAPS,	/* Caps lock */
    KEY_F1,	/* 59 - F1 key ... > */
    KEY_F2,   KEY_F3,   KEY_F4,   KEY_F5,   KEY_F6,   KEY_F7,   KEY_F8,   KEY_F9,
    KEY_F10,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    KEY_F11,	/* F11 Key */
    KEY_F12,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_driver( unsigned char scancode ){
      /* If the top bit of the byte we read from the keyboard is
      *  set, that means that a key has just been released */
      if (scancode & BYTE(1000,0000))
      {
	    /* You can use this one to see if the user released the
	    *  shift, alt, or control keys... */	
      // 	if(kbdus[scancode] == 'CAPSLOCK ?'){
      // 	      keyboard_turn_on_lights();
      // 	}
      }
      else
      {
	    /* Here, a key was just pressed. Please note that if you
	    *  hold a key down, you will get repeated key press
	    *  interrupts. */

	    /* Just to show you how this works, we simply translate
	    *  the keyboard scancode into an ASCII value, and then
	    *  display it to the screen. You can get creative and
	    *  use some flags to see if a shift is pressed and use a
	    *  different layout, or you can add another 128 entries
	    *  to the above layout to correspond to 'shift' being
	    *  held. If shift is held using the larger lookup table,
	    *  you would add 128 to the scancode when you look for it */
	    putch(kbdus[scancode]);
      }
}

void keyboard_turn_on_lights(){
      for(;;){
	    if ((inb(PS2_CTRL_REGISTER) & 2) == 0) break;
      }
      outb(PS2_DATA_REGISTER, 0xED);
      outb(PS2_DATA_REGISTER, 2);      
}