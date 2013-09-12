#include <system.h>
#include <libio.h>
#include <libtimer.h>

/* This will keep track of how many ticks that the system
*  has been running for */
unsigned long timer_ticks = 0;
void (*t_handler)(void);
/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler( struct regs *r __attribute__((__unused__)) )
{
      /* Increment our 'tick count' */
      timer_ticks++;

      /* Every 100 clocks (approximately 1 second), we will
      *  display a message on the screen */
      if (timer_ticks % 100 == 0)
      {

	if( t_handler )	{
		t_handler();
	}
      }
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
      timer_phase(100);	  
      /* Installs 'timer_handler' to IRQ0 */
      irq_install_handler(0, timer_handler);
}

void register_timer_handler( void(*handler)(void) ){
	t_handler = handler;
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}


