/*
 * Copyright (c) 1998-2014 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _SYS_DISK_H_
#define _SYS_DISK_H_

#include <stdint.h>
#include <sys/ioctl.h>


/*
 * Definitions
 *
 * ioctl                                 description
 * ------------------------------------- ---------------------------------------
 * DKIOCEJECT                            eject media
 * DKIOCSYNCHRONIZE                      flush media
 *
 * DKIOCFORMAT                           format media
 * DKIOCGETFORMATCAPACITIES              get media's formattable capacities
 *
 * DKIOCGETBLOCKSIZE                     get media's block size
 * DKIOCGETBLOCKCOUNT                    get media's block count
 * DKIOCGETFIRMWAREPATH                  get media's firmware path
 *
 * DKIOCISFORMATTED                      is media formatted?
 * DKIOCISWRITABLE                       is media writable?
 *
 * DKIOCREQUESTIDLE                      idle media
 * DKIOCUNMAP                            delete unused data
 *
 * DKIOCGETLOCATION                      get device's physical location
 *
 * DKIOCGETMAXBLOCKCOUNTREAD             get maximum block count for reads
 * DKIOCGETMAXBLOCKCOUNTWRITE            get maximum block count for writes
 * DKIOCGETMAXBYTECOUNTREAD              get maximum byte count for reads
 * DKIOCGETMAXBYTECOUNTWRITE             get maximum byte count for writes
 *
 * DKIOCGETMAXSEGMENTCOUNTREAD           get maximum segment count for reads
 * DKIOCGETMAXSEGMENTCOUNTWRITE          get maximum segment count for writes
 * DKIOCGETMAXSEGMENTBYTECOUNTREAD       get maximum segment byte count for reads
 * DKIOCGETMAXSEGMENTBYTECOUNTWRITE      get maximum segment byte count for writes
 *
 * DKIOCGETMINSEGMENTALIGNMENTBYTECOUNT  get minimum segment alignment in bytes
 * DKIOCGETMAXSEGMENTADDRESSABLEBITCOUNT get maximum segment width in bits
 *
 * DKIOCGETFEATURES                      get device's feature set
 * DKIOCGETPHYSICALBLOCKSIZE             get device's block size
 * DKIOCGETCOMMANDPOOLSIZE               get device's queue depth
 *
 * DKIOCGETPROVISIONSTATUS               get device's block provision status
 * DKIOCGETIOMINSATURATIONBYTECOUNT      get minimum byte count to saturate storage bandwidth
 *
 * DKIOCGETERRORDESCRIPTION              get description of any drive error
 *
 * DKIOCGETMAXSWAPWRITE                  get maximum swap file write per day in bytes
 */

#define DK_FEATURE_BARRIER                    0x00000002
#define DK_FEATURE_PRIORITY                   0x00000004
#define DK_FEATURE_UNMAP                      0x00000010

#define DK_SYNCHRONIZE_OPTION_BARRIER         0x00000002

typedef struct{
	uint64_t               offset;
	uint64_t               length;
} dk_extent_t;

typedef struct{
	char                   path[128];
} dk_firmware_path_t;

typedef struct{
	uint64_t               blockCount;
	uint32_t               blockSize;

	uint8_t                reserved0096[4];    /* reserved, clear to zero */
} dk_format_capacity_t;

typedef struct{
	dk_format_capacity_t * capacities;
	uint32_t               capacitiesCount;    /* use zero to probe count */

#ifdef __LP64__
	uint8_t                reserved0096[4];    /* reserved, clear to zero */
#else /* !__LP64__ */
	uint8_t                reserved0064[8];    /* reserved, clear to zero */
#endif /* !__LP64__ */
} dk_format_capacities_t;

typedef struct{
	uint64_t               offset;
	uint64_t               length;

	uint32_t               options;

	uint8_t                reserved0160[4];    /* reserved, clear to zero */
} dk_synchronize_t;

typedef struct{
	dk_extent_t *          extents;
	uint32_t               extentsCount;

	uint32_t               options;

#ifndef __LP64__
	uint8_t                reserved0096[4];    /* reserved, clear to zero */
#endif /* !__LP64__ */
} dk_unmap_t;

typedef struct{
	uint64_t           flags;
	uint64_t           hotfile_size;           /* in bytes */
	uint64_t           hibernate_minsize;
	uint64_t           swapfile_pinning;

	uint64_t           padding[4];
} dk_corestorage_info_t;

#define DK_CORESTORAGE_PIN_YOUR_METADATA        0x00000001
#define DK_CORESTORAGE_ENABLE_HOTFILES          0x00000002
#define DK_CORESTORAGE_PIN_YOUR_SWAPFILE        0x00000004

#define DK_PROVISION_TYPE_MAPPED                0x00
#define DK_PROVISION_TYPE_DEALLOCATED           0x01
#define DK_PROVISION_TYPE_ANCHORED              0x02

typedef struct{
	uint64_t           offset;
	uint64_t           length;
	uint8_t            provisionType;
	uint8_t            reserved[7];
} dk_provision_extent_t;

typedef struct{
	uint64_t                offset;         /* input:        logical byte offset */
	uint64_t                length;         /* input:        byte length, 0 for whole length */
	uint64_t                options;        /*               reserved, clear to zero */
	uint32_t                reserved;       /*               not used */
	uint32_t                extentsCount;   /* input/output: count for extents */
	dk_provision_extent_t * extents;        /* output:       provision extents */
} dk_provision_status_t;

typedef struct{
	uint64_t               options;        /*               reserved, clear to zero */
	uint64_t               reserved;       /*               reserved, clear to zero */
	uint64_t               description_size;
	char *                 description;
} dk_error_description_t;

#define DK_LOCATION_INTERNAL                   0x00000000
#define DK_LOCATION_EXTERNAL                   0x00000001


#define DKIOCEJECT                            _IO('d', 21)
#define DKIOCSYNCHRONIZE                      _IOW('d', 22, dk_synchronize_t)

#define DKIOCFORMAT                           _IOW('d', 26, dk_format_capacity_t)
#define DKIOCGETFORMATCAPACITIES              _IOWR('d', 26, dk_format_capacities_t)

#define DKIOCGETBLOCKSIZE                     _IOR('d', 24, uint32_t)
#define DKIOCGETBLOCKCOUNT                    _IOR('d', 25, uint64_t)
#define DKIOCGETFIRMWAREPATH                  _IOR('d', 28, dk_firmware_path_t)

#define DKIOCISFORMATTED                      _IOR('d', 23, uint32_t)
#define DKIOCISWRITABLE                       _IOR('d', 29, uint32_t)

#define DKIOCREQUESTIDLE                      _IO('d', 30)
#define DKIOCUNMAP                            _IOW('d', 31, dk_unmap_t)
#define DKIOCCORESTORAGE                      _IOR('d', 32, dk_corestorage_info_t)

#define DKIOCGETLOCATION                      _IOR('d', 33, uint64_t)

#define DKIOCGETMAXBLOCKCOUNTREAD             _IOR('d', 64, uint64_t)
#define DKIOCGETMAXBLOCKCOUNTWRITE            _IOR('d', 65, uint64_t)
#define DKIOCGETMAXBYTECOUNTREAD              _IOR('d', 70, uint64_t)
#define DKIOCGETMAXBYTECOUNTWRITE             _IOR('d', 71, uint64_t)

#define DKIOCGETMAXSEGMENTCOUNTREAD           _IOR('d', 66, uint64_t)
#define DKIOCGETMAXSEGMENTCOUNTWRITE          _IOR('d', 67, uint64_t)
#define DKIOCGETMAXSEGMENTBYTECOUNTREAD       _IOR('d', 68, uint64_t)
#define DKIOCGETMAXSEGMENTBYTECOUNTWRITE      _IOR('d', 69, uint64_t)

#define DKIOCGETMINSEGMENTALIGNMENTBYTECOUNT  _IOR('d', 74, uint64_t)
#define DKIOCGETMAXSEGMENTADDRESSABLEBITCOUNT _IOR('d', 75, uint64_t)

#define DKIOCGETFEATURES                      _IOR('d', 76, uint32_t)
#define DKIOCGETPHYSICALBLOCKSIZE             _IOR('d', 77, uint32_t)
#define DKIOCGETCOMMANDPOOLSIZE               _IOR('d', 78, uint32_t)

#define DKIOCGETPROVISIONSTATUS               _IOWR('d', 79, dk_provision_status_t)

#define DKIOCGETERRORDESCRIPTION              _IOR('d', 80, dk_error_description_t)

#define DKIOCSYNCHRONIZECACHE                 _IO('d', 22)

#define DK_FEATURE_FORCE_UNIT_ACCESS          0x00000001

#define DK_ENCRYPTION_TYPE_AES_CBC            1
#define DK_ENCRYPTION_TYPE_AES_XEX            2
#define DK_ENCRYPTION_TYPE_AES_XTS            3

#define DK_TIER_MASK                          0xC0
#define DK_TIER_SHIFT                         6

#define DK_TIER_TO_PRIORITY(tier)             (((tier) << DK_TIER_SHIFT) | ~DK_TIER_MASK)
#define DK_PRIORITY_TO_TIER(priority)         ((priority) >> DK_TIER_SHIFT)

typedef struct{
	uint64_t               offset;
	uint64_t               length;

	uint8_t                reserved0128[12];   /* reserved, clear to zero */

	dev_t                  dev;
} dk_physical_extent_t;

typedef struct{
	dk_extent_t *          extents;
	uint32_t               extentsCount;

	uint8_t                tier;

#ifdef __LP64__
	uint8_t                reserved0104[3];    /* reserved, clear to zero */
#else /* !__LP64__ */
	uint8_t                reserved0072[7];    /* reserved, clear to zero */
#endif /* !__LP64__ */
} dk_set_tier_t;

#define DKIOCSETBLOCKSIZE                     _IOW('d', 24, uint32_t)
#define DKIOCGETBSDUNIT                       _IOR('d', 27, uint32_t)
#define DKIOCISSOLIDSTATE                     _IOR('d', 79, uint32_t)
#define DKIOCISVIRTUAL                        _IOR('d', 72, uint32_t)
#define DKIOCGETBASE                          _IOR('d', 73, uint64_t)
#define DKIOCGETTHROTTLEMASK                  _IOR('d', 80, uint64_t)
#define DKIOCLOCKPHYSICALEXTENTS              _IO('d', 81)
#define DKIOCGETPHYSICALEXTENT                _IOWR('d', 82, dk_physical_extent_t)
#define DKIOCUNLOCKPHYSICALEXTENTS            _IO('d', 83)
#define DKIOCSETTIER                          _IOW('d', 85, dk_set_tier_t)
#define DKIOCGETENCRYPTIONTYPE                _IOR('d', 86, uint32_t)
#define DKIOCISLOWPOWERMODE                   _IOR('d', 87, uint32_t)
#define DKIOCGETIOMINSATURATIONBYTECOUNT      _IOR('d', 88, uint32_t)



#endif  /* _SYS_DISK_H_ */
