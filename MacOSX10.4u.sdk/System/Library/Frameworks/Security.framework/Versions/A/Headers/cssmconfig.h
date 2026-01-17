/*
 * Copyright (c) 2000-2001,2003-2004 Apple Computer, Inc. All Rights Reserved.
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
 *
 * cssmconfig.h -- Platform specific defines and typedefs for cdsa.
 */

#ifndef _CSSMCONFIG_H_
#define _CSSMCONFIG_H_  1

#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/ConditionalMacros.h>

/* #if defined(TARGET_API_MAC_OS8) || defined(TARGET_API_MAC_CARBON) || defined(TARGET_API_MAC_OSX) */
#if defined(TARGET_OS_MAC)
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#else
#error Unknown API architecture.
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef SInt64 sint64;
typedef UInt64 uint64;
typedef SInt32 sint32;
typedef SInt16 sint16;
typedef SInt8 sint8;
typedef UInt32 uint32;
typedef UInt16 uint16;
typedef UInt8 uint8;

#define CSSMACI
#define CSSMAPI
#define CSSMCLI
#define CSSMCSPI
#define CSSMDLI
#define CSSMKRI
#define CSSMSPI
#define CSSMTPI

#ifdef __cplusplus
}
#endif

#endif /* _CSSMCONFIG_H_ */
