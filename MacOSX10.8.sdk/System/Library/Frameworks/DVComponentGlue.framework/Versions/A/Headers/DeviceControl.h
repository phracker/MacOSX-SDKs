/*
 * Copyright (c) 2009 Apple Inc. All rights reserved.
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
     File:       DVComponentGlue/DeviceControl.h
 
     Contains:   Component API for doing AVC transactions.

     Copyright:  © 1997-2006 by Apple Computer, Inc., all rights reserved.

*/
#ifndef __DEVICECONTROL__
#define __DEVICECONTROL__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

typedef CALLBACK_API_C( UInt32 , DCResponseHandler )(UInt32 fwCommandObjectID, Ptr responseBuffer, UInt32 responseLength);
struct DVCTransactionParams {
  Ptr                 commandBufferPtr;
  UInt32              commandLength;
  Ptr                 responseBufferPtr;
  UInt32              responseBufferSize;
  DCResponseHandler * responseHandler;
};
typedef struct DVCTransactionParams     DVCTransactionParams;
/*
 *  DeviceControlDoAVCTransaction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DVComponentGlue.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in IDHLib 1.0 and later
 */
extern ComponentResult 
DeviceControlDoAVCTransaction(
  ComponentInstance       instance,
  DVCTransactionParams *  params);




/* selectors for component calls */
enum {
    kDeviceControlDoAVCTransactionSelect       = 0x0001
};

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DEVICECONTROL__ */

