[ BITS 32 ]
SECTION .boot2

BOOT_TWO_START:

GLOBAL BOOT_TWO_START
GLOBAL _start

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

