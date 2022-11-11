/*
 * Copyright (c) 1998-2019 Apple Inc. All rights reserved.
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
/*
 * 24 Nov  1998 suurballe  Created.
 */
#ifndef _IORTCCONTROLLER_H
#define _IORTCCONTROLLER_H

#include <IOKit/IOService.h>

typedef void (*RTC_tick_handler)( IOService * );


class IORTCController : public IOService
{
	OSDeclareAbstractStructors(IORTCController);

public:

	virtual IOReturn getRealTimeClock( UInt8 * currentTime, IOByteCount * length ) = 0;
	virtual IOReturn setRealTimeClock( UInt8 * newTime ) = 0;
};

class IORTC : public IOService
{
	OSDeclareAbstractStructors(IORTC);

protected:

/*! @var reserved
 *   Reserved for future use.  (Internal use only)  */
	struct ExpansionData { };
	ExpansionData *iortc_reserved __unused;

public:

	virtual long            getGMTTimeOfDay( void ) = 0;
	virtual void            setGMTTimeOfDay( long secs ) = 0;

	virtual void                    getUTCTimeOfDay( clock_sec_t * secs, clock_nsec_t * nsecs );
	virtual void                    setUTCTimeOfDay( clock_sec_t secs, clock_nsec_t nsecs );

	virtual void            setAlarmEnable( IOOptionBits message ) = 0;

	virtual IOReturn        getMonotonicClockOffset( int64_t * usecs );
	virtual IOReturn        setMonotonicClockOffset( int64_t usecs );
	virtual IOReturn        getMonotonicClockAndTimestamp( uint64_t * usecs, uint64_t *mach_absolute_time );


	OSMetaClassDeclareReservedUnused(IORTC, 0);
	OSMetaClassDeclareReservedUnused(IORTC, 1);
	OSMetaClassDeclareReservedUnused(IORTC, 2);
	OSMetaClassDeclareReservedUnused(IORTC, 3);
	OSMetaClassDeclareReservedUnused(IORTC, 4);
	OSMetaClassDeclareReservedUnused(IORTC, 5);
	OSMetaClassDeclareReservedUnused(IORTC, 6);
	OSMetaClassDeclareReservedUnused(IORTC, 7);
};

#endif /* !_IORTCCONTROLLER_H */
