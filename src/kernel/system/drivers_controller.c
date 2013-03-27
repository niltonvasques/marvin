#include <system.h>
#include <keyboard.h>

void keyboard_register_listener( void (*key_listener)(unsigned char character) ){
      add_key_listener( key_listener );
}

void keyboard_unregister_listener( ){
      remove_key_listener();
}