#ifndef _OPEN_SOURCE_

/*
 * Copyright (c) 1999-2008 Apple Computer, Inc.  All Rights Reserved.
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

#ifndef _IOKIT_HID_IOHIDEVENTSYSTEMEVENTFILTERPLUGIN_H
#define _IOKIT_HID_IOHIDEVENTSYSTEMEVENTFILTERPLUGIN_H


#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <IOKit/hid/IOHIDSession.h>
#include <IOKit/hid/IOHIDEvent.h>

__BEGIN_DECLS


// 7F1A3AE6-3E3D-470A-BD15-A2DD7E1BB719
#define kIOHIDSessionPlugInTypeID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorSystemDefault, \
0x7F, 0x1A, 0x3A, 0xE6, 0x3E, 0x3D, 0x47, 0x0A, \
0xBD, 0x15, 0xA2, 0xDD, 0x7E, 0x1B, 0xB7, 0x19)


// 1F83FA31-B964-4FD2-81D7-5D14BDAC34C1
#define kIOHIDSessionFilterPlugInInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorSystemDefault, \
0x1F, 0x83, 0xFA, 0x31, 0xB9, 0x64, 0x4F, 0xD2, \
0x81, 0xD7, 0x5D, 0x14, 0xBD, 0xAC, 0x34, 0xC1)


typedef struct IOHIDSessionFilterPlugInInterface {
    IUNKNOWN_C_GUTS;
    
    IOHIDEventRef   (*filter)(
                                    void * self,
                                    IOHIDServiceRef sender,
                                    IOHIDEventRef event);
    
} IOHIDSessionFilterPlugInInterface;


// 2F525554-0193-423D-A50A-AF23E8D9E3DC
#define kIOHIDSessionPlugInInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorSystemDefault, \
0x2F, 0x52, 0x55, 0x54, 0x01, 0x93, 0x42, 0x3D, \
0xA5, 0x0A, 0xAF, 0x23, 0xE8, 0xD9, 0xE3, 0xDC)


typedef struct IOHIDSessionPlugInInterface {
    IUNKNOWN_C_GUTS;
    
    void            (*open)(
                                    void * self,
                                    IOHIDSessionRef session,
                                    IOOptionBits options);

    void            (*close)(
                                    void * self,
                                    IOHIDSessionRef session,
                                    IOOptionBits options);
    
    void            (*registerService)(
                                    void * self,
                                    IOHIDServiceRef service);

    void            (*unregisterService)(
                                    void * self,
                                    IOHIDServiceRef service);    
    
    void            (*scheduleWithRunLoop)(
                                    void *                      self, 
                                    CFRunLoopRef                runLoop, 
                                    CFStringRef                 runLoopMode);

    void            (*unscheduleFromRunLoop)(
                                    void *                      self, 
                                    CFRunLoopRef                runLoop, 
                                    CFStringRef                 runLoopMode);

    
    void            (*setLockState)(
                                    void * self,
                                    Boolean lockState);
    
    void            (*setPropertyForClient)(
                                    void * self,
                                    CFStringRef key,
                                    CFTypeRef property,
                                    CFTypeRef client);
    
    IOHIDEventRef   (*filter)(
                                    void * self,
                                    IOHIDServiceRef sender,
                                    IOHIDEventRef event);
    
} IOHIDSessionPlugInInterface;


__END_DECLS

#endif /* _IOKIT_HID_IOHIDEVENTSYSTEMEVENTFILTERPLUGIN_H */

#endif /* _OPEN_SOURCE_ */

