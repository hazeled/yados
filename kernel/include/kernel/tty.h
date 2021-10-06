#pragma once

#include <stddef.h>
#include <stdint.h>

void tty_initialize(void);
void tty_putchar(char c);
void tty_putentryat(unsigned char c, uint8_t color, uint16_t x, uint16_t y);
void tty_write(const char* data, size_t size);
void tty_writestring(const char* data);
