#pragma once

#include <bool.h>

/* Very basic ATA driver. Includes basic loading and reading from drive in
 * LBA format 
 */

/* Data that's only useful to ata driver implementations
 * Hidden behind define as to not clog up global namespace*/
#ifdef DRIVER_ATA_IMPORT_STRUCTS

#define DRIVER_ATA_IO_BASE_PRI 0x1F0
#define DRIVER_ATA_IO_BASE_SEC 0x3F6

enum driver_ata_port
{
    DATA = 0,
    ERR,
    SECTOR_COUNT,
    LBA_LO,
    LBA_MID,
    LBA_HI,
    DRIVE,
    COMMAND
};

#endif

void  driver_ata_init ( void ) ;

/* Send the "Identify" command to the acpi device and record 
 * the information returned.
 * If pri is true, query the master bus. Otherwise,
 * query the slave.
 */ 
void _driver_ata_identify ( bool pri );

/* Select a master or slave bus.
 * Will select five times in order to add a 400ns delay
 * If pri is true, select the master bus. Otherwise,
 * select the slave.
 */ 
void _driver_ata_select ( bool pri );

void  driver_ata_debug_print ( void );


void  driver_ata_lba_to_chs ( int lba, int *head, int *track, int *sector );
