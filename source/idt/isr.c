#include <idt/isr.h>
#include <boot/tty/tty.h>

void _fault_handler ( void )
{
    tty_print("SUCCESS!!!!!!!!!!!\n");
}
