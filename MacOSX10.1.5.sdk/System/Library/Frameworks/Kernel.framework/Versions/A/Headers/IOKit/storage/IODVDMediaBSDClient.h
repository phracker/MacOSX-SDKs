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

#ifndef _IODVDMEDIABSDCLIENT_H
#define _IODVDMEDIABSDCLIENT_H

#include <sys/ioctl.h>
#include <sys/types.h>

#include <IOKit/storage/IODVDTypes.h>

/*
 * Definitions
 */

typedef struct
{
    u_int8_t  format;

    u_int8_t  reserved0008[3];                     /* reserved, clear to zero */

    u_int32_t address;
    u_int8_t  grantID;
    u_int8_t  layer;

    u_int16_t bufferLength;
    void *    buffer;
} dk_dvd_read_structure_t;

typedef struct
{
    u_int8_t  format;
    u_int8_t  keyClass;

    u_int8_t  reserved0016[2];                     /* reserved, clear to zero */

    u_int32_t address;
    u_int8_t  grantID;

    u_int8_t  reserved0072[1];                     /* reserved, clear to zero */

    u_int16_t bufferLength;
    void *    buffer;
} dk_dvd_report_key_t;

typedef struct
{
    u_int8_t  format;
    u_int8_t  keyClass;

    u_int8_t  reserved0016[6];                     /* reserved, clear to zero */

    u_int8_t  grantID;

    u_int8_t  reserved0072[1];                     /* reserved, clear to zero */

    u_int16_t bufferLength;
    void *    buffer;
} dk_dvd_send_key_t;

#define DKIOCDVDREADSTRUCTURE _IOW('d', 128, dk_dvd_read_structure_t)
#define DKIOCDVDREPORTKEY     _IOW('d', 129, dk_dvd_report_key_t)
#define DKIOCDVDSENDKEY       _IOW('d', 130, dk_dvd_send_key_t)

#define DKIOCDVDGETSPEED      _IOR('d', 131, u_int16_t)
#define DKIOCDVDSETSPEED      _IOW('d', 131, u_int16_t)

/*
 * Kernel
 */

#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/storage/IODVDMedia.h>
#include <IOKit/storage/IOMediaBSDClient.h>

/*
 * Class
 */

class IODVDMediaBSDClient : public IOMediaBSDClient
{
    OSDeclareDefaultStructors(IODVDMediaBSDClient)

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

public:

    /*
     * Obtain this object's provider.   We override the superclass's method
     * to return a more specific subclass of IOService -- IODVDMedia.  This
     * method serves simply as a convenience to subclass developers.
     */

    virtual IODVDMedia * getProvider() const;

    /*
     * Process a DVD-specific ioctl.
     */

    virtual int ioctl(dev_t, u_long cmd, caddr_t data, int, struct proc *);

    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 0);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 1);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 2);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 3);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 4);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 5);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 6);
    OSMetaClassDeclareReservedUnused(IODVDMediaBSDClient, 7);
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* !_IODVDMEDIABSDCLIENT_H */
