OUTPUT_FORMAT("binary")
ENTRY("_bmain")

SECTIONS 
{
    . = 0x7c00 ;
    .text . :
    {
        *(.text)
    }
    .k_start : { *(.k_start) }
    .k_text : { *(.k_text) }
    .k_end : { *(.k_end) }

    .data . : 
    {
        *(.data)
        *(.rodata)
    }
}
