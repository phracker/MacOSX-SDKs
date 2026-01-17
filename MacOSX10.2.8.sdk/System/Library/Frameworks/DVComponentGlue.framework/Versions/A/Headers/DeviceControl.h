/*
     File:       DVComponentGlue/DeviceControl.h
 
     Contains:   Component API for doing AVC transactions.
 
     Version:    xxx put version here xxx
 
     DRI:        Jed (George) Wilson
 
     Copyright:  © 1999-2001 by Apple Computer, Inc., all rights reserved.
 
     Warning:    *** APPLE INTERNAL USE ONLY ***
                 This file may contain unreleased API's
 
     BuildInfo:  Built by:            wgulland
                 On:                  Tue Mar 12 16:49:01 2002
                 With Interfacer:     3.0d35   (Mac OS X for PowerPC)
                 From:                DeviceControl.i
                     Revision:        3
                     Dated:           6/16/99
                     Last change by:  GDW
                     Last comment:    Changed AVC struct name to DVC for people that include
 
     Bugs:       Report bugs to Radar component "System Interfaces", "Latest"
                 List the version information (from above) in the Problem Description.
 
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

