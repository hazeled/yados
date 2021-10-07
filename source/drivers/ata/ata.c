#include "boot/util.h"
#include <drivers/ata/ata.h>
#include <drivers/serial/serial.h>
#include <boot/tty/tty.h>

extern char BOOT_DRIVEINFO[2];

void driver_ata_init()
{
    tty_print("Hard drive info:\n");
    tty_print("   Number of heads   : %d\n", (int)BOOT_DRIVEINFO[0]);
    tty_print("   Sectors per track : %d\n", (int)BOOT_DRIVEINFO[1]);
}

void driver_ata_lba_to_chs ( int lba, int *head, int *track, int *sector )
{
    (*head)   = (lba % (BOOT_DRIVEINFO[1] * 2)) / BOOT_DRIVEINFO[1];
    (*track)  = (lba / (BOOT_DRIVEINFO[1] * 2));
    (*sector) = (lba %  BOOT_DRIVEINFO[1] + 1); 
}
