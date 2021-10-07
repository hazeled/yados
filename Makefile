ASM=nasm
OBJCOPY=objcopy
include config/crosscomp/make.config

CCINCLUDEDIR=-Iinclude
CFLAGS := $(CCINCLUDEDIR) -ffreestanding -Wall 
ASMFLAGS=
COPYFLAGS=status=noxfer conv=notrunc
LDFLAGS=

SRCDIR=source/
K_SRCDIR=$(SRCDIR)kernel/
BUILDDIR=build/

CSRCS  := $(wildcard $(SRCDIR)/*/*.c)
CSRCS  += $(wildcard $(SRCDIR)/*/*/*.c) 
COBJS  := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)%.o,$(CSRCS))

K_ASMSRCS := $(wildcard $(K_SRCDIR)/*.s)
K_ASMOBJS := $(patsubst $(K_SRCDIR)/%.s,$(BUILDDIR)%.asmo,$(K_ASMSRCS))
#-include $(COBJS:.c=.d)
#COBJS  := $(patsubst $(SRCDIR)/%,$(BOOTBUILDDIR)%,$(COBJS))

.PHONY : all clean

all : $(BUILDDIR)yados.bin

clean : 
	rm -rf $(BUILDDIR)/*

$(BUILDDIR)yados.bin : $(BUILDDIR)boot1.elf32 $(BUILDDIR)boot/boot_two.asmo $(COBJS) $(K_ASMOBJS)
	$(CROSS_LD) $(LDFLAGS) $^ -Tlinker/linker.ld -o $@ 	

$(BUILDDIR)boot1.elf32 : source/boot/boot.s
	$(ASM) -f elf32 $^ -o $@

$(BUILDDIR)%.o : $(SRCDIR)/%.c
	mkdir -p $(patsubst %$(notdir $@),%,$@)
	$(CROSS_CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)%.asmo : $(SRCDIR)%.s
	mkdir -p $(patsubst %$(notdir $@),%,$@)
	$(ASM) -f elf32 $(ASMFLAGS) $< -o $@

$(BUILDDIR)%.asmo : $(K_SRCDIR)%.s
	mkdir -p $(patsubst %$(notdir $@),%,$@)
	$(ASM) -f elf32 $(ASMFLAGS) $< -o $@
