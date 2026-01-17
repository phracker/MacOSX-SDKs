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

