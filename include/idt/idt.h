#pragma once

#include <stdint.h>
#include <config.h>

// IDT descriptors vary by architecture

#ifdef YADOS_BUILD_IA32
typedef struct IDT_descriptor
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t offset_2;
} IDT_descriptor;
#endif

#ifdef YADOS_BUILD_AMD64
struct IDTDescr {
   uint16_t offset_1; 
   uint16_t selector;
   uint8_t  IST;      
   uint8_t  type_attr; 
   uint16_t offset_2; 
   uint32_t offset_3; 
   uint32_t zero;     
};
#endif

void idt_initialize();
