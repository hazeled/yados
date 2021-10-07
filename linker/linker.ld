OUTPUT_FORMAT("binary")
ENTRY("_bmain")

SECTIONS 
{
    . = 0x7c00 ;
    .text . :
    {
        *(.text)
        *(.k_start)
        *(.k_end)
    }

    .data . : 
    {
        *(.data)
        *(.rodata)
    }
}
