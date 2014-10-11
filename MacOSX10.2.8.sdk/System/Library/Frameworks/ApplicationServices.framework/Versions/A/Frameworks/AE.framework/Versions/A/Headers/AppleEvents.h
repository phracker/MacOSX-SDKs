/*
     File:       AE/AppleEvents.h
 
     Contains:   AppleEvent Package Interfaces.
 
     Version:    AppleEvents-242~1
 
     Copyright:  © 1989-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __APPLEEVENTS__
#define __APPLEEVENTS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

/*
    Note:   The functions and types for the building and parsing AppleEvent  
            messages has moved to AEDataModel.h
*/
#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
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
  Boolean             isSysHandler)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean             isSysHandler)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean              isSysHandler)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
  Boolean             isSysHandler)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean             isSysHandler)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean              isSysHandler)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  long *      result)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;







#ifdef __cplusplus
}
#endif

#endif /* __APPLEEVENTS__ */

