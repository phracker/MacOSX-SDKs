/*
 * Copyright (c) 1998-2014 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * This header contains the IOFDiskPartitionScheme class definition.
 */

#ifndef _IOFDISKPARTITIONSCHEME_H
#define _IOFDISKPARTITIONSCHEME_H

#include <IOKit/IOTypes.h>

/*
 * kIOFDiskPartitionSchemeClass is the name of the IOFDiskPartitionScheme class.
 */

#define kIOFDiskPartitionSchemeClass "IOFDiskPartitionScheme"

/*
 * FDisk Partition Map Definitions
 */

#pragma pack(push, 1)                        /* (enable 8-bit struct packing) */

/* Structure constants. */

#define DISK_BLK0SZ sizeof(struct disk_blk0)    /* (size of partition map)    */
#define DISK_BOOTSZ 446                         /* (size of boot code in map) */
#define DISK_NPART  4                           /* (number of entries in map) */

/* Partition map entry. */

struct fdisk_part
{
    UInt8   bootid;    /* (is active boot partition?)                         */
    UInt8   beghead;   /* (beginning head)                                    */
    UInt8   begsect;   /* (beginning sector; beginning cylinder, high 2 bits) */
    UInt8   begcyl;    /* (beginning cylinder, low 8 bits)                    */
    UInt8   systid;    /* (type)                                              */
    UInt8   endhead;   /* (ending head)                                       */
    UInt8   endsect;   /* (ending sector; ending cylinder, high 2 bits)       */
    UInt8   endcyl;    /* (ending cylinder, low 8 bits)                       */
    UInt32  relsect;   /* (block start)                                       */
    UInt32  numsect;   /* (block count)                                       */
};

/* Partition map, as found in block zero of the disk (or extended partition). */

struct disk_blk0
{
    UInt8             bootcode[DISK_BOOTSZ];    /* (boot code)                */
    struct fdisk_part parts[DISK_NPART];        /* (partition entries)        */
    UInt16            signature;                /* (unique signature for map) */
};

/* Partition map signature (signature). */

#define DISK_SIGNATURE 0xAA55

/* Partition map entry types (systid). */

#define FDISK_PARTITION_TYPE_01 "DOS_FAT_12"
#define FDISK_PARTITION_TYPE_04 "DOS_FAT_16_S"
#define FDISK_PARTITION_TYPE_06 "DOS_FAT_16"
#define FDISK_PARTITION_TYPE_07 "Windows_NTFS"
#define FDISK_PARTITION_TYPE_0B "DOS_FAT_32"
#define FDISK_PARTITION_TYPE_0C "Windows_FAT_32"
#define FDISK_PARTITION_TYPE_0E "Windows_FAT_16"
#define FDISK_PARTITION_TYPE_42 "Windows_LDM"
#define FDISK_PARTITION_TYPE_82 "Linux_Swap"
#define FDISK_PARTITION_TYPE_83 "Linux"
#define FDISK_PARTITION_TYPE_8E "Linux_LVM"
#define FDISK_PARTITION_TYPE_A5 "FreeBSD"
#define FDISK_PARTITION_TYPE_A6 "OpenBSD"
#define FDISK_PARTITION_TYPE_A7 "Apple_Rhapsody_UFS"
#define FDISK_PARTITION_TYPE_A8 "Apple_UFS"
#define FDISK_PARTITION_TYPE_A9 "NetBSD"
#define FDISK_PARTITION_TYPE_AB "Apple_Boot"
#define FDISK_PARTITION_TYPE_AE "Apple_Encrypted"
#define FDISK_PARTITION_TYPE_AF "Apple_HFS"
#define FDISK_PARTITION_TYPE_FD "Linux_RAID"

#pragma pack(pop)                        /* (reset to default struct packing) */

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/storage/IOPartitionScheme.h>

/*
 * Class
 */

class __exported IOFDiskPartitionScheme : public IOPartitionScheme
{
    OSDeclareDefaultStructors(IOFDiskPartitionScheme);

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    OSSet * _partitions;    /* (set of media objects representing partitions) */

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free(void) APPLE_KEXT_OVERRIDE;

    /*
     * Scan the provider media for an FDisk partition map.  Returns the set
     * of media objects representing each of the partitions (the retain for
     * the set is passed to the caller), or null should no partition map be
     * found.  The default probe score can be adjusted up or down, based on
     * the confidence of the scan.
     */

    virtual OSSet * scan(SInt32 * score);

    /*
     * Ask whether the given partition is extended.
     */

    virtual bool isPartitionExtended(fdisk_part * partition);

    /*
     * Ask whether the given partition is used.
     */

    virtual bool isPartitionUsed(fdisk_part * partition);

    /*
     * Ask whether the given partition appears to be corrupt.  A partition that
     * is corrupt will cause the failure of the FDisk partition map recognition
     * altogether.
     */

    virtual bool isPartitionCorrupt( fdisk_part * partition,
                                     UInt32       partitionID,
                                     UInt32       fdiskBlock );

    /*
     * Ask whether the given partition appears to be invalid.  A partition that
     * is invalid will cause it to be skipped in the scan, but will not cause a
     * failure of the FDisk partition map recognition.
     */

    virtual bool isPartitionInvalid( fdisk_part * partition,
                                     UInt32       partitionID,
                                     UInt32       fdiskBlock );

    /*
     * Instantiate a new media object to represent the given partition.
     */

    virtual IOMedia * instantiateMediaObject( fdisk_part * partition,
                                              UInt32       partitionID,
                                              UInt32       fdiskBlock );

    /*
     * Allocate a new media object (called from instantiateMediaObject).
     */

    virtual IOMedia * instantiateDesiredMediaObject( fdisk_part * partition,
                                                     UInt32       partitionID,
                                                     UInt32       fdiskBlock );

public:

    /*
     * Initialize this object's minimal state.
     */

    virtual bool init(OSDictionary * properties = 0) APPLE_KEXT_OVERRIDE;

    /*
     * Determine whether the provider media contains an FDisk partition map.
     */

    virtual IOService * probe(IOService * provider, SInt32 * score) APPLE_KEXT_OVERRIDE;

    /*
     * Publish the new media objects which represent our partitions.
     */

    virtual bool start(IOService * provider) APPLE_KEXT_OVERRIDE;

    /*
     * Clean up after the media objects we published before terminating.
     */

    virtual void stop(IOService * provider) APPLE_KEXT_OVERRIDE;

    /*
     * Request that the provider media be re-scanned for partitions.
     */

    virtual IOReturn requestProbe(IOOptionBits options) APPLE_KEXT_OVERRIDE;

    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  0);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  1);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  2);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  3);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  4);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  5);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  6);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  7);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  8);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme,  9);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 10);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 11);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 12);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 13);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 14);
    OSMetaClassDeclareReservedUnused(IOFDiskPartitionScheme, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOFDISKPARTITIONSCHEME_H */
