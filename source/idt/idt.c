#include <boot/mem.h>
#include <idt/idt.h>
#include <idt/isr.h>
#include <boot/tty/tty.h>

// Variable in boot.s
extern char CODESEG;

idt_entry_t idt[256];
idt_ptr_t g_idt_ptr;

void idt_initialize ( void )
{
    memset(idt, 0x00, sizeof(idt_entry_t) * 256);

    g_idt_ptr.limit = (sizeof (idt_entry_t) * 256) - 1;
    g_idt_ptr.base  = (uint32_t)&idt;
    
    _idt_install();
}

void _idt_set_descriptor ( unsigned char num, uint32_t isr, uint8_t flags )
{
    idt[num].isr_low   = isr & 0xFFFF;
    idt[num].kernel_cs = (uint16_t)&CODESEG;
    idt[num].reserved  = 0;
    idt[num].flags     = flags;
    idt[num].isr_high  = (isr >> 16) & 0xFFFF;
}
