OUTPUT_FORMAT("elf32-i386")
ENTRY("_start")

SECTIONS 
{
    . = 0x7e0f;
    .text :  
    {
        *(.boot2)
        *(.text)
        *(.rodata)
    }
}
