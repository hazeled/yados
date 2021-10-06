#include <kernel/tty.h>

#include <stddef.h>
#include <stdint.h>

// Printing to ONLY the TTY

const size_t TTY_VGA_WIDTH = 80;
const size_t TTY_VGA_HEIGHT = 25;
uint16_t* const TTY_MEMORY = (uint16_t*)0xB8000;


