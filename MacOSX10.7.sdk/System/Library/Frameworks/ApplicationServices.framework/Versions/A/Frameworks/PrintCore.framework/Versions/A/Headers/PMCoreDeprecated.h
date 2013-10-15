/*
     File:       PrintCore/PMCoreDeprecated.h
 
     Contains:   Deprecated Carbon Printing Manager Interfaces.
 
     Copyright (c) 1998-2006,2008 by Apple Inc. All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMCORE_DEPRECATED__
#define __PMCORE_DEPRECATED__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#include <ColorSync/ColorSyncDeprecated.h>

#ifndef __PMDEFINITIONS__
#include <PrintCore/PMDefinitions.h>
#endif

#ifndef __PMDEFINITIONS__
#include <PrintCore/PMDefinitionsDeprecated.h>
#endif

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  PMFlattenPageFormatToCFData() *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPageFormatCreateDataRepresentation instead.
 *
 *  Summary:
 *    Returns a flattened representation of the page format object in a CFDataRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormatToCFData(
  PMPageFormat   pageFormat,
  CFDataRef *    flatFormat)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMFlattenPageFormatToURL() *** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead use PMPageFormatCreateDataRepresentation and write the resulting data to your destination.
 *
 *  Summary:
 *    Writes a flattened representation of the print settings to the
 *    URL specified by flattenFileURL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormatToURL(
  PMPageFormat   pageFormat,
  CFURLRef       flattenFileURL)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMUnflattenPageFormatWithCFData()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPageFormatCreateWithDataRepresentation instead.
 *
 *  Summary:
 *    Returns a page format object given a CFDataRef to a previously
 *    flattened page format.
 *  
 *  Parameters:
 *    
 *    flattenCFData:
 *      A CFDataRef containing a flattened print settings.
 *    
 *    pageFormat:
 *      On return, a newly created page format object create with the
 *      data contained in 'flattenCFData'. The printing framework will
 *      create the object. The app is responsible for disposing of it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormatWithCFData(
  CFDataRef       flattenCFData,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMUnflattenPageFormatWithURL()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead read the data into a CFData object and use PMPageFormatCreateWithDataRepresentation.
 *
 *  Summary:
 *    Returns a page format object given a CFURLRef referencing a file
 *    containing a previously flattened page format.
 *  
 *  Parameters:
 *    
 *    flattenFileURL:
 *      A CFURLRef referencing a file that contains a flattened page
 *      format.
 *    
 *    pageFormat:
 *      On return, a newly created page format object created from the
 *      flattened page format data specified by 'flattenFileURL'. The
 *      caller is responsible for releasing the page format created.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormatWithURL(
  CFURLRef        flattenFileURL,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMFlattenPrintSettingsToCFData()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsCreateDataRepresentation instead.
 *
 *  Summary:
 *    Returns a flattened print settings object as a CFDataRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettingsToCFData(
  PMPrintSettings   printSettings,
  CFDataRef *       flatSetting)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMFlattenPrintSettingsToURL()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead use PMPrintSettingsCreateDataRepresentation and write the resulting data to your destination.
 *
 *  Summary:
 *    Writes a flattened representation of the print settings to the
 *    URL specified by flattenFileURL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettingsToURL(
  PMPrintSettings   printSettings,
  CFURLRef          flattenFileURL)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMUnflattenPrintSettingsWithCFData()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsCreateWithDataRepresentation instead.
 *
 *  Summary:
 *    Returns a print settings object given a CFDataRef to a previously
 *    flatten print settings.
 *  
 *  Parameters:
 *    
 *    flattenCFData:
 *      A CFDataRef containing a flatten print settings.
 *    
 *    printSettings:
 *      On return, a newly created print settings object create with
 *      the data contained in 'flattenCFData'. The printing framework
 *      will create the object. The app is responsible for disposing of
 *      it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettingsWithCFData(
  CFDataRef          flattenCFData,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMUnflattenPrintSettingsWithURL()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead read the data into a CFData object and use PMPrintSettingsCreateWithDataRepresentation.
 *
 *  Summary:
 *    Returns a print settings object given a CFURLRef referencing a
 *    file containing a previously flattened print settings.
 *  
 *  Parameters:
 *    
 *    flattenFileURL:
 *      A CFURLRef referencing a file that contains a flattened print
 *      settings.
 *    
 *    printSettings:
 *      On return, a newly created print settings object created with
 *      the data specified by 'flattenFileURL'. The caller is
 *      responsible for releasing the print settings created.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettingsWithURL(
  CFURLRef           flattenFileURL,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
  
/*
 *  PMGetPrintSettingsExtendedData()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsGetValue instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrintSettingsExtendedData(
  PMPrintSettings   printSettings,
  OSType            dataID,
  UInt32 *          size,
  void *            extendedData)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;

/*
 *  PMSetPrintSettingsExtendedData()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsSetValue instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPrintSettingsExtendedData(
  PMPrintSettings   printSettings,
  OSType            dataID,
  UInt32            size,
  void *            extendedData)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;

/*
 *  PMPaperGetName()
 *  
 *  Summary:
 *    Returns the name for a given paper.
 *  
 *  Discussion:
 *		Use PMPaperCreateLocalizedName instead
 *
 *  Parameters:
 *    
 *    paper:
 *      Obtain the name for this paper.
 *    
 *    paperName:
 *      If successful noErr is returned and *paperName is set to the
 *      name of the paper. The returned paper name is that appropriate
 *      to display to a user.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework but deprecated in 10.7
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 *  
 *  Compatibility:
 *  	Not appropriate for CUPS filters, drivers, and backends.
 *  
 */
extern OSStatus 
PMPaperGetName(
  PMPaper        paper,
  CFStringRef *  paperName)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

/*
 *  PMPrinterCreatePaperInfoListForMenu()
 *  
 *  Summary:
 *    Hand back a list of paper info items that can be used to create a
 *    paper size menu. Each item is a dictionary describing the menu item.
 *  
 *  Parameters:
 *    
 *    printer:
 *      The printer whose page size list should be enumerated. To get
 *      the session's current printer, see PMSessionGetCurrentPrinter().
 *    
 *    pageFormat:
 *      The page format object that contains the current paper size. 
 *    
 *    paperInfoList:
 *      If this function is successful then noErr will be returned and
 *      *'paperInfoList' will be set to a newly created CFArray. Each
 *      element in the array will be a CFDictionary describing the
 *      menu item that needs to be added for the paper size menu. If this
 *      function fails then a non-zero error code will be returned and
 *      *'paperInfoList' will be set to NULL.
 *
 */
extern OSStatus PMPrinterCreatePaperInfoListForMenu(
  PMPrinter printer,
  PMPageFormat pageFormat,
  CFArrayRef *paperInfoList) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_7;

#if !__LP64__

#ifndef PM_USE_SESSION_APIS
#define PM_USE_SESSION_APIS 1
#endif  /* !defined(PM_USE_SESSION_APIS) */

/*
 * SPECIAL AVAILABILITY note: This routine is available in ApplicationsServices.framework in
 * Mac OS X version 10.0 and later. On Mac OS X it is available to CFM applications through CarbonLib
 * starting with Mac OS X version 10.2 and later.
 *
 * On Mac OS 8/9 using CarbonLib, this routine returns kPMNotImplemented
 */

/*
 *  PMSetProfile()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect. Use Quartz drawing instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetProfile(
  PMPrintSettings            printSettings,
  PMTag                      tag,
  const CMProfileLocation *  profile)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* Callbacks */
/*****************************************/
/*  All Idle UPP routines are deprecated */
/*****************************************/
typedef CALLBACK_API( void , PMIdleProcPtr )(void);
typedef STACK_UPP_TYPE(PMIdleProcPtr)                           PMIdleUPP;

#if __MACH__
    #define NewPMIdleUPP(userRoutine)                           ((PMIdleUPP)userRoutine)
    #define DisposePMIdleUPP(userUPP)
    #define InvokePMIdleUPP(userUPP)                            (*userUPP)()
#else

/*
 *  NewPMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMIdleUPP
NewPMIdleUPP(PMIdleProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMIdleUPP(PMIdleUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMIdleUPP(PMIdleUPP userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#endif

#if PM_USE_SESSION_APIS

/*
 *      @function PMSessionBeginDocumentNoDialog
 *      @discussion Use PMSessionBeginCGDocumentNoDialog instead.
 */
/*
 *  PMSessionBeginDocumentNoDialog()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginDocumentNoDialog(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMSessionGetGraphicsContext()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionGetCGGraphicsContext instead.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      the session
 *    
 *    graphicsContextType:
 *      either kPMGraphicsContextQuickdraw or
 *      kPMGraphicsContextCoreGraphics
 *    
 *    graphicsContext:
 *      returns a GrafPtr or a CGContextRef
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetGraphicsContext(
  PMPrintSession   printSession,
  CFStringRef      graphicsContextType,
  void **          graphicsContext)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMSessionEnableColorSync()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect. Use Quartz drawing instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEnableColorSync(PMPrintSession printSession)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMSessionDisableColorSync()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect. Use Quartz drawing instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisableColorSync(PMPrintSession printSession)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMSessionSetIdleProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetIdleProc(
  PMPrintSession   printSession,
  PMIdleUPP        idleProc)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionGeneral()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetCommInfo instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGeneral(
  PMPrintSession   printSession,
  Ptr              pData)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionConvertOldPrintRecord()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionConvertOldPrintRecord(
  PMPrintSession     printSession,
  Handle             printRecordHandle,
  PMPrintSettings *  printSettings,
  PMPageFormat *     pageFormat)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionMakeOldPrintRecord()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionMakeOldPrintRecord(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  Handle *          printRecordHandle)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionSetCurrentPrinter()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionSetCurrentPMPrinter after creating a PMPrinter with
 *    PMPrinterCreateFromPrinterID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetCurrentPrinter(
  PMPrintSession   session,
  CFStringRef      printerName)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPostScriptBegin()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptBegin(PMPrintSession printSession)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPostScriptEnd()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptEnd(PMPrintSession printSession)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPostScriptHandle()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptHandle(
  PMPrintSession   printSession,
  Handle           psHandle)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPostScriptData()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptData(
  PMPrintSession   printSession,
  Ptr              psPtr,
  Size             len)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionPostScriptFile()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptFile(
  PMPrintSession   printSession,
  FSSpec *         psFile)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionSetPSInjectionData()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetPSInjectionData(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFArrayRef        injectionDictArray)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionGetDocumentFormatSupported()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDocumentFormatSupported(
  PMPrintSession   printSession,
  CFArrayRef *     docFormats,
  UInt32           limit)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionGetDocumentFormatGeneration()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDocumentFormatGeneration(
  PMPrintSession   printSession,
  CFArrayRef *     docFormats)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionSetDocumentFormatGeneration()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Carbon applications using CoreGraphics instead of QuickDraw for
 *    all their drawing should use PMSessionBeginCGDocument or
 *    PMSessionBeginCGDocumentNoDialog. For generating PostScript data
 *    you should be using: PMPrinterPrintWithFile or
 *    PMPrinterPrintWithProvider. For mixing EPS data with Quartz drawing
 *    use PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetDocumentFormatGeneration(
  PMPrintSession   printSession,
  CFStringRef      docFormat,
  CFArrayRef       graphicsContextTypes,
  CFTypeRef        options)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSessionIsDocumentFormatSupported()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionIsDocumentFormatSupported(
  PMPrintSession   printSession,
  CFStringRef      docFormat,
  Boolean *        supported)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#else	/* PM_USE_SESSION_APIS */

/*
 *  PMSetIdleProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetIdleProc(PMIdleUPP idleProc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Print loop */
/*
 *  PMBegin()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMCreateSession instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBegin(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMEnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnd(void)                                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetGrafPtr()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionGetCGGraphicsContext instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetGrafPtr(
  PMPrintContext   printContext,
  GrafPtr *        grafPort)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* PMPageFormat */
/*
 *  PMNewPageFormat()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMCreatePageFormat instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMNewPageFormat(PMPageFormat * pageFormat)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDisposePageFormat()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMRelease instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePageFormat(PMPageFormat pageFormat)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDefaultPageFormat()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionDefaultPageFormat instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPageFormat(PMPageFormat pageFormat)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMValidatePageFormat()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionValidatePageFormat instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMValidatePageFormat(
  PMPageFormat   pageFormat,
  Boolean *      result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* PMPrintSettings */
/*
 *  PMNewPrintSettings()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMCreatePrintSettings instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMNewPrintSettings(PMPrintSettings * printSettings)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDisposePrintSettings()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMRelease instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePrintSettings(PMPrintSettings printSettings)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDefaultPrintSettings()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionDefaultPrintSettings instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPrintSettings(PMPrintSettings printSettings)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMValidatePrintSettings()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionValidatePrintSettings instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMValidatePrintSettings(
  PMPrintSettings   printSettings,
  Boolean *         result)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Mac OS 9 Support */
/*
 *  PMGeneral()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGeneral(Ptr pData)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMConvertOldPrintRecord()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMConvertOldPrintRecord(
  Handle             printRecordHandle,
  PMPrintSettings *  printSettings,
  PMPageFormat *     pageFormat)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMMakeOldPrintRecord()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMMakeOldPrintRecord(
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  Handle *          printRecordHandle)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Driver Information */
/*
 *  PMIsPostScriptDriver()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterIsPostScriptCapable or PMPrinterIsPostScriptPrinter instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMIsPostScriptDriver(Boolean * isPostScript)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetLanguageInfo()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetLanguageInfo instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetLanguageInfo(PMLanguageInfo * info)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetDriverCreator()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetDriverCreator instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverCreator(OSType * creator)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetDriverReleaseInfo()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetDriverReleaseInfo instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverReleaseInfo(VersRec * release)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetPrinterResolutionCount()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetPrinterResolutionCount instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrinterResolutionCount(UInt32 * count)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetPrinterResolution()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetPrinterResolution instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrinterResolution(
  PMTag           tag,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetIndexedPrinterResolution()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetIndexedPrinterResolution instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetIndexedPrinterResolution(
  UInt32          index,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* ColorSync & PostScript Support */
/*
 *  PMEnableColorSync()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use Quartz drawing instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnableColorSync(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDisableColorSync()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use Quartz drawing instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisableColorSync(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPostScriptBegin()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptBegin(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPostScriptEnd()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptEnd(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPostScriptHandle()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptHandle(Handle psHandle)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPostScriptData()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptData(
  Ptr    psPtr,
  Size   len)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPostScriptFile()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterPrintWithFile or PMPrinterPrintWithProvider instead.
 *
 *    For using EPS data together with other application drawing
 *    using Quartz, see PMCGImageCreateWithEPSDataProvider.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptFile(FSSpec * psFile)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Error */
/*
 *  PMError()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionError instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMError(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetError()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionSetError instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetError(OSStatus printError)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#endif /* PM_USE_SESSION_APIS */

/*
 *  PMGetJobName()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsGetJobName instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  PMSetJobName()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsSetJobName instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetPhysicalPaperSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMGetUnadjustedPaperRect instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPhysicalPaperSize(
  PMPageFormat   pageFormat,
  PMRect *       paperSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetAdjustedPageRect() *** DEPRECATED ***
 *  
 *  Discussion:
 *    To set a particular paper size and margins create a PMPaper first then call
 *    PMCreatePageFormatWithPMPaper.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetAdjustedPageRect(
  PMPageFormat    pageFormat,
  const PMRect *  pageRect)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMSetPhysicalPaperSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    To set a particular paper size create a PMPaper first then call
 *    PMCreatePageFormatWithPMPaper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPhysicalPaperSize(
  PMPageFormat    pageFormat,
  const PMRect *  paperSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  PMSetUnadjustedPaperRect()	 *** DEPRECATED ***
 *  
 *  Discussion:
 *    To set a particular paper size create a PMPaper first then call
 *    PMCreatePageFormatWithPMPaper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetUnadjustedPaperRect(
  PMPageFormat    pageFormat,
  const PMRect *  paperRect)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMGetPhysicalPageSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMGetUnadjustedPageRect instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPhysicalPageSize(
  PMPageFormat   pageFormat,
  PMRect *       pageSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetColorMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetColorMode(
  PMPrintSettings   printSettings,
  PMColorMode *     colorMode)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetColorMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetColorMode(
  PMPrintSettings   printSettings,
  PMColorMode       colorMode)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  PMGetDestination()	*** DEPRECATED ***
 *
 *  Discussion:
 *    Use PMSessionGetDestinationType, PMSessionCopyDestinationFormat, and/or PMSessionCopyDestinationLocation instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDestination(
  PMPrintSettings      printSettings,
  PMDestinationType *  destType,
  CFURLRef *           fileURL)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMPrinterGetDescriptionURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterCopyDescriptionURL instead. Please be aware that
 *    PMPrinterGetDescriptionURL will return a copy of the URL which
 *    you'll need to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDescriptionURL(
  PMPrinter     printer,
  CFStringRef   descriptionType,
  CFURLRef *    fileURL)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrinterGetDeviceURI()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterCopyDeviceURI instead. Please be aware that
 *    PMPrinterGetDeviceURI will return a copy of the URI which you'll
 *    need to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDeviceURI(
  PMPrinter   printer,
  CFURLRef *  deviceURI)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  PMGetResolution()	*** DEPRECATED ***
 *  
 *  Summary:
 *    Obtains the current application drawing resolution.
 *  
 *  Discussion:
 *
 *    Use Quartz drawing and call CGContextScaleCTM instead.
 *
 *    This is the drawing resolution of an app. This should not be
 *    confused with the resolution of the printer. You can call
 *    PMGetPrinterResolution to see what resolutions are avaliable for
 *    the current printer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetResolution(
  PMPageFormat    pageFormat,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/*
 *  PMSetResolution()	*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use Quartz drawing and call CGContextScaleCTM instead.
 *
 *    This sets the drawing resolution of an app. This should not be
 *    confused with the resolution of the printer.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetResolution(
  PMPageFormat          pageFormat,
  const PMResolution *  res)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMFlattenPageFormat()    *** DEPRECATED ***
 *  
 *  Summary:
 *    Use PMPageFormatCreateDataRepresentation instead.
 *
 *    Flattens a PMPageFormat object for storage in a user document.
 *  
 *  Discussion:
 *    Flattening a page format should only be necessary if you intend
 *    to preserve the object settings along with a document. A page
 *    format will persist outside of a
 *    PMSessionBeginDocxxx/PMSessionEndDocxxx block. This will allow
 *    you to use any accessors on the object without the need to
 *    flatten and unflatten. Keep in mind accessors make no assumption
 *    on the validity of the value you set. This can only be done thru
 *    PMSessionValidatePageFormat in a
 *    PMSessionBeginDocxxx/PMSessionEndDocxxx block with a valid
 *    session.
 *  
 *  Parameters:
 *    
 *    pageFormat:
 *      A page format object.
 *    
 *    flatFormat:
 *      On return, a handle to a flattened PMPageFormat object. The
 *      handle is allocated by the function. You are responsible for
 *      disposing of the handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormat(
  PMPageFormat   pageFormat,
  Handle *       flatFormat)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMUnflattenPageFormat()    *** DEPRECATED ***
 *  
 *  Summary:
 *    Use PMPageFormatCreateWithDataRepresentation instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormat(
  Handle          flatFormat,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/*
 *  PMFlattenPrintSettings()    *** DEPRECATED ***
 *  
 *  Summary:
 *    Use PMPrintSettingsCreateDataRepresentation instead.
 *
 *    Flattens a PMPrintSettings object for storage in a user document.
 *  
 *  Discussion:
 *    Flattening a print settings should only be necessary if you
 *    intend to preserve the object settings along with a document. A
 *    print settings will persist outside of a
 *    PMSessionBeginDocxxx/PMSessionEndDocxxx block. This allows you to
 *    use any accessors on the object without the need to flatten and
 *    unflatten. Keep in mind the accessors make no assumption on the
 *    validity of the value. This can only be done thru
 *    PMSessionValidatePrintSettings in a
 *    PMSessionBeginDocxxx/PMSessionEndDocxxx block with a valid
 *    session.
 *  
 *  Parameters:
 *    
 *    printSettings:
 *      A print settings object.
 *    
 *    flatSettings:
 *      On return, a handle to a flattened PMPrintSettings object. The
 *      handle is allocated by the function. You are responsible for
 *      disposing of the handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettings(
  PMPrintSettings   printSettings,
  Handle *          flatSettings)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMUnflattenPrintSettings()    *** DEPRECATED ***
 *  
 *  Summary:
 *    Use PMPrintSettingsCreateWithDataRepresentation instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettings(
  Handle             flatSettings,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMGetJobNameCFString()    *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsGetJobName instead.
 *    
 *    Please be aware that PMGetJobNameCFString will return a copy of 
 *    the job name which you'll need to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetJobNameCFString(
  PMPrintSettings   printSettings,
  CFStringRef *     name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMSetJobNameCFString()    *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsSetJobName instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetJobNameCFString(
  PMPrintSettings   printSettings,
  CFStringRef       name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  PMPrinterGetPrinterResolution()    *** DEPRECATED ***
 *
 *  Discussion:
 *    Use PMPrinterGetPrinterResolutionCount and PMPrinterGetIndexedPrinterResolution to examine the available printer resolutions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetPrinterResolution(
  PMPrinter       printer,
  PMTag           tag,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
 *  PMPaperCreate()			*** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterGetPaperList to list the PMPaper instances available for a given printer or use PMPaperCreateCustom
 *    to create a PMPaper that represents a custom paper instance.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperCreate(
  PMPrinter               printer,
  CFStringRef             id,
  CFStringRef             name,
  double                  width,
  double                  height,
  const PMPaperMargins *  margins,
  PMPaper *               paperP)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

#endif  /* !__LP64__ */

#ifdef __cplusplus
}
#endif

#endif /* __PMCORE_DEPRECATED__ */
