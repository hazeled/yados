TOP=$(shell pwd)

export CFLAGS=-ffreestanding -fno-builtin -Wall -nostdlib

export BUILDDIR=$(TOP)/build

export BOOTBUILDDIR=$(BUILDDIR)/boot/
export KERNELBUILDDIR=$(BUILDDIR)/kernel/

include config/crosscomp/make.config

all : 
	@echo . To build YADOS, please use:
	@echo .	make \<architecture\>, e.g:
	@echo .	make i386
	@echo .
	@echo . The full list of options are: i386 x86_64

clean:
	rm -rf $(BUILDDIR)/*

i386 : Pre Pre_i386 Bootloader Kernel_i386
	@#$(MAKE) -C config/i386/

Pre_i386 : 

Kernel_i386 :
	@mkdir -p $(KERNELBUILDDIR)
	$(MAKE) -C kernel/ ARCH=i386

Pre:
	@mkdir -p $(BUILDDIR)

Bootloader : 
	@mkdir -p $(BOOTBUILDDIR)
	$(MAKE) -C bootloader


