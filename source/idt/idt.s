GLOBAL _idt_install
EXTERN g_idt_ptr

_idt_install:
    lidt [g_idt_ptr]
    ret
