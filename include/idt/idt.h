#pragma once

#include <stdint.h>
#include <config.h>

// IDT descriptors may vary by architecture
typedef struct __attribute__((packed)) idt_entry_t 
{
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
    uint16_t    kernel_cs;    // GDT selector that the code resides in, always kernel
    uint8_t     reserved;     // Always zero
    uint8_t     flags;
    uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} idt_entry_t;

struct idt_ptr_t 
{
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));
typedef struct idt_ptr_t idt_ptr_t;

// Set up IDT descriptors
void idt_initialize ( void );

// Install IDT
extern void _idt_install ( void );

// Adds an IDT descriptor to the global idt array
void _idt_set_descriptor ( unsigned char num, uint32_t isr, uint8_t flags );

