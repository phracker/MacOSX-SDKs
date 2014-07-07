/*
     File:       CommonPanels/CMCalibrator.h
 
     Contains:   ColorSync Calibration API
 
     Version:    CommonPanels-51~48
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMCALIBRATOR__
#define __CMCALIBRATOR__

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
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

typedef CALLBACK_API( void , CalibrateEventProcPtr )(EventRecord * event);
typedef STACK_UPP_TYPE(CalibrateEventProcPtr)                   CalibrateEventUPP;

/* Interface for new ColorSync monitor calibrators (ColorSync 2.6 and greater) */

enum {
  kCalibratorNamePrefix         = 'cali'
};

struct CalibratorInfo {
  UInt32              dataSize;               /* Size of this structure - compatibility */
  CMDisplayIDType     displayID;              /* Contains an hDC on Win32 */
  UInt32              profileLocationSize;    /* Max size for returned profile location */
  CMProfileLocation * profileLocationPtr;     /* For returning the profile */
  CalibrateEventUPP   eventProc;              /* Ignored on Win32 */
  Boolean             isGood;                 /* true or false */
};
typedef struct CalibratorInfo           CalibratorInfo;
typedef CALLBACK_API( Boolean , CanCalibrateProcPtr )(CMDisplayIDType displayID, Str255 errMessage);
typedef CALLBACK_API( OSErr , CalibrateProcPtr )(CalibratorInfo * theInfo);
typedef STACK_UPP_TYPE(CanCalibrateProcPtr)                     CanCalibrateUPP;
typedef STACK_UPP_TYPE(CalibrateProcPtr)                        CalibrateUPP;
/*
 *  NewCalibrateEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CalibrateEventUPP
NewCalibrateEventUPP(CalibrateEventProcPtr userRoutine);

/*
 *  NewCanCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CanCalibrateUPP
NewCanCalibrateUPP(CanCalibrateProcPtr userRoutine);

/*
 *  NewCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CalibrateUPP
NewCalibrateUPP(CalibrateProcPtr userRoutine);

/*
 *  DisposeCalibrateEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCalibrateEventUPP(CalibrateEventUPP userUPP);

/*
 *  DisposeCanCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCanCalibrateUPP(CanCalibrateUPP userUPP);

/*
 *  DisposeCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCalibrateUPP(CalibrateUPP userUPP);

/*
 *  InvokeCalibrateEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeCalibrateEventUPP(
  EventRecord *      event,
  CalibrateEventUPP  userUPP);

/*
 *  InvokeCanCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCanCalibrateUPP(
  CMDisplayIDType  displayID,
  Str255           errMessage,
  CanCalibrateUPP  userUPP);

/*
 *  InvokeCalibrateUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCalibrateUPP(
  CalibratorInfo *  theInfo,
  CalibrateUPP      userUPP);

/*
 *  CMCalibrateDisplay()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
CMCalibrateDisplay(CalibratorInfo * theInfo);




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

#endif /* __CMCALIBRATOR__ */

