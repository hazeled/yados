#include <drivers/serial/serial.h>
#include <drivers/io/io.h>

unsigned int g_port;

void driver_serial_init ( unsigned int port )
{
    // Shamelessly stolen
    g_port = port;
    outb(port + 1, 0x00);    // Disable all interrupts
    outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(port + 1, 0x00);    //                  (hi byte)
    outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

bool driver_serial_verify ( void ) 
{
    outb(g_port + 0, 0xAE);
    if (inb(g_port + 0) != 0xAE) {
        return TRUE;
    }
    return FALSE;
}

int driver_serial_recieved ( void )
{
    return inb(g_port + 5) & 1;
}

char driver_serial_read ( void )
{
    while (driver_serial_recieved () == 0);
    return inb(g_port);
}

bool driver_serial_is_transmit_empty ( void )
{
    if ((inb(g_port + 5) & 0x20) == 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void driver_serial_write ( char c )
{
    while (!driver_serial_is_transmit_empty());
    outb(g_port, c);
}

void serial_write ( char* str )
{
    char* strptr = str;
    while (*strptr)
    {
        driver_serial_write(*strptr++);
    }
}
