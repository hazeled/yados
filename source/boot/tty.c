#include <boot/tty/tty.h>
#include <boot/util.h>
#include <stdarg.h>

int cursor_x = 0;
int cursor_y = 0;

void tty_initialize ( void )
{
}

void tty_clear ( void )
{
    volatile unsigned char* vidmem = (unsigned char*)0xb8000;
    for (uint16_t i = 0; i < TTY_WIDTH * TTY_HEIGHT; i++)
    {
        *vidmem++ = 0x00;
        *vidmem++ = 0x00;
    }
}

void tty_print_char ( char c )
{
    if (cursor_x == TTY_WIDTH - 1) 
    {
        tty_new_line();
    }
    tty_print_char_pos(c, cursor_x++, cursor_y);
}

void tty_print_char_pos ( char c, uint8_t x, uint8_t y )
{
    volatile unsigned char* vidmem = (volatile unsigned char*)0xb8000;
    vidmem += y * TTY_WIDTH * 2;
    vidmem += x * 2;
    vidmem[0] = c;
    vidmem[1] = 15;
}

void tty_new_line ( void ) 
{
    cursor_x = 0;
    cursor_y++;
}

void do_nothing () { return; }
void tty_print ( char* str, ... )
{
    va_list args;
    va_start (args, str);

    char* strptr = str;
    // sprintf();
    while (*strptr != '\0')
    {
        switch(*strptr)
        {
            case '\n':
                tty_new_line();
                strptr++;
                break;
            case '%':
                strptr++;
                int num;
                char strbuf[20];
                num = va_arg(args, int);
                switch(*strptr)
                {
                    case 'd':
                        itoa(num, &strbuf[0], 10);
                        tty_print(strbuf);
                        strptr++;
                        break;
                    case 'x':
                        itoa(num, &strbuf[0], 16);
                        tty_print("0x");
                        tty_print(strbuf);
                        break;
                    default:
                        tty_print("%");
                        break;
                }
                break;
            default:
                tty_print_char(*strptr++);
                break;
        }

    }
}
