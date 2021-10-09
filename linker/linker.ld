OUTPUT_FORMAT("binary")
ENTRY("_bmain")

SECTIONS 
{
    . = 0x7c00 ;
    .text . :
    {
        *(.boot1)
        *(.boot2)
        *(.boot_text)
        *(.text)
    }
    .data . : 
    {
        *(.data)
        *(.rodata)
    }
}
