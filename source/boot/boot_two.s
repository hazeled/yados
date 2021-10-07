[ BITS 32 ]

global _start

section .boot2
extern tty_print
extern tty_clear
extern c_bmain

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

