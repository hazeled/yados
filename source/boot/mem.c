#include <boot/boot.h>
#include <boot/mem.h>

void* BOOT memcpy ( void* dst, const void* src, unsigned int size )
{
    void* temp = dst;
    __asm__ volatile (
        "rep movsb"
        :"=D"(dst),"=S"(src),"=c"(size)
        :"0"(dst),"1"(src),"2"(size)
        :"memory"
    );
    return temp;
}

void BOOT strcpy ( char* dst, char* src ) 
{
    while (*src)
    {
        *dst++ = *src++;
    }
}
