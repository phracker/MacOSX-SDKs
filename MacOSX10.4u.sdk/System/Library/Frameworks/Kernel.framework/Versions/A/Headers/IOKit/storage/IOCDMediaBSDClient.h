/*
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOCDMEDIABSDCLIENT_H
#define _IOCDMEDIABSDCLIENT_H

#include <sys/ioctl.h>
#include <sys/types.h>

#include <IOKit/storage/IOCDTypes.h>

/*
 * Definitions
 *
 * ioctl                        description
 * ---------------------------- ------------------------------------------------
 * DKIOCCDREAD                  see IOCDMedia::readCD()           in IOCDMedia.h
 * DKIOCCDREADTOC               see IOCDMedia::readTOC()          in IOCDMedia.h
 *
 * DKIOCCDREADDISCINFO          see IOCDMedia::readDiscInfo()     in IOCDMedia.h
 * DKIOCCDREADTRACKINFO         see IOCDMedia::readTrackInfo()    in IOCDMedia.h
 *
 * DKIOCCDREADISRC              see IOCDMedia::readISRC()         in IOCDMedia.h
 * DKIOCCDREADMCN               see IOCDMedia::readMCN()          in IOCDMedia.h
 *
 * DKIOCCDGETSPEED              see IOCDMedia::getSpeed()         in IOCDMedia.h
 * DKIOCCDSETSPEED              see IOCDMedia::setSpeed()         in IOCDMedia.h
 *
 *         in /System/Library/Frameworks/Kernel.framework/Headers/IOKit/storage/
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

typedef struct
{
    u_int8_t  format;
    u_int8_t  formatAsTime;

    u_int8_t  reserved0016[5];                     /* reserved, clear to zero */

    union
    {
        u_int8_t session;
        u_int8_t track;
    } address;

    u_int8_t  reserved0064[2];                     /* reserved, clear to zero */

    u_int16_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_cd_read_toc_t;

typedef struct
{
    u_int8_t  reserved0000[10];                    /* reserved, clear to zero */

    u_int16_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_cd_read_disc_info_t;

typedef struct
{
    u_int8_t  reserved0000[4];                     /* reserved, clear to zero */

    u_int32_t address;
    u_int8_t  addressType;

    u_int8_t  reserved0072[1];                     /* reserved, clear to zero */

    u_int16_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_cd_read_track_info_t;

#define DKIOCCDREAD          _IOWR('d', 96, dk_cd_read_t)

#define DKIOCCDREADISRC      _IOWR('d', 97, dk_cd_read_isrc_t)
#define DKIOCCDREADMCN       _IOWR('d', 98, dk_cd_read_mcn_t)

#define DKIOCCDGETSPEED      _IOR('d', 99, u_int16_t)
#define DKIOCCDSETSPEED      _IOW('d', 99, u_int16_t)

#define DKIOCCDREADTOC       _IOWR('d', 100, dk_cd_read_toc_t)

#define DKIOCCDREADDISCINFO  _IOWR('d', 101, dk_cd_read_disc_info_t)
#define DKIOCCDREADTRACKINFO _IOWR('d', 102, dk_cd_read_track_info_t)

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

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

    virtual int ioctl(dev_t, u_long cmd, caddr_t data, int, proc_t);

    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 0);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 1);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 2);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 3);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 4);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 5);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 6);
    OSMetaClassDeclareReservedUnused(IOCDMediaBSDClient, 7);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOCDMEDIABSDCLIENT_H */
