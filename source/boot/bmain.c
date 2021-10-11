#include <boot/boot.h>
#include <boot/util.h>
#include <drivers/io/io.h>
#include <boot/tty/tty.h>
#include <drivers/ata/ata.h>
#include <drivers/serial/serial.h>
#include <idt/idt.h>

extern char KERNEL_END;
extern char BOOT_TWO_START;
extern char CODESEG;
extern char DATASEG;
extern idt_ptr_t g_idt_ptr;
extern idt_entry_t idt[255];

void BOOT c_bmain ( void )
{
    tty_initialize();
    tty_clear();
    tty_print("Entered boot stage 2.5\n");

    tty_print("Initializing IDT\n");
    idt_initialize();

    tty_print("Starting serial driver...\n");
    driver_serial_init(DRIVER_SERIAL_PORT_COM1);
    if (!driver_serial_verify())
    {
        tty_print("ERROR STARTING SERIAL DRIVER\n");
    }
    else
    {
        tty_print("Serial driver verified\n");
    }
    serial_write("Serial initialized...\n");

    tty_print("Initializing ATA PIO driver\n");
    driver_ata_init();
    driver_ata_debug_print();
    
    tty_print("IDTPTR located at : %x\n", (int)&g_idt_ptr);
    tty_print("IDT located at : %x\n", (int)idt);
    tty_print("GDT DATASEG located at : %x\n", (int)&DATASEG);
    tty_print("GDT CODESEG located at : %x\n", (int)&CODESEG);
    tty_print("BOOT_TWO_START located at : %x\n", (int)&BOOT_TWO_START);
    tty_print("KERNEL_END located at : %x\n", (int)&KERNEL_END);

    __asm__("sti; int $1");
    __asm__("l: jmp l");

    tty_print("Hm\n");
}
