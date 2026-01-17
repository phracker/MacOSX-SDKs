/*
 * Copyright (c) 1999-2009 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */

#ifndef _IOKIT_IOHIDLIB_H
#define _IOKIT_IOHIDLIB_H

#include <IOKit/hidsystem/IOHIDShared.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

extern kern_return_t
IOHIDCreateSharedMemory( io_connect_t connect,
	unsigned int version );

extern kern_return_t
IOHIDSetEventsEnable( io_connect_t connect,
	boolean_t enable );

extern kern_return_t
IOHIDSetCursorEnable( io_connect_t connect,
	boolean_t enable );

enum {
    // Options for IOHIDPostEvent()
    kIOHIDSetGlobalEventFlags       = 0x00000001,
    kIOHIDSetCursorPosition         = 0x00000002,
    kIOHIDSetRelativeCursorPosition = 0x00000004,
    kIOHIDPostHIDManagerEvent       = 0x00000008
};

extern kern_return_t
IOHIDPostEvent( io_connect_t        connect,
                UInt32              eventType,
                IOGPoint            location,
                const NXEventData * eventData,
                UInt32              eventDataVersion,
                IOOptionBits        eventFlags,
                IOOptionBits        options );

extern kern_return_t
IOHIDSetMouseLocation( io_connect_t connect,
	int x, int y);

extern kern_return_t
IOHIDGetButtonEventNum( io_connect_t connect,
	NXMouseButton button, int * eventNum );

extern kern_return_t
IOHIDSetCursorBounds( io_connect_t connect, const IOGBounds * bounds );

extern kern_return_t
IOHIDGetScrollAcceleration( io_connect_t handle, double * acceleration );

extern kern_return_t
IOHIDSetScrollAcceleration( io_connect_t handle, double acceleration );

extern kern_return_t
IOHIDGetMouseAcceleration( io_connect_t handle, double * acceleration );

extern kern_return_t
IOHIDSetMouseAcceleration( io_connect_t handle, double acceleration );

extern kern_return_t
IOHIDGetMouseButtonMode( io_connect_t handle, int * mode );

extern kern_return_t
IOHIDSetMouseButtonMode( io_connect_t handle, int mode );

extern kern_return_t
IOHIDGetAccelerationWithKey( io_connect_t handle, CFStringRef key, double * acceleration );

extern kern_return_t
IOHIDSetAccelerationWithKey( io_connect_t handle, CFStringRef key, double acceleration );

extern kern_return_t
IOHIDGetParameter( io_connect_t handle, CFStringRef key, IOByteCount maxSize, 
		void * bytes, IOByteCount * actualSize );

extern kern_return_t
IOHIDSetParameter( io_connect_t handle, CFStringRef key, 
		const void * bytes, IOByteCount size );

extern kern_return_t
IOHIDCopyCFTypeParameter( io_connect_t handle, CFStringRef key,
                CFTypeRef * parameter );

extern kern_return_t
IOHIDSetCFTypeParameter( io_connect_t handle, CFStringRef key,
                CFTypeRef parameter );

// selectors are found in IOHIDParameter.h
extern kern_return_t
IOHIDGetModifierLockState( io_connect_t handle, int selector, bool *state );

extern kern_return_t
IOHIDSetModifierLockState( io_connect_t handle, int selector, bool state );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

__END_DECLS

#endif /* ! _IOKIT_IOHIDLIB_H */

