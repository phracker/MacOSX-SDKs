/*
 * Copyright (c) 1998-2009 Apple Inc. All Rights Reserved.
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

#ifndef __DISKARBITRATION_DASESSION__
#define __DISKARBITRATION_DASESSION__

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __DISKARBITRATIOND__

/*!
 * @typedef   DASessionRef
 * Type of a reference to DASession instances.
 */

typedef struct __DASession * DASessionRef;

/*!
 * @function   DASessionGetTypeID
 * @abstract   Returns the type identifier of all DASession instances.
 */

extern CFTypeID DASessionGetTypeID( void );

/*!
 * @function   DASessionCreate
 * @abstract   Creates a new session.
 * @result     A reference to a new DASession.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it.
 */

extern DASessionRef DASessionCreate( CFAllocatorRef allocator );

/*!
 * @function   DASessionScheduleWithRunLoop
 * @abstract   Schedules the session on a run loop.
 * @param      session     The session which is being scheduled.
 * @param      runLoop     The run loop on which the session should be scheduled.
 * @param      runLoopMode The run loop mode in which the session should be scheduled.
 */

extern void DASessionScheduleWithRunLoop( DASessionRef session, CFRunLoopRef runLoop, CFStringRef runLoopMode );

/*!
 * @function   DASessionUnscheduleFromRunLoop
 * @abstract   Unschedules the session from a run loop.
 * @param      session     The session which is being unscheduled.
 * @param      runLoop     The run loop on which the session is scheduled.
 * @param      runLoopMode The run loop mode in which the session is scheduled.
 */

extern void DASessionUnscheduleFromRunLoop( DASessionRef session, CFRunLoopRef runLoop, CFStringRef runLoopMode );

/*!
 * @typedef   DAApprovalSessionRef
 * Type of a reference to DAApprovalSession instances.
 */

typedef struct __DASession * DAApprovalSessionRef;

/*!
 * @function   DAApprovalSessionGetTypeID
 * @abstract   Returns the type identifier of all DAApprovalSession instances.
 */

extern CFTypeID DAApprovalSessionGetTypeID( void );

/*!
 * @function   DAApprovalSessionCreate
 * @abstract   Creates a new approval session.
 * @result     A reference to a new DAApprovalSession.
 * @discussion
 * The caller of this function receives a reference to the returned object.  The
 * caller also implicitly retains the object and is responsible for releasing it.
 */

extern DAApprovalSessionRef DAApprovalSessionCreate( CFAllocatorRef allocator );

/*!
 * @function   DAApprovalSessionScheduleWithRunLoop
 * @abstract   Schedules the approval session on a run loop.
 * @param      session     The approval session which is being scheduled.
 * @param      runLoop     The run loop on which the approval session should be scheduled.
 * @param      runLoopMode The run loop mode in which the approval session should be scheduled.
 */

extern void DAApprovalSessionScheduleWithRunLoop( DAApprovalSessionRef session, CFRunLoopRef runLoop, CFStringRef runLoopMode );

/*!
 * @function   DAApprovalSessionUnscheduleFromRunLoop
 * @abstract   Unschedules the approval session from a run loop.
 * @param      session     The approval session which is being unscheduled.
 * @param      runLoop     The run loop on which the approval session is scheduled.
 * @param      runLoopMode The run loop mode in which the approval session is scheduled.
 */

extern void DAApprovalSessionUnscheduleFromRunLoop( DAApprovalSessionRef session, CFRunLoopRef runLoop, CFStringRef runLoopMode );

#endif /* !__DISKARBITRATIOND__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__DISKARBITRATION_DASESSION__ */
