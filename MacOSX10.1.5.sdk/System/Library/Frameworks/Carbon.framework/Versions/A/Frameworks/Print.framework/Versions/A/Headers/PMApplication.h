/*
     File:       Print/PMApplication.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Version:    Printing-91~3
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMAPPLICATION__
#define __PMAPPLICATION__

#ifndef __PMCORE__
#include <PrintCore/PMCore.h>
#endif

#ifndef __DIALOGS__
#include <HIToolbox/Dialogs.h>
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

/* Callbacks */
typedef CALLBACK_API( void , PMItemProcPtr )(DialogRef theDialog, short item);
typedef CALLBACK_API( void , PMPrintDialogInitProcPtr )(PMPrintSettings printSettings, PMDialog *theDialog);
typedef CALLBACK_API( void , PMPageSetupDialogInitProcPtr )(PMPageFormat pageFormat, PMDialog *theDialog);
typedef CALLBACK_API( void , PMSheetDoneProcPtr )(PMPrintSession printSession, WindowRef documentWindow, Boolean accepted);
typedef STACK_UPP_TYPE(PMItemProcPtr)                           PMItemUPP;
typedef STACK_UPP_TYPE(PMPrintDialogInitProcPtr)                PMPrintDialogInitUPP;
typedef STACK_UPP_TYPE(PMPageSetupDialogInitProcPtr)            PMPageSetupDialogInitUPP;
typedef STACK_UPP_TYPE(PMSheetDoneProcPtr)                      PMSheetDoneUPP;
/*
 *  NewPMItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMItemUPP
NewPMItemUPP(PMItemProcPtr userRoutine);

/*
 *  NewPMPrintDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMPrintDialogInitUPP
NewPMPrintDialogInitUPP(PMPrintDialogInitProcPtr userRoutine);

/*
 *  NewPMPageSetupDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMPageSetupDialogInitUPP
NewPMPageSetupDialogInitUPP(PMPageSetupDialogInitProcPtr userRoutine);

/*
 *  NewPMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern PMSheetDoneUPP
NewPMSheetDoneUPP(PMSheetDoneProcPtr userRoutine);

/*
 *  DisposePMItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMItemUPP(PMItemUPP userUPP);

/*
 *  DisposePMPrintDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMPrintDialogInitUPP(PMPrintDialogInitUPP userUPP);

/*
 *  DisposePMPageSetupDialogInitUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMPageSetupDialogInitUPP(PMPageSetupDialogInitUPP userUPP);

/*
 *  DisposePMSheetDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMSheetDoneUPP(PMSheetDoneUPP userUPP);

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
  PMItemUPP  userUPP);

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
  PMPrintDialogInitUPP  userUPP);

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
  PMPageSetupDialogInitUPP  userUPP);

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
  PMSheetDoneUPP  userUPP);

#if PM_USE_SESSION_APIS
/* Print loop */
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
  PMPageFormat      pageFormat);


/*
 *  PMSessionEndDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndDocument(PMPrintSession printSession);


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
  const PMRect *   pageFrame);


/*
 *  PMSessionEndPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndPage(PMPrintSession printSession);


/* Session Printing Dialogs */
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
  Boolean *        accepted);


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
  Boolean *         accepted);


/*
 *  PMSessionPageSetupDialogInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialogInit(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  PMDialog *       newDialog);


/*
 *  PMSessionPrintDialogInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPrintDialogInit(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  PMDialog *        newDialog);


/*
 *  PMSessionPrintDialogMain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPrintDialogMain(
  PMPrintSession         printSession,
  PMPrintSettings        printSettings,
  PMPageFormat           constPageFormat,
  Boolean *              accepted,
  PMPrintDialogInitUPP   myInitProc);


/*
 *  PMSessionPageSetupDialogMain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPageSetupDialogMain(
  PMPrintSession             printSession,
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc);


/************************/
/*  Sheets are not available on classic. */
/************************/
/*
 *  PMSessionUseSheets()
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
  PMSheetDoneUPP   sheetDoneProc);


#else
/* Print loop */
/*
 *  PMBeginDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBeginDocument(
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  PMPrintContext *  printContext);


/*
 *  PMEndDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEndDocument(PMPrintContext printContext);


/*
 *  PMBeginPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBeginPage(
  PMPrintContext   printContext,
  const PMRect *   pageFrame);


/*
 *  PMEndPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEndPage(PMPrintContext printContext);


/* Printing Dialogs */
/*
 *  PMPageSetupDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialog(
  PMPageFormat   pageFormat,
  Boolean *      accepted);


/*
 *  PMPrintDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialog(
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  Boolean *         accepted);


/*
 *  PMPageSetupDialogInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialogInit(
  PMPageFormat   pageFormat,
  PMDialog *     newDialog);


/************************/
/*  PMPrintDialogInit is not recommended. You should instead use */
/*  PMPrintDialogInitWithPageFormat or PMSessionPrintDialogInit */
/************************/
/*
 *  PMPrintDialogInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogInit(
  PMPrintSettings   printSettings,
  PMDialog *        newDialog);


/*
 *  PMPrintDialogInitWithPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogInitWithPageFormat(
  PMPrintSettings   printSettings,
  PMPageFormat      constPageFormat,
  PMDialog *        newDialog);


/*
 *  PMPrintDialogMain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintDialogMain(
  PMPrintSettings        printSettings,
  PMPageFormat           constPageFormat,
  Boolean *              accepted,
  PMPrintDialogInitUPP   myInitProc);


/*
 *  PMPageSetupDialogMain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPageSetupDialogMain(
  PMPageFormat               pageFormat,
  Boolean *                  accepted,
  PMPageSetupDialogInitUPP   myInitProc);


#endif  /* PM_USE_SESSION_APIS */

/* Printing Dialog accessors */
/*
 *  PMGetDialogPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogPtr(
  PMDialog     pmDialog,
  DialogRef *  theDialog);


#define PMGetDialogRef PMGetDialogPtr
/*
 *  PMGetModalFilterProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetModalFilterProc(
  PMDialog          pmDialog,
  ModalFilterUPP *  filterProc);


/*
 *  PMSetModalFilterProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetModalFilterProc(
  PMDialog         pmDialog,
  ModalFilterUPP   filterProc);


/*
 *  PMGetItemProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetItemProc(
  PMDialog     pmDialog,
  PMItemUPP *  itemProc);


/*
 *  PMSetItemProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetItemProc(
  PMDialog    pmDialog,
  PMItemUPP   itemProc);


/*
 *  PMGetDialogAccepted()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogAccepted(
  PMDialog   pmDialog,
  Boolean *  process);


/*
 *  PMSetDialogAccepted()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetDialogAccepted(
  PMDialog   pmDialog,
  Boolean    process);


/*
 *  PMGetDialogDone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDialogDone(
  PMDialog   pmDialog,
  Boolean *  done);


/*
 *  PMSetDialogDone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetDialogDone(
  PMDialog   pmDialog,
  Boolean    done);



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

#endif /* __PMAPPLICATION__ */

