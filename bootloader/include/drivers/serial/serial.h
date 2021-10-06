#pragma once

#include <bool.h>

#define DRIVER_SERIAL_PORT_COM1 0x3f8

void driver_serial_init ( unsigned int port );
bool driver_serial_verify ( void );
bool driver_serial_is_transmit_empty ( void );

int  driver_serial_recieved ( void );
void driver_serial_write ( char c );

// does not specifically interract with driver/ports,
// so not prefixed with driver
void serial_write ( char* str );
