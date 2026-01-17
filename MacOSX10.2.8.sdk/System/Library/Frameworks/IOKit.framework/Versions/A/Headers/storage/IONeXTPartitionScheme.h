/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * This header contains the IONeXTPartitionScheme class definition.
 */

#ifndef _IONEXTPARTITIONSCHEME_H
#define _IONEXTPARTITIONSCHEME_H

#include <IOKit/IOTypes.h>

/*
 * kIONeXTPartitionSchemeClass is the name of the IONeXTPartitionScheme class.
 */

#define kIONeXTPartitionSchemeClass "IONeXTPartitionScheme"

/*
 * NeXT Partition Map Definitions
 */

#pragma pack(2) /* (enable 16-bit struct packing for dl_un, disk[tab,_label]) */

#include <sys/disktab.h>

/* Structure constants. */

#define	MAXLBLLEN 24                    /* (length of disk name)              */
#define	NBAD      1670                  /* (size of bad sector table in map)  */
#define	NLABELS   4                     /* (number of partition maps on disk) */

/* Structure aliases, for disktab and dl_un fields. */

#define dl_name          dl_dt.d_name
#define dl_type          dl_dt.d_type
#define dl_part          dl_dt.d_partitions
#define dl_front         dl_dt.d_front
#define dl_back          dl_dt.d_back
#define dl_ngroups       dl_dt.d_ngroups
#define dl_ag_size       dl_dt.d_ag_size
#define dl_ag_alts       dl_dt.d_ag_alts
#define dl_ag_off        dl_dt.d_ag_off
#define dl_secsize       dl_dt.d_secsize
#define dl_ncyl          dl_dt.d_ncylinders
#define dl_nsect         dl_dt.d_nsectors
#define dl_ntrack        dl_dt.d_ntracks
#define dl_rpm           dl_dt.d_rpm
#define dl_bootfile      dl_dt.d_bootfile
#define dl_boot0_blkno   dl_dt.d_boot0_blkno
#define dl_hostname      dl_dt.d_hostname
#define dl_rootpartition dl_dt.d_rootpartition
#define dl_rwpartition   dl_dt.d_rwpartition
#define dl_v3_checksum   dl_un.DL_v3_checksum
#define dl_bad           dl_un.DL_bad

/* Partition map, as found in block zero (or a redundant block) of the disk. */

typedef union
{
    UInt16         DL_v3_checksum;       /* (V3: ones complement checksum)    */
    SInt32         DL_bad[NBAD];         /* (V1-V2: bad sector table)         */
} dl_un_t;

typedef struct disk_label
{
    SInt32         dl_version;           /* (unique signature for map)        */
    SInt32         dl_label_blkno;       /* (block on which this map resides) */
    SInt32         dl_size;              /* (device block count)              */
    char           dl_label[MAXLBLLEN];  /* (device name)                     */
    UInt32         dl_flags;             /* (device flags)                    */
    UInt32         dl_tag;               /* (device tag)                      */
    struct disktab dl_dt;                /* (device info, partition entries)  */
    dl_un_t        dl_un;
    UInt16         dl_checksum;          /* (V1-V2: ones complement checksum) */
	
                   /* (add things here so dl_checksum stays in a fixed place) */
} disk_label_t;

/* Partition map signature (dl_version). */

#define DL_V1           0x4e655854                     /* (version 1: "NeXT") */
#define DL_V2           0x646c5632                     /* (version 2: "dlV2") */
#define DL_V3           0x646c5633                     /* (version 3: "dlV3") */
#define DL_VERSION      DL_V3                          /* (default version)   */

/* Partition map flags (dl_flags). */

#define DL_UNINIT       0x80000000                     /* (is uninitialized?) */

#pragma options align=reset              /* (reset to default struct packing) */

#endif /* !_IONEXTPARTITIONSCHEME_H */
