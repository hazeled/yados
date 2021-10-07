#include <boot/mem.h>

void memcpy ( void* dst, void* src, unsigned int bytes )
{
    unsigned int i;
    for (i = 0; i < bytes; i++)
    {
        *(char*)dst = *(char*)src;
        dst++;
        src++;
    }
}

void strcpy ( char* dst, char* src ) 
{
    while (*src)
    {
        *dst++ = *src++;
    }
}
