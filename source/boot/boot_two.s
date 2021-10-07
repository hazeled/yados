[ BITS 32 ]

BOOT_TWO_START:

GLOBAL BOOT_TWO_START
GLOBAL _start

SECTION .boot2
EXTERN tty_print
EXTERN tty_clear
EXTERN c_bmain

jmp _start

%macro print 1+
     section .data    
 %%string:
     db %1,0
     section .text    
     push %%string
     call tty_print
%endmacro

_start:

    call    c_bmain

	jmp 	$

