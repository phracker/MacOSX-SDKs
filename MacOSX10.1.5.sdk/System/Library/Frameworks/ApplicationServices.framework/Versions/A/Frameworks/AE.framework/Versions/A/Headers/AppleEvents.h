/*
     File:       AE/AppleEvents.h
 
     Contains:   AppleEvent Package Interfaces.
 
     Version:    AppleEvents-116~3
 
     Copyright:  © 1989-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __APPLEEVENTS__
#define __APPLEEVENTS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

/*
    Note:   The functions and types for the building and parsing AppleEvent  
            messages has moved to AEDataModel.h
*/
#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
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

enum {
                                        /* Keywords for Apple event parameters */
  keyDirectObject               = '----',
  keyErrorNumber                = 'errn',
  keyErrorString                = 'errs',
  keyProcessSerialNumber        = 'psn ', /* Keywords for special handlers */
  keyPreDispatch                = 'phac', /* preHandler accessor call */
  keySelectProc                 = 'selh', /* more selector call */
                                        /* Keyword for recording */
  keyAERecorderCount            = 'recr', /* available only in vers 1.0.1 and greater */
                                        /* Keyword for version information */
  keyAEVersion                  = 'vers' /* available only in vers 1.0.1 and greater */
};

/* Event Class */
enum {
  kCoreEventClass               = 'aevt'
};

/* Event IDÕs */
enum {
  kAEOpenApplication            = 'oapp',
  kAEOpenDocuments              = 'odoc',
  kAEPrintDocuments             = 'pdoc',
  kAEQuitApplication            = 'quit',
  kAEAnswer                     = 'ansr',
  kAEApplicationDied            = 'obit',
  kAEShowPreferences            = 'pref' /* sent by Mac OS X when the user chooses the Preferences item */
};

/* Constants for recording */
enum {
  kAEStartRecording             = 'reca', /* available only in vers 1.0.1 and greater */
  kAEStopRecording              = 'recc', /* available only in vers 1.0.1 and greater */
  kAENotifyStartRecording       = 'rec1', /* available only in vers 1.0.1 and greater */
  kAENotifyStopRecording        = 'rec0', /* available only in vers 1.0.1 and greater */
  kAENotifyRecording            = 'recr' /* available only in vers 1.0.1 and greater */
};





/*
 * AEEventSource is defined as an SInt8 for compatability with pascal.
 * Important note: keyEventSourceAttr is returned by AttributePtr as a typeShortInteger.
 * Be sure to pass at least two bytes of storage to AEGetAttributePtr - the result can be
 * compared directly against the following enums.
 */
typedef SInt8 AEEventSource;
enum {
  kAEUnknownSource              = 0,
  kAEDirectCall                 = 1,
  kAESameProcess                = 2,
  kAELocalProcess               = 3,
  kAERemoteProcess              = 4
};

/**************************************************************************
  These calls are used to set up and modify the event dispatch table.
**************************************************************************/
/*
 *  AEInstallEventHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEInstallEventHandler(
  AEEventClass        theAEEventClass,
  AEEventID           theAEEventID,
  AEEventHandlerUPP   handler,
  long                handlerRefcon,
  Boolean             isSysHandler);


/*
 *  AERemoveEventHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AERemoveEventHandler(
  AEEventClass        theAEEventClass,
  AEEventID           theAEEventID,
  AEEventHandlerUPP   handler,
  Boolean             isSysHandler);


/*
 *  AEGetEventHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetEventHandler(
  AEEventClass         theAEEventClass,
  AEEventID            theAEEventID,
  AEEventHandlerUPP *  handler,
  long *               handlerRefcon,
  Boolean              isSysHandler);




/**************************************************************************
  These calls are used to set up and modify special hooks into the
  AppleEvent manager.
**************************************************************************/
/*
 *  AEInstallSpecialHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEInstallSpecialHandler(
  AEKeyword           functionClass,
  AEEventHandlerUPP   handler,
  Boolean             isSysHandler);


/*
 *  AERemoveSpecialHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AERemoveSpecialHandler(
  AEKeyword           functionClass,
  AEEventHandlerUPP   handler,
  Boolean             isSysHandler);


/*
 *  AEGetSpecialHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEGetSpecialHandler(
  AEKeyword            functionClass,
  AEEventHandlerUPP *  handler,
  Boolean              isSysHandler);



/**************************************************************************
  This call was added in version 1.0.1. If called with the keyword
  keyAERecorderCount ('recr'), the number of recorders that are
  currently active is returned in 'result'
  (available only in vers 1.0.1 and greater).
**************************************************************************/
/*
 *  AEManagerInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AEManagerInfo(
  AEKeyword   keyWord,
  long *      result);







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

#endif /* __APPLEEVENTS__ */

