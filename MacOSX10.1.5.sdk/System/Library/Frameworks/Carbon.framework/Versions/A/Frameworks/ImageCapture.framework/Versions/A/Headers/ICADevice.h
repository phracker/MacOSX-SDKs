/*
     File:       ImageCapture/ICADevice.h
 
     Contains:   Low level Image Capture device definitions.
 
     Version:    ImageCapture-84.1~4
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ICADEVICE__
#define __ICADEVICE__

#ifndef __ICAAPPLICATION__
#include <ImageCapture/ICAApplication.h>
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

/* 
--------------- Completion Procs --------------- 
*/
/*
   
   NOTE: the parameter for the completion proc (ICDHeader*) has to be casted to the appropriate type
   e.g. (ICD_BuildObjectChildrenPB*), ...
   
*/
typedef struct ICDHeader                ICDHeader;
typedef CALLBACK_API_C( void , ICDCompletion )(ICDHeader * pb);
/* 
--------------- ICDHeader --------------- 
*/
struct ICDHeader {
  OSErr               err;                    /* --> */
  UInt32              refcon;                 /* <-- */
};

/*
--------------- Object parameter blocks ---------------
*/
struct ICD_NewObjectPB {
  ICDHeader           header;

  ICAObject           parentObject;           /* <-- */
  ICAObjectInfo       objectInfo;             /* <-- */

  ICAObject           object;                 /* --> */
};
typedef struct ICD_NewObjectPB          ICD_NewObjectPB;
struct ICD_DisposeObjectPB {
  ICDHeader           header;

  ICAObject           object;                 /* <-- */
};
typedef struct ICD_DisposeObjectPB      ICD_DisposeObjectPB;
/*
--------------- Property parameter blocks ---------------
*/
struct ICD_NewPropertyPB {
  ICDHeader           header;

  ICAObject           object;                 /* <-- */
  ICAPropertyInfo     propertyInfo;           /* <-- */

  ICAProperty         property;               /* --> */
};
typedef struct ICD_NewPropertyPB        ICD_NewPropertyPB;
struct ICD_DisposePropertyPB {
  ICDHeader           header;

  ICAProperty         property;               /* <-- */
};
typedef struct ICD_DisposePropertyPB    ICD_DisposePropertyPB;
/*
   
   NOTE: for all APIs - pass NULL as completion parameter to make a synchronous call 
   
*/

/* 
--------------- Object utilities for device libraries --------------- 
*/
/*
 *  ICDNewObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICDNewObject(
  ICD_NewObjectPB *  pb,
  ICDCompletion      completion);      /* can be NULL */


/*
 *  ICDDisposeObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICDDisposeObject(
  ICD_DisposeObjectPB *  pb,
  ICDCompletion          completion);      /* can be NULL */


/*
 *  ICDNewProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICDNewProperty(
  ICD_NewPropertyPB *  pb,
  ICDCompletion        completion);      /* can be NULL */


/*
 *  ICDDisposeProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ImageCaptureLib 1.0 and later
 */
extern OSErr 
ICDDisposeProperty(
  ICD_DisposePropertyPB *  pb,
  ICDCompletion            completion);      /* can be NULL */







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

#endif /* __ICADEVICE__ */

