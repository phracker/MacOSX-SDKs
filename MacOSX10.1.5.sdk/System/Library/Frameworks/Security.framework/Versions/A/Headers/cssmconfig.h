/*
 * Copyright (c) 2000-2001 Apple Computer, Inc. All Rights Reserved.
 * 
 * The contents of this file constitute Original Code as defined in and are
 * subject to the Apple Public Source License Version 1.2 (the 'License').
 * You may not use this file except in compliance with the License. Please obtain
 * a copy of the License at http://www.apple.com/publicsource and read it before
 * using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for the
 * specific language governing rights and limitations under the License.
 */


/*
   File:      cssmconfig.h

   Contains:  Platform specific defines and typedefs for cdsa.

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
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

#if 0
#define CSSM_EXTERN(_type) EXTERN_API_C(_type)
#define CSSM_DEFINE(_type) DEFINE_API_C(_type)
#define CSSM_CALLBACK(_type, _name) CALLBACK_API_C(_type, _name)
#else
#define CSSMACI
#define CSSMAPI
#define CSSMCLI
#define CSSMCSPI
#define CSSMDLI
#define CSSMKRI
#define CSSMSPI
#define CSSMTPI
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CSSMCONFIG_H_ */
