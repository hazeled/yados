KINCLUDEDIR=include/

CFLAGS=$(CFLAGS) -ffreestanding -Wall -Wextra -I$(KINCLUDEDIR)
LIBS=$(LIBS) -nostdlib -lk -lgcc

KSRCDIR=source/kernel
ARCHDIR=source/arch/$(ARCH)
#include $(ARCHDIR)/make.config

SOURCES=$(KSRCDIR)/kernel.c 
OBJECTS:=$(SOURCE:.c=.o)

.SUFFIXES : .o .c

all : $(KERNELBUILDDIR)/yados.kernel

$(KERNELBUILDDIR)/yados.kernel : $(ARCHSOURCES) $(SOURCES)

.c.o:
	$(KERNEL_ARCH_CC) -MD -c $< -o $@ -std=gnull $(CFLAGS) $(LIBS) $(KERNEL_ARCH_CFLAGS) 

