#include <boot/boot.h>
#include <boot/tty/tty.h>
#include <boot/util.h>
#include <boot/mem.h>
#include <stdarg.h>

int cursor_x = 0;
int cursor_y = 0;

void BOOT tty_initialize ( void )
{
}

void BOOT tty_clear ( void )
{
    volatile unsigned char* vidmem = (unsigned char*)0xb8000;
    for (uint16_t i = 0; i < TTY_WIDTH * TTY_HEIGHT; i++)
    {
        *vidmem++ = 0x00;
        *vidmem++ = 0x00;
    }
}

void BOOT tty_print_char ( char c )
{
    if (cursor_x == TTY_WIDTH - 1) 
    {
        tty_new_line();
    }
    tty_print_char_pos(c, cursor_x++, cursor_y);
}

void BOOT tty_print_char_pos ( char c, uint8_t x, uint8_t y )
{
    volatile unsigned char* vidmem = (volatile unsigned char*)0xb8000;
    vidmem += y * TTY_WIDTH * 2;
    vidmem += x * 2;
    vidmem[0] = c;
    vidmem[1] = 15;
}

void BOOT tty_new_line ( void ) 
{
    if (cursor_y == TTY_HEIGHT - 1)
    {
        // Scroll TTY
        volatile unsigned char* vidmem = (volatile unsigned char*)0xb8000;
        // 160 is the size of a single line
        memcpy(vidmem, &vidmem[160], 160 * TTY_HEIGHT - 1);
    }
    else
    {
        // Move cursor normally
        cursor_y++;
    }
    cursor_x = 0;
}

void BOOT tty_print ( char* str, ... )
{
    va_list args;
    va_start (args, str);

    char* strptr = str;
    // sprintf();
    while (*strptr != '\0')
    {
        switch(*strptr)
        {
            case '\\':
                strptr++;
                tty_print(strptr++);
                break;
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
                        itoa(num, strbuf, 10);
                        tty_print(strbuf);
                        strptr++;
                        break;
                    case 'x':
                        itoa(num, strbuf, 16);
                        tty_print("0x");
                        tty_print(strbuf);
                        strptr++;
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
