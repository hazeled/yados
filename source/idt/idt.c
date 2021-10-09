#include <boot/mem.h>
#include <idt/idt.h>

// Variable in boot.s
extern char CODESEG;

idt_entry_t idt[256];

void idt_initialize ( void )
{
    memset(idt, 0x00, sizeof(idt_entry_t) * 256);
}

void _idt_add_descriptor ( unsigned char num, void* isr, uint8_t flags )
{
    idt[num].isr_low   = (uint32_t)isr & 0xFFFF;
    idt[num].kernel_cs = CODESEG;
    idt[num].reserved  = 0;
    idt[num].flags     = flags;
    idt[num].isr_high  = (uint32_t)isr >> 16;
}
