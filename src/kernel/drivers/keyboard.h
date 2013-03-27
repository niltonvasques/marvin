#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_driver( unsigned char scancode );
void add_key_listener( void (*key_listener)( unsigned char character ) );
void remove_key_listener( );

#define KEY_LSHIFT	0xA0
#define KEY_RSHIFT	0xA1
#define KEY_CTRL	0xA2
#define KEY_ALT		0xA3
#define KEY_CAPS	0xA4
#define KEY_F1		0xB1
#define KEY_F2		0xB2
#define KEY_F3		0xB3
#define KEY_F4		0xB4
#define KEY_F5		0xB5
#define KEY_F6		0xB6
#define KEY_F7		0xB7
#define KEY_F8		0xB8
#define KEY_F9		0xB9
#define KEY_F10		0xC0
#define KEY_F11		0xC1
#define KEY_F12		0xC2

#endif