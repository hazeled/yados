[ BITS 16 ]
;[ ORG 0x7C00 ] 

GLOBAL 		_bmain
GLOBAL      BOOT_DRIVEINFO
GLOBAL      CODESEG
GLOBAL      DATASEG

SECTION .boot1

	jmp 	_bmain

_bmain:
	
	cli
	;mov 	ax, 0x07C0
	;mov 	ds, ax
	xor 	ax, ax 
	mov 	sp, 0x7C00
	mov 	ss, ax
	;mov 	es, ax
	sti 

	mov [DISK], dl

	cld
	call 	pre512_clearscreen
	mov 	si, MSG_TITLE
	call	pre512_printstr
	mov 	si, MSG_BOOTING
	call 	pre512_printstr

.reset:
	mov 	si, MSG_RESETTING
	call 	pre512_printstr
	mov 	ax, 0
	mov 	dl, 0
	int 	13h
	jc 		.reset ; Error has occured, reset again
	mov 	ax, 0
.read:
	inc 	ax
	cmp 	ax, 4
	je 		.readfailed
	mov 	si, MSG_READING
	call 	pre512_printstr
	push 	ax
	; Load at 0x7E00
	mov 	bx, 0x07E0
	mov 	es, bx
	xor 	bx, bx
	mov 	ah, 0x02
	mov 	al, 10   ; sectors to read
	mov 	ch, 0x00
	mov 	cl, 0x02
	mov 	dh, 0x00
	mov 	dl, [DISK]
	int 	13h ; do the read!

	mov 	bh, ah
	pop 	ax
	jc 		.read ; loop if error
	jmp 	.readsuccess 
.readfailed: 
	mov 	si, MSG_READFAILED
	call 	pre512_printstr
	mov 	dx, 00
	mov 	dl, bh
	hlt
	jmp $
.readsuccess:

    ; These values are typically more accurate than the "default" values on 
    ; hard drives. However, it's typically the other way around on USB sticks.
    ; It might be a good idea to check to see if the boot is occuring on a hard
    ; drive or other device, and use the needed values accordingly.
.readdrivegeom:
    ; Get drive geometry
    mov     si, MSG_DRIVEGEOM
    call    pre512_printstr
    mov     ah, 0x08
    int     0x13
    jc .readdrivegeom
    and     cl, 0x3F
    mov     [BOOT_DRIVEINFO.one], dh ; Number of heads
    mov     [BOOT_DRIVEINFO.two], cl ; Sec per track

	; Disable cursor before moving to PM
	mov 	ah, 0x01
	mov 	ch, 0x3F
	int 	0x10

.setupGDT:
	mov 	si, MSG_ENABLEGDT
	call 	pre512_printstr
	cli

	; Now set up the basic boot GDT and enable protected mode
	lgdt 	[GDTdescriptor]
	mov 	eax, cr0
	or 		eax, 1
	mov 	cr0, eax
	
	jmp CODESEG:startprotected

; Note to self: could possible have a descriptor soley for stack
; If implemented, make sure to enable the direction bit
GDT:
.nulldesc:

	dq 0

.code: ; cs should point here 

	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0

.data:

	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0 

GDTend:

GDTdescriptor:
	dw GDTend - GDT - 1	; Size of gdt
	dd GDT

CODESEG equ GDT.code - GDT
DATASEG equ GDT.data - GDT

pre512_printnl:

	push 	ax
	mov 	ah, 0x0E
	mov 	al, 13
	int 	0x10
	mov 	al, 10
	int 	0x10
	pop 	ax
	ret

pre512_printstr:

	push 	ax
	mov 	ah, 0x0E
.loop:
	lodsb        
	or 		al, al 
	jz 		.done  
	int 	0x10      
	jmp 	.loop
.done:
	call 	pre512_printnl
	pop 	ax
	ret

pre512_clearscreen:

	mov 	ah, 0x00
	mov 	ax, 0x3
	int 	0x10
	ret

DISK:
	db 0x0

BOOT_DRIVEINFO:
.one:
    db 0x00
.two:
    db 0x0

MSG_TITLE     db "YADB", 0
MSG_BOOTING   db "Booting YADOS", 0
MSG_RESETTING db "Reseting drive (should not loop)", 0
MSG_READING   db "Preforming read (should not loop)", 0
MSG_DRIVEGEOM db "Reading drive geometry (should not loop)", 0
MSG_READFAILED db "Read has failed three times. Halting...", 0
MSG_ENABLEGDT db "Enabling Global Descriptor Table...", 0
MSG_PASTBREAK db "Jumping past 512 byte break", 0

times 510 - ($ - $$) db 0
dw 0xaa55

[ BITS 32 ]

startprotected:

    ; Setup flat memory model
	mov 	ax, DATASEG
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov 	ss, ax
