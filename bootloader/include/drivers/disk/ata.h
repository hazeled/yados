#pragma once

/* Very basic ATA driver. Includes basic loading and reading from drive in
 * LBA format 
 */

void driver_ata_init ( void );
void driver_ata_lba_to_chs ( int lba, int *head, int *track, int *sector );
