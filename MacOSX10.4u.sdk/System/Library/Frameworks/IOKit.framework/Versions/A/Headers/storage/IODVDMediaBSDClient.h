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

#ifndef _IODVDMEDIABSDCLIENT_H
#define _IODVDMEDIABSDCLIENT_H

#include <sys/ioctl.h>
#include <sys/types.h>

#include <IOKit/storage/IODVDTypes.h>

/*
 * Definitions
 *
 * ioctl                        description
 * ---------------------------- ------------------------------------------------
 * DKIOCDVDREADSTRUCTURE        see IODVDMedia::readStructure()  in IODVDMedia.h
 *
 * DKIOCDVDREADDISCINFO         see IODVDMedia::readDiscInfo()   in IODVDMedia.h
 * DKIOCDVDREADRZONEINFO        see IODVDMedia::readRZoneInfo()  in IODVDMedia.h
 *
 * DKIOCDVDREPORTKEY            see IODVDMedia::reportKey()      in IODVDMedia.h
 * DKIOCDVDSENDKEY              see IODVDMedia::sendKey()        in IODVDMedia.h
 *
 * DKIOCDVDGETSPEED             see IODVDMedia::getSpeed()       in IODVDMedia.h
 * DKIOCDVDSETSPEED             see IODVDMedia::setSpeed()       in IODVDMedia.h
 *
 *         in /System/Library/Frameworks/Kernel.framework/Headers/IOKit/storage/
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

typedef struct
{
    u_int8_t  reserved0000[10];                    /* reserved, clear to zero */

    u_int16_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_dvd_read_disc_info_t;

typedef struct
{
    u_int8_t  reserved0000[4];                     /* reserved, clear to zero */

    u_int32_t address;
    u_int8_t  addressType;

    u_int8_t  reserved0072[1];                     /* reserved, clear to zero */

    u_int16_t bufferLength;                        /* actual length on return */
    void *    buffer;
} dk_dvd_read_rzone_info_t;

#define DKIOCDVDREADSTRUCTURE _IOW('d', 128, dk_dvd_read_structure_t)
#define DKIOCDVDREPORTKEY     _IOW('d', 129, dk_dvd_report_key_t)
#define DKIOCDVDSENDKEY       _IOW('d', 130, dk_dvd_send_key_t)

#define DKIOCDVDGETSPEED      _IOR('d', 131, u_int16_t)
#define DKIOCDVDSETSPEED      _IOW('d', 131, u_int16_t)

#define DKIOCDVDREADDISCINFO  _IOWR('d', 132, dk_dvd_read_disc_info_t)
#define DKIOCDVDREADRZONEINFO _IOWR('d', 133, dk_dvd_read_rzone_info_t)

#endif /* !_IODVDMEDIABSDCLIENT_H */
