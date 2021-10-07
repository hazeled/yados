#include <boot/util.h>
#include <boot/mem.h>

/*void num_to_str ( char *str, unsigned long num, unsigned base )
{
    static char digits[] = "0123456789abcdef";
    char buf[20], *ptr;

    ptr = buf + sizeof(buf) - 1;
    *ptr = '\0';
    do
    {
        ptr--;
        *ptr = digits[num % base];
        num /= base;
    } while (num > 0);
    
    // Flip
    char buf2[20], *ptr2;
    ptr = buf + sizeof(buf) - 1;
    ptr2 = buf2;
    while (*ptr)
    {
        *ptr2++ = *ptr--;
    }

    strcpy(str, buf2);
}*/
 

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3. */


char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
