/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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
 * HISTORY
 *
 */

#ifndef _IOKIT_IOPOWERSOURCES_H
#define _IOKIT_IOPOWERSOURCES_H

typedef void  (*IOPowerSourceCallbackType)(void *context);

/***
 Returns a blob of Power Source information in an opaque CFTypeRef. Clients should
 not actually look directly at data in the CFTypeRef - they should use the accessor
 functions IOPSCopyPowerSourcesList and IOPSGetPowerSourceDescription, instead.
 Returns NULL if errors were encountered.
 Return: Caller must CFRelease() the return value when done.
***/
CFTypeRef IOPSCopyPowerSourcesInfo(void);

/***
 Arguments - Takes the CFTypeRef returned by IOPSCopyPowerSourcesInfo()
 Returns a CFArray of Power Source handles, each of type CFTypeRef.
 The caller shouldn't look directly at the CFTypeRefs, but should use
 IOPSGetPowerSourceDescription on each member of the CFArrayRef.
 Returns NULL if errors were encountered.
 Return: Caller must CFRelease() the returned CFArrayRef.
***/
CFArrayRef IOPSCopyPowerSourcesList(CFTypeRef);

/***
 Arguments -
 1) The CFTypeRef returned by IOPSCopyPowerSourcesInfo
 2) One of the CFTypeRefs in the CFArray returned by IOPSCopyPowerSourcesList

 Returns a CFDictionary with specific information about the power source.
 See IOPSKeys.h for keys and the meaning of specific fields.
 Return: Caller should NOT CFRelease() the returned CFDictionaryRef
***/
CFDictionaryRef IOPSGetPowerSourceDescription(CFTypeRef, CFTypeRef);

/***
 Returns a CFRunLoopSourceRef that notifies the caller when power source
 information changes.
 Arguments:
    IOPowerSourceCallbackType callback - A function to be called whenever any power source is added, removed, or changes
    void *context - Any user-defined pointer, passed to the IOPowerSource callback.
 Returns NULL if there were any problems.
 Caller must CFRelease() the returned value.
***/
CFRunLoopSourceRef IOPSNotificationCreateRunLoopSource(IOPowerSourceCallbackType, void *);

#endif /* _IOKIT_IOPOWERSOURCES_H */
