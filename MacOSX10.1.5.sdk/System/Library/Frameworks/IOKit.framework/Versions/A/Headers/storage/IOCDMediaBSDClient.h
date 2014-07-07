/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOCDMEDIABSDCLIENT_H
#define _IOCDMEDIABSDCLIENT_H

#include <sys/ioctl.h>
#include <sys/types.h>

#include <IOKit/storage/IOCDTypes.h>

/*
 * Definitions
 */

typedef struct
{
    u_int64_t offset;

    u_int8_t  sectorArea;
    u_int8_t  sectorType;

    u_int8_t  reserved0080[6];                     /* reserved, clear to zero */

    u_int32_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_cd_read_t;

typedef struct
{
    CDISRC    isrc;
    u_int8_t  track;

    u_int8_t  reserved0112[2];                     /* reserved, clear to zero */
} dk_cd_read_isrc_t;

typedef struct
{
    CDMCN     mcn;

    u_int8_t  reserved0112[2];                     /* reserved, clear to zero */
} dk_cd_read_mcn_t;

#define DKIOCCDREAD        _IOWR('d', 96, dk_cd_read_t)

#define DKIOCCDREADISRC    _IOWR('d', 97, dk_cd_read_isrc_t)
#define DKIOCCDREADMCN     _IOWR('d', 98, dk_cd_read_mcn_t)

#define DKIOCCDGETSPEED    _IOR('d', 99, u_int16_t)
#define DKIOCCDSETSPEED    _IOW('d', 99, u_int16_t)

/*
 * Kernel
 */

#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/storage/IOCDMedia.h>
#include <IOKit/storage/IOMediaBSDClient.h>

/*
 * Class
 */

class IOCDMediaBSDClient : public IOMediaBSDClient
{
    OSDeclareDefaultStructors(IOCDMediaBSDClient)

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

public:

    /*
     * Obtain this object's provider.  We override the superclass's method
     * to return a more specific subclass of IOService -- IOCDMedia.  This
     * method serves simply as a convenience to subclass developers.
     */

    virtual IOCDMedia * getProvider() const;

    /*
     * Process a CD-specific ioctl.
     */

    virtual int ioctl(dev_t, u_long cmd, caddr_t data, int, struct proc *);

    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 0);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 1);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 2);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 3);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 4);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 5);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 6);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 7);
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* !_IOCDMEDIABSDCLIENT_H */
