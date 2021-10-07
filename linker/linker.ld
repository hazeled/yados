OUTPUT_FORMAT("binary")
ENTRY("_bmain")

SECTIONS 
{
    . = 0x7c00 ;
    .text . :
    {
        *(.text)
    }

    .data . : 
    {
        *(.data)
    }
}
