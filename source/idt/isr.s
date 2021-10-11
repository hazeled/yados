GLOBAL _isr0
EXTERN _fault_handler
EXTERN tty_print 

a: db "SUCCESS!!!!!!", 0x0a, 0x00

_isr0:
    jmp $
    call _fault_handler
    cli
    push word 0
    jmp isr_common_stub
    sti

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x08   ; Load the Kernel Data Segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp    
    push eax
    mov eax, _fault_handler
    call eax       ; preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret
