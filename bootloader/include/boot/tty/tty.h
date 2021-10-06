#pragma once

#include <stdint.h>

// Bootloader tty functions
// Used for printing and output to the default tty
// NOT serial communcation, and not VGA communication

#define TTY_WIDTH  80
#define TTY_HEIGHT 25

void tty_initialize     ( void );
void tty_clear          ( void );
void tty_print_char     ( char c );
void tty_print_char_pos ( char c, uint8_t x, uint8_t y );
void tty_new_line       ( void );
void tty_print          ( char* str, ... );
// VERY minimal printf-like printing
// Formats:
//      %d : decimal
