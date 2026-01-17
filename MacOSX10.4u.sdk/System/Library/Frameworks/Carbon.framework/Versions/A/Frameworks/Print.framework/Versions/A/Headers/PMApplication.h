/*
     File:       Print/PMApplication.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Version:    Printing-192.4~592
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMAPPLICATION__
#define __PMAPPLICATION__

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

#ifndef PM_USE_SESSION_APIS
#define PM_USE_SESSION_APIS 1
#endif  /* !defined(PM_USE_SESSION_APIS) */

/* Callbacks */
typedef CALLBACK_API( void , PMSheetDoneProcPtr )(PMPrintSession printSession, WindowRef documentWindow, Boolean accepted);
/******************************************/
/* The following callbacks are deprecated */
/******************************************/
typedef CALLBACK_API( void , PMItemProcPtr )(DialogRef theDialog, short item);
typedef CALLBACK_API( void , PMPrintDialogInitProcPtr )(PMPrintSettings printSettings, PMDialog *theDialog);
typedef CALLBACK_API( void , PMPageSetupDialogInitProcPtr )(PMPageFormat pageFormat, PMDialog *theDialog);
typedef STACK_UPP_TYPE(PMSheetDoneProcPtr)                      PMSheetDoneUPP;
typedef STACK_UPP_TYPE(PMItemProcPtr)                           PMItemUPP;
typedef STACK_UPP_TYPE(PMPrintDialogInitProcPtr)                PMPrintDialogInitUPP;
typedef STACK_UPP_TYPE(PMPageSetupDialogInitProcPtr)            PMPageSetupDialogInitUPP;
/*
 *  NewPMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern PMSheetDoneUPP
NewPMSheetDoneUPP(PMSheetDoneProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewPMItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMItemUPP
NewPMItemUPP(PMItemProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewPMPrintDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMPrintDialogInitUPP
NewPMPrintDialogInitUPP(PMPrintDialogInitProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewPMPageSetupDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMPageSetupDialogInitUPP
NewPMPageSetupDialogInitUPP(PMPageSetupDialogInitProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposePMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMSheetDoneUPP(PMSheetDoneUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposePMItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMItemUPP(PMItemUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposePMPrintDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMPrintDialogInitUPP(PMPrintDialogInitUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposePMPageSetupDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMPageSetupDialogInitUPP(PMPageSetupDialogInitUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokePMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMSheetDoneUPP(
  PMPrintSession  printSession,
  WindowRef       documentWindow,
  Boolean         accepted,
  PMSheetDoneUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokePMItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMItemUPP(
  DialogRef  theDialog,
  short      item,
  PMItemUPP  userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokePMPrintDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMPrintDialogInitUPP(
  PMPrintSettings       printSettings,
  PMDialog *            theDialog,
  PMPrintDialogInitUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokePMPageSetupDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMPageSetupDialogInitUPP(
  PMPageFormat              pageFormat,
  PMDialog *                theDialog,
  PMPageSetupDialogInitUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if PM_USE_SESSION_APIS
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
 *    function should be used in conjunction with
 *    PMSessionGetCGGraphicsContext instead of
 *    PMSessionGetGraphicsContext.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginCGDocument(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMSessionBeginDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginDocument(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionEndDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndDocument(PMPrintSession printSession)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionBeginPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndPage(PMPrintSession printSession)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPageSetupDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
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
 *  Discussion:
 *    Sheets are not available on classic.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionUseSheets(
  PMPrintSession   printSession,
  WindowRef        documentWindow,
  PMSheetDoneUPP   sheetDoneProc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Presets */
/*
 *  PMSessionEnablePrinterPresets()
 *  
 *  Summary:
 *    Enable the use of printer presets in the print dialog.
 *  
 *  Discussion:
 *    Displaying the print dialog on a session after making this call
 *    will show the presets available for the specified graphis type.
 *    In addition this call will enable the use of the simplified print
 *    dialog. On OS 9 this function returns kPMNotImplemented.
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
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
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
 *  Discussion:
 *    On OS 9 this function returns noErr since presets are never used
 *    in that OS.
 *  
 *  Parameters:
 *    
 *    session:
 *      The session that will be used to present the print dialog.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisablePrinterPresets(PMPrintSession session)        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#endif  /* PM_USE_SESSION_APIS */

#pragma mark -
#pragma mark DEPRECATED
#pragma mark
#if PM_USE_SESSION_APIS
/*
 *  PMSessionPageSetupDialogInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialogInit(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  PMDialog *       newDialog)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPrintDialogInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPrintDialogInit(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  PMDialog *        newDialog)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPrintDialogMain()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPrintDialogMain(
  PMPrintSession         printSession,
  PMPrintSettings        printSettings,
  PMPageFormat           constPageFormat,
  Boolean *              accepted,
  PMPrintDialogInitUPP   myInitProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPageSetupDialogMain()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialogMain(
  PMPrintSession             printSession,
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#else
/* Print loop */
/*
 *  PMBeginDocument()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionBeginDocument instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBeginDocument(
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  PMPrintContext *  printContext)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMEndDocument()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionEndDocument instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEndDocument(PMPrintContext printContext)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMBeginPage()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionBeginPage instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBeginPage(
  PMPrintContext   printContext,
  const PMRect *   pageFrame)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMEndPage()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionEndPage instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEndPage(PMPrintContext printContext)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPageSetupDialog()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionPageSetupDialog instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialog(
  PMPageFormat   pageFormat,
  Boolean *      accepted)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrintDialog()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionPrintDialog instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialog(
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  Boolean *         accepted)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPageSetupDialogInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialogInit(
  PMPageFormat   pageFormat,
  PMDialog *     newDialog)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrintDialogInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogInit(
  PMPrintSettings   printSettings,
  PMDialog *        newDialog)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrintDialogInitWithPageFormat()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogInitWithPageFormat(
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  PMDialog *        newDialog)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrintDialogMain()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogMain(
  PMPrintSettings        printSettings,
  PMPageFormat           constPageFormat,
  Boolean *              accepted,
  PMPrintDialogInitUPP   myInitProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPageSetupDialogMain()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialogMain(
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif  /* PM_USE_SESSION_APIS */

/*
 *  PMGetDialogPtr()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogPtr(
  PMDialog     pmDialog,
  DialogRef *  theDialog)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#define PMGetDialogRef PMGetDialogPtr
/*
 *  PMGetModalFilterProc()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetModalFilterProc(
  PMDialog          pmDialog,
  ModalFilterUPP *  filterProc)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetModalFilterProc()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetModalFilterProc(
  PMDialog         pmDialog,
  ModalFilterUPP   filterProc)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetItemProc()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetItemProc(
  PMDialog     pmDialog,
  PMItemUPP *  itemProc)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetItemProc()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetItemProc(
  PMDialog    pmDialog,
  PMItemUPP   itemProc)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetDialogAccepted()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogAccepted(
  PMDialog   pmDialog,
  Boolean *  process)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetDialogAccepted()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetDialogAccepted(
  PMDialog   pmDialog,
  Boolean    process)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetDialogDone()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogDone(
  PMDialog   pmDialog,
  Boolean *  done)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetDialogDone()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetDialogDone(
  PMDialog   pmDialog,
  Boolean    done)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



#ifdef __cplusplus
}
#endif

#endif /* __PMAPPLICATION__ */

