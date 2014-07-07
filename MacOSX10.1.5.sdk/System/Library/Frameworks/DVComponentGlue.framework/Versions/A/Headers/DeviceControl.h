/*
     File:       DeviceControl.h
 
     Contains:   Component API for doing AVC transactions.
 
     Version:    xxx put version here xxx
 
     DRI:        Jed (George) Wilson
 
     Copyright:  (c) 1999-2000 by Apple Computer, Inc., all rights reserved.
 
     BuildInfo:  Built by:            wgulland
                 On:                  Thu Sep 21 14:47:22 2000
                 With Interfacer:     3.0d20e4 (Mac OS X for PowerPC)
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

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif

#ifndef __COMPONENTS__
#include <Components.h>
#endif





#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
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
    Ptr                             commandBufferPtr;
    UInt32                          commandLength;
    Ptr                             responseBufferPtr;
    UInt32                          responseBufferSize;
    DCResponseHandler *             responseHandler;
};
typedef struct DVCTransactionParams     DVCTransactionParams;
EXTERN_API( ComponentResult )
DeviceControlDoAVCTransaction   (ComponentInstance      instance,
                                 DVCTransactionParams * params)                             FIVEWORDINLINE(0x2F3C, 0x0004, 0x0001, 0x7000, 0xA82A);



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

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DEVICECONTROL__ */

