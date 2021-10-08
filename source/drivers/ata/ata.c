#define DRIVER_ATA_IMPORT_STRUCTS
#include <drivers/ata/ata.h>
#include <drivers/io/io.h>
#include <boot/tty/tty.h>

extern char BOOT_DRIVEINFO[2];

void driver_ata_init ( void )
{
    _driver_ata_identify(TRUE);
}

void _driver_ata_identify ( bool pri )
{
    _driver_ata_select(pri);
    // Send identify command
    outb(DRIVER_ATA_IO_BASE_PRI + COMMAND, 0xEC);

    // Set sec->lba_hi to 0
    outb(DRIVER_ATA_IO_BASE_PRI + SECTOR_COUNT, 0);
    outb(DRIVER_ATA_IO_BASE_PRI + LBA_LO,       0);
    outb(DRIVER_ATA_IO_BASE_PRI + LBA_MID,      0);
    outb(DRIVER_ATA_IO_BASE_PRI + LBA_HI,       0);
}

void _driver_ata_select ( bool pri ) 
{
    char port = pri ? 0xA0 : 0xB0;
    // Send identify command to primary bus 
    // Query primary port
    for (int i = 0; i < 5; i++)
    {
       outb(DRIVER_ATA_IO_BASE_PRI + DRIVE, port);
    }
}

void driver_ata_debug_print ( void )
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
