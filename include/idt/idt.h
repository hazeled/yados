#pragma once

#include <stdint.h>
#include <config.h>

// IDT descriptors may vary by architecture
typedef struct idt_entry_t {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
    uint16_t    kernel_cs;    // GDT selector that the code resides in, always kernel
    uint8_t     reserved;     // Always zero
    uint8_t     flags;
    uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

// Will set up IDT descriptors
void idt_initialize ( void );

// Adds an IDT descriptor to the global idt array
void _idt_add_descriptor ( unsigned char num, void* isr, uint8_t flags );

