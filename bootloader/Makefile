ASM=nasm
OBJCOPY=objcopy

CCINCLUDEDIR=-Iinclude
CFLAGS := $(CFLAGS) $(CCINCLUDEDIR) 
ASMFLAGS=
COPYFLAGS=status=noxfer conv=notrunc
LDFLAGS=


SRCDIR=source/

CSRCS  := $(wildcard $(SRCDIR)/*/*.c)
CSRCS  += $(wildcard $(SRCDIR)/*/*/*.c) 
COBJS  := $(patsubst $(SRCDIR)/%.c,$(BOOTBUILDDIR)%.o,$(CSRCS))
#-include $(COBJS:.c=.d)
#COBJS  := $(patsubst $(SRCDIR)/%,$(BOOTBUILDDIR)%,$(COBJS))

.PHONY : all

all : $(BOOTBUILDDIR)boot.bin

$(BOOTBUILDDIR)boot.bin : $(BOOTBUILDDIR)boot1.elf32 $(BOOTBUILDDIR)boot/boot_two.b $(COBJS) # $(BOOTBUILDDIR)boot2.elf32 
	$(CROSS_LD) $(LDFLAGS) $^ -Tlinker/boot.ld -o $@ 	

$(BOOTBUILDDIR)boot1.elf32 : source/boot/boot.s
	$(ASM) -f elf32 $^ -o $@

$(BOOTBUILDDIR)%.o : $(SRCDIR)/%.c
	mkdir -p $(patsubst %$(notdir $@),%,$@)
	$(CROSS_CC) $(CFLAGS) -c $< -o $@

$(BOOTBUILDDIR)%.b : $(SRCDIR)%.s
	mkdir -p $(patsubst %$(notdir $@),%,$@)
	$(ASM) -f elf32 $(ASMFLAGS) $< -o $@

