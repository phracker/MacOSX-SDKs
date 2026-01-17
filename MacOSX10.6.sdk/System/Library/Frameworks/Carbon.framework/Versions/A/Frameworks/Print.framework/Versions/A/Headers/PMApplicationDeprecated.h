/*
     File:       Print/PMApplicationDeprecated.h
 
     Contains:   Deprecated Carbon Printing Manager Interfaces.
 
	 Copyright  (c) 1998-2006, 2008 Apple Inc. All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __PMAPPLICATION_DEPRECATED__
#define __PMAPPLICATION_DEPRECATED__

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

#ifndef PM_USE_SESSION_APIS
#define PM_USE_SESSION_APIS 1
#endif  /* !defined(PM_USE_SESSION_APIS) */

/******************************************/
/* The following callbacks are deprecated */
/******************************************/
typedef CALLBACK_API( void , PMItemProcPtr )(DialogRef theDialog, short item);
typedef CALLBACK_API( void , PMPrintDialogInitProcPtr )(PMPrintSettings printSettings, PMDialog *theDialog);
typedef CALLBACK_API( void , PMPageSetupDialogInitProcPtr )(PMPageFormat pageFormat, PMDialog *theDialog);
typedef STACK_UPP_TYPE(PMItemProcPtr)                           PMItemUPP;
typedef STACK_UPP_TYPE(PMPrintDialogInitProcPtr)                PMPrintDialogInitUPP;
typedef STACK_UPP_TYPE(PMPageSetupDialogInitProcPtr)            PMPageSetupDialogInitUPP;

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

#if __MACH__
    #define NewPMItemUPP(userRoutine)                           ((PMItemUPP)userRoutine)
    #define NewPMPrintDialogInitUPP(userRoutine)                ((PMPrintDialogInitUPP)userRoutine)
    #define NewPMPageSetupDialogInitUPP(userRoutine)            ((PMPageSetupDialogInitUPP)userRoutine)
    #define DisposePMItemUPP(userUPP)
    #define DisposePMPrintDialogInitUPP(userUPP)
    #define DisposePMPageSetupDialogInitUPP(userUPP)
    #define InvokePMItemUPP(theDialog, item, userUPP)           (*userUPP)(theDialog, item)
    #define InvokePMPrintDialogInitUPP(printSettings, theDialog, userUPP) (*userUPP)(printSettings, theDialog)
    #define InvokePMPageSetupDialogInitUPP(pageFormat, theDialog, userUPP) (*userUPP)(pageFormat, theDialog)
#endif

#if PM_USE_SESSION_APIS

/*
 *  PMSessionBeginDocument()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead use PMSessionBeginCGDocument.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginDocument(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMSessionPageSetupDialogInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialogMain(
  PMPrintSession             printSession,
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#else	/* PM_USE_SESSION_APIS */

/*
 *  PMBeginDocument()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionBeginDocument instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialogMain(
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif	/* PM_USE_SESSION_APIS */

/*
 *  PMGetDialogPtr()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    You should create a PDE for your application instead of relying
 *    on this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.4
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

#endif  /* !__LP64__ */

#endif	/* __PMAPPLICATION_DEPRECATED__ */

