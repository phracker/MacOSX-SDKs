/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
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

#import <DriverKit/DriverKit.h>

//! Project version number for HIDDriverKit.
extern double HIDDriverKitVersionNumber;

//! Project version string for HIDDriverKit.
extern const unsigned char HIDDriverKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <HIDDriverKit/PublicHeader.h>

#include <HIDDriverKit/IOHIDDeviceTypes.h>
#include <HIDDriverKit/IOHIDDeviceKeys.h>
#include <HIDDriverKit/IOHIDEventServiceTypes.h>
#include <HIDDriverKit/IOHIDEventServiceKeys.h>
#include <HIDDriverKit/IOHIDUsageTables.h>
#include <HIDDriverKit/IOHIDDevice.h>
#include <HIDDriverKit/IOHIDInterface.h>
#include <HIDDriverKit/IOHIDEventService.h>
#include <HIDDriverKit/IOUserHIDDevice.h>
#include <HIDDriverKit/IOUserHIDEventService.h>
#include <HIDDriverKit/IOUserHIDEventDriver.h>
#include <HIDDriverKit/IOUserUSBHostHIDDevice.h>
#include <HIDDriverKit/IOHIDElement.h>
#include <HIDDriverKit/IOHIDDigitizerCollection.h>
#include <HIDDriverKit/IOHIDDigitizerStructs.h>
