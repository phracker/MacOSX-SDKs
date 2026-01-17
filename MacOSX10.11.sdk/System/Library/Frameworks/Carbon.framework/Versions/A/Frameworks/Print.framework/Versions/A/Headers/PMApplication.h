/*
     File:       Print/PMApplication.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Copyright  (c) 1998-2008 Apple Inc. All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMAPPLICATION__
#define __PMAPPLICATION__

#if !__LP64__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __DIALOGS__
#include <HIToolbox/Dialogs.h>
#endif

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark
#pragma mark Callbacks
#pragma mark

/* Callbacks */
typedef CALLBACK_API( void , PMSheetDoneProcPtr )(PMPrintSession printSession, WindowRef documentWindow, Boolean accepted);
typedef STACK_UPP_TYPE(PMSheetDoneProcPtr)                      PMSheetDoneUPP;

#if __MACH__

    #define NewPMSheetDoneUPP(userRoutine)                      ((PMSheetDoneUPP)userRoutine)
    #define DisposePMSheetDoneUPP(userUPP)
    #define InvokePMSheetDoneUPP(printSession, documentWindow, accepted, userUPP) (*userUPP)(printSession, documentWindow, accepted)

#else
/*
 *  NewPMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern PMSheetDoneUPP
NewPMSheetDoneUPP(PMSheetDoneProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposePMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMSheetDoneUPP(PMSheetDoneUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokePMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMSheetDoneUPP(
  PMPrintSession  printSession,
  WindowRef       documentWindow,
  Boolean         accepted,
  PMSheetDoneUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
#endif

#pragma mark
#pragma mark Print Loop
#pragma mark

/* Print loop */
/*
 *  PMSessionBeginCGDocument()
 *  
 *  Summary:
 *    Begin a new print job that uses only drawing to a CoreGraphics
 *    context.
 *  
 *  Discussion:
 *    This is an updated version of the function
 *    PMSessionBeginDocument. The functionality is identical to
 *    PMSessionBeginDocument except that during a print job, the caller
 *    cannot obtain a Quickdraw grafPort for the printing context but
 *    can only obtain a Quartz graphics context (CGContextRef). This
 *    function should be used in conjunction with PMSessionGetCGGraphicsContext.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginCGDocument(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  PMSessionEndDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndDocument(PMPrintSession printSession)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionBeginPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginPage(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  const PMRect *   pageFrame)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionEndPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndPage(PMPrintSession printSession)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#pragma mark
#pragma mark Dialogs
#pragma mark

/*
 *  PMSessionPageSetupDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialog(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  Boolean *        accepted)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPrintDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPrintDialog(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  Boolean *         accepted)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionUseSheets()
 *  
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        in CarbonLib 1.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionUseSheets(
  PMPrintSession   printSession,
  WindowRef        documentWindow,
  PMSheetDoneUPP   sheetDoneProc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  PMShowPageSetupDialogAsSheet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMShowPageSetupDialogAsSheet(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  WindowRef	       documentWindow,
  PMSheetDoneUPP   sheetDoneProc)                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  PMShowPrintDialogWithOptions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMShowPrintDialogWithOptions(
  PMPrintSession	        printSession,
  PMPrintSettings           printSettings,
  PMPageFormat              pageFormat,
  PMPrintDialogOptionFlags  printDialogOptions,
  Boolean *                 accepted)                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  PMShowPrintDialogWithOptionsAsSheet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMShowPrintDialogWithOptionsAsSheet(
  PMPrintSession	        printSession,
  PMPrintSettings           printSettings,
  PMPageFormat              pageFormat,
  PMPrintDialogOptionFlags  printDialogOptions,
  WindowRef	                documentWindow,
  PMSheetDoneUPP            sheetDoneProc)                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#pragma mark
#pragma mark Presets
#pragma mark

/* Presets */
/*
 *  PMSessionEnablePrinterPresets()
 *  
 *  Summary:
 *    Enable the use of printer presets in the print dialog.
 *  
 *  Discussion:
 *    Displaying the print dialog on a session after making this call
 *    will show the presets available for the specified graphics type.
 *  
 *  Parameters:
 *    
 *    session:
 *      The session that will be used to present the print dialog.
 *    
 *    graphicsType:
 *      The printer presets in the dialog should be suitable for
 *      rendering this type of graphic. Currently defined graphics
 *      types are: "Photo"
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEnablePrinterPresets(
  PMPrintSession   session,
  CFStringRef      graphicsType)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  PMSessionDisablePrinterPresets()
 *  
 *  Summary:
 *    Disable the use of printer presets in the print dialog.
 *  
 *  Parameters:
 *    
 *    session:
 *      The session that will be used to present the print dialog.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework  [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisablePrinterPresets(PMPrintSession session)        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif  /* !__LP64__ */

#endif /* __PMAPPLICATION__ */

