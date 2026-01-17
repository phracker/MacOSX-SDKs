/*
     File:       PrintCore/PMCore.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Version:    PrintingCore-102.1~1
 
     Copyright:  © 1998-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMCORE__
#define __PMCORE__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif

#ifndef __PMDEFINITIONS__
#include <PrintCore/PMDefinitions.h>
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
typedef CALLBACK_API( void , PMIdleProcPtr )(void);
typedef STACK_UPP_TYPE(PMIdleProcPtr)                           PMIdleUPP;
/*
 *  NewPMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern PMIdleUPP
NewPMIdleUPP(PMIdleProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMIdleUPP(PMIdleUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMIdleUPP(PMIdleUPP userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if PM_USE_SESSION_APIS
/* Session routines */
/* Session support */
/*
 *  PMRetain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMRetain(PMObject object)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMRelease(PMObject object)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session Print loop */
/************************/
/* A session is created with a refcount of 1. */
/************************/
/*
 *  PMCreateSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreateSession(PMPrintSession * printSession)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session PMPageFormat */
/************************/
/* A pageformat is created with a refcount of 1. */
/************************/
/*
 *  PMCreatePageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreatePageFormat(PMPageFormat * pageFormat)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionDefaultPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDefaultPageFormat(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionValidatePageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionValidatePageFormat(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  Boolean *        result)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session PMPrintSettings */
/************************/
/* A printSettings is created with a refcount of 1. */
/************************/
/*
 *  PMCreatePrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreatePrintSettings(PMPrintSettings * printSettings)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionDefaultPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDefaultPrintSettings(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionValidatePrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionValidatePrintSettings(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  Boolean *         result)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session Classic support */
/*
 *  PMSessionGeneral()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGeneral(
  PMPrintSession   printSession,
  Ptr              pData)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionConvertOldPrintRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionConvertOldPrintRecord(
  PMPrintSession     printSession,
  Handle             printRecordHandle,
  PMPrintSettings *  printSettings,
  PMPageFormat *     pageFormat)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionMakeOldPrintRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionMakeOldPrintRecord(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  Handle *          printRecordHandle)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session Driver Information */
/*
 *  PMPrinterGetDescriptionURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDescriptionURL(
  PMPrinter     printer,
  CFStringRef   descriptionType,
  CFURLRef *    fileURL)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionGetCurrentPrinter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetCurrentPrinter(
  PMPrintSession   printSession,
  PMPrinter *      currentPrinter)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetLanguageInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetLanguageInfo(
  PMPrinter         printer,
  PMLanguageInfo *  info)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetDriverCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDriverCreator(
  PMPrinter   printer,
  OSType *    creator)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetDriverReleaseInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDriverReleaseInfo(
  PMPrinter   printer,
  VersRec *   release)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetPrinterResolutionCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetPrinterResolutionCount(
  PMPrinter   printer,
  UInt32 *    count)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetPrinterResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetPrinterResolution(
  PMPrinter       printer,
  PMTag           tag,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterGetIndexedPrinterResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetIndexedPrinterResolution(
  PMPrinter       printer,
  UInt32          index,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPrinterIsPostScriptCapable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
PMPrinterIsPostScriptCapable(PMPrinter printer)               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetMakeAndModelName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetMakeAndModelName(
  PMPrinter      printer,
  CFStringRef *  makeAndModel)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Session ColorSync & PostScript Support */
/*
 *  PMSessionEnableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEnableColorSync(PMPrintSession printSession)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionDisableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisableColorSync(PMPrintSession printSession)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPostScriptBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptBegin(PMPrintSession printSession)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPostScriptEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptEnd(PMPrintSession printSession)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPostScriptHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptHandle(
  PMPrintSession   printSession,
  Handle           psHandle)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPostScriptData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptData(
  PMPrintSession   printSession,
  Ptr              psPtr,
  Size             len)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionPostScriptFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptFile(
  PMPrintSession   printSession,
  FSSpec *         psFile)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionSetPSInjectionData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetPSInjectionData(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFArrayRef        injectionDictArray)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Session Error */
/*
 *  PMSessionError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionError(PMPrintSession printSession)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionSetError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetError(
  PMPrintSession   printSession,
  OSStatus         printError)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Other Session routines */
/*
 *  PMSessionGetDocumentFormatGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDocumentFormatGeneration(
  PMPrintSession   printSession,
  CFArrayRef *     docFormats)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionSetDocumentFormatGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetDocumentFormatGeneration(
  PMPrintSession   printSession,
  CFStringRef      docFormat,
  CFArrayRef       graphicsContextTypes,
  CFTypeRef        options)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionGetDocumentFormatSupported()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDocumentFormatSupported(
  PMPrintSession   printSession,
  CFArrayRef *     docFormats,
  UInt32           limit)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionIsDocumentFormatSupported()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionIsDocumentFormatSupported(
  PMPrintSession   printSession,
  CFStringRef      docFormat,
  Boolean *        supported)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionGetGraphicsContext()
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetGraphicsContext(
  PMPrintSession   printSession,
  CFStringRef      graphicsContextType,
  void **          graphicsContext)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionSetIdleProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetIdleProc(
  PMPrintSession   printSession,
  PMIdleUPP        idleProc)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionSetDataInSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetDataInSession(
  PMPrintSession   printSession,
  CFStringRef      key,
  CFTypeRef        data)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionGetDataFromSession()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDataFromSession(
  PMPrintSession   printSession,
  CFStringRef      key,
  CFTypeRef *      data)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSessionCreatePrinterList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCreatePrinterList(
  PMPrintSession   printSession,
  CFArrayRef *     printerList,
  CFIndex *        currentIndex,
  PMPrinter *      currentPrinter)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionSetCurrentPrinter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetCurrentPrinter(
  PMPrintSession   session,
  CFStringRef      printerName)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionSetDestination()
 *  
 *  Summary:
 *    Alter a print session and print settings so that an associated
 *    print job is sent to the provided destination type in the,
 *    optional, MIME document format.
 *  
 *  Discussion:
 *    This function is most useful when an application would like to
 *    write its print output to disk without requiring user
 *    interaction. The list of MIME types that can be sent to the
 *    provided destination can be obtained from
 *    PMSessionCopyOutputFormatList and one of these passed to this
 *    function.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      The session to be used for a print job. The session holds the
 *      preview setting which can override the destination type in the
 *      print settings.
 *    
 *    printSettings:
 *      The print settings to be used for a print job. The print
 *      settings specify whether a job will be directed toward a
 *      printer or to file. It also holds the requested MIME output
 *      type.
 *    
 *    destType:
 *      The destiation type for a print job associated with the
 *      provided print session and print settings. Fax is currently not
 *      supported, but kPMDestinationPrinter, kPMDestinationFile, and
 *      kPMDestinationPreview can be set.
 *    
 *    destFormat:
 *      The MIME type to be generated for the provided destination
 *      type. This parameter can be NULL in which the default format
 *      for the requested destination type is used. To obtain a list of
 *      valid formats for a given destiation type, use the function
 *      PMSessionCopyOutputFormatList.
 *    
 *    destLocation:
 *      Some destination types support a destination location. The
 *      clearest example is the kPMDestinationFile destination type
 *      which allows a caller to also supply a file URL specifying
 *      where the output file is to be created.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetDestination(
  PMPrintSession      printSession,
  PMPrintSettings     printSettings,
  PMDestinationType   destType,
  CFStringRef         destFormat,
  CFURLRef            destLocation)                           AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionGetDestinationType()
 *  
 *  Summary:
 *    Hand back the destination type that will be used for a print job
 *    with the specified print settings and print session.
 *  
 *  Discussion:
 *    Currently there are four destination types:
 *    kPMDestinationPrinter, kPMDestinationFile, kPMDestinationFax and
 *    kPMDestinationPreview. The first three destination types are
 *    stored in the print settings. The switch for preview is stored in
 *    the print session and, if enabled, overrides the destination in
 *    the print setting. This function is preferred over
 *    PMGetDestination as the latter does not take a print session
 *    parameter and therefore can not indicate whether preview has been
 *    selected as the destination.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      The session to be used for a print job. The session holds the
 *      preview setting which can override the destination type in the
 *      print settings.
 *    
 *    printSettings:
 *      The print settings to be used for a print job. The print
 *      settings specify whether a job will be directed toward a
 *      printer or to file.
 *    
 *    destTypeP:
 *      A pointer to a caller supplied PMDestinationType variable. If
 *      this function succeeds then *'destTypeP' will be filled in with
 *      the destination type for a print job that used the specified
 *      session and print settings. If this function fails, then
 *      *'destType' will be set to kPMDestinationInvalid.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDestinationType(
  PMPrintSession       printSession,
  PMPrintSettings      printSettings,
  PMDestinationType *  destTypeP)                             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionCopyDestinationFormat()
 *  
 *  Summary:
 *    Hand back the destination output MIME type associated with the
 *    provided print session and print settings.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      A currently open print session.
 *    
 *    printSettings:
 *      The print settings that are to be searched.
 *    
 *    destFormatP:
 *      A pointer to a caller allocated CFStringRef variable. If this
 *      routine returns noErr then *'destFormatP' will either be a copy
 *      of a CFStringRef specifying the output format for the print
 *      job, or NULL indicating that the default output format will be
 *      used. If this function return an error, then *'destFormatP'
 *      will be set to NULL.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyDestinationFormat(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFStringRef *     destFormatP)                              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionCopyDestinationLocation()
 *  
 *  Summary:
 *    Hand back the URL destination location given a print session and
 *    print settings.
 *  
 *  Discussion:
 *    Some destination type support a destination location which
 *    further defines where the output from a pritn job should be sent.
 *    The kPMDestinationFile destiation type, for example, will use a
 *    file URL to determine where a new file should be created.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      A currently open print session.
 *    
 *    printSettings:
 *      The print settings that are to be searched.
 *    
 *    destLocationP:
 *      A pointer to a caller allocated CFURLRef variable. If this
 *      routine returns noErr then *'outputFileP' will either be NULL
 *      indicating that the job is using the default destination
 *      location for the current destination type or a copy of a
 *      CFURLRef will be placed in *'destLocationP'. If this function
 *      returns an error then 'destLocationP' will be set to NULL.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyDestinationLocation(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFURLRef *        destLocationP)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  PMSessionCopyOutputFormatList()
 *  
 *  Summary:
 *    Hands back an an array of MIME types describing the possible
 *    output formats for the printer module associated with the current
 *    printer.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      This session's current printer's printer module will be queried
 *      for its supported output MIME types.
 *    
 *    destType:
 *      A print job can have one of several possible destination types.
 *      The list of valid output formats is dependent upon the
 *      destination type. This parameter specifies destination type of
 *      interest when retrieving the output formats list.
 *    
 *    documentFormatP:
 *      A pointer to a caller's CFArrayRef variable. If this routine
 *      completes successfully, then *'documentFormatP' will be set to
 *      a CFArrayRef containing CFStringRefs. Each CFStringRef in the
 *      array is a MIME type specifying a type of output that can be
 *      generated by the printer module associated with the current
 *      printer.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later. On Mac OS 8/9 using CarbonLib, this
 *      routine returns kPMNotImplemented
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyOutputFormatList(
  PMPrintSession      printSession,
  PMDestinationType   destType,
  CFArrayRef *        documentFormatP)                        AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  PMSessionCreatePageFormatList()
 *  
 *  Summary:
 *    Hand back a list of page format instances. Each page format
 *    instance describes a paper size available on the specified
 *    printer.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      A currently open print session.
 *    
 *    printer:
 *      The printer whose page size list should be enumerated. To get
 *      the session's current printer, see PMSessionGetCurrentPrinter().
 *    
 *    pageFormatList:
 *      If this function is successful then noErr will be returned and
 *      *'pageFormatList' will be set to a newly created CFArray. Each
 *      element in the array will be a PMPageFormat describing an
 *      available paper size for the specified printer. If this
 *      function fails then a non-zero error code will be returned and
 *      *'pageFormatList' will be set to NULL.
 *    
 *    SPECIAL_AVAILABILITY_NOTE:
 *      This routine is available in ApplicationsServices.framework in
 *      Mac OS X version 10.1 and later. On Mac OS X it is available to
 *      CFM applications through CarbonLib starting with Mac OS X
 *      version 10.2 and later. On Mac OS 8/9 using CarbonLib, this
 *      routine returns kPMNotImplemented
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCreatePageFormatList(
  PMPrintSession   printSession,
  PMPrinter        printer,
  CFArrayRef *     pageFormatList)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 * SPECIAL AVAILABILITY note: This routine is available in ApplicationsServices.framework in
 * Mac OS X version 10.0 and later. On Mac OS X it is available to CFM applications through CarbonLib
 * starting with Mac OS X version 10.2 and later.
 *
 * On Mac OS 8/9 using CarbonLib, this routine returns kPMNotImplemented
 */
/*
 *  PMSessionBeginDocumentNoDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginDocumentNoDialog(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 * SPECIAL AVAILABILITY note: This routine is available in ApplicationsServices.framework in
 * Mac OS X version 10.0 and later. On Mac OS X it is available to CFM applications through CarbonLib
 * starting with Mac OS X version 10.2 and later.
 *
 * On Mac OS 8/9 using CarbonLib, this routine returns kPMNotImplemented
 */
/*
 *  PMSessionEndDocumentNoDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndDocumentNoDialog(PMPrintSession printSession)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 * SPECIAL AVAILABILITY note: This routine is available in ApplicationsServices.framework in
 * Mac OS X version 10.0 and later. On Mac OS X it is available to CFM applications through CarbonLib
 * starting with Mac OS X version 10.2 and later.
 *
 * On Mac OS 8/9 using CarbonLib, this routine returns kPMNotImplemented
 */
/*
 *  PMSessionBeginPageNoDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginPageNoDialog(
  PMPrintSession   printSession,
  PMPageFormat     pageFormat,
  const PMRect *   pageFrame)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 * SPECIAL AVAILABILITY note: This routine is available in ApplicationsServices.framework in
 * Mac OS X version 10.0 and later. On Mac OS X it is available to CFM applications through CarbonLib
 * starting with Mac OS X version 10.2 and later.
 *
 * On Mac OS 8/9 using CarbonLib, this routine returns kPMNotImplemented
 */
/*
 *  PMSessionEndPageNoDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionEndPageNoDialog(PMPrintSession printSession)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#else
/*
 *  PMSetIdleProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetIdleProc(PMIdleUPP idleProc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Print loop */
/*
 *  PMBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBegin(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnd(void)                                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  Valid only within a PMBeginPage/PMEndPage block. You should retrieve the printing */
/*  port with this call and set it before imaging a page. */
/************************/
/*
 *  PMGetGrafPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetGrafPtr(
  PMPrintContext   printContext,
  GrafPtr *        grafPort)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PMPageFormat */
/*
 *  PMNewPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMNewPageFormat(PMPageFormat * pageFormat)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMDisposePageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePageFormat(PMPageFormat pageFormat)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMDefaultPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPageFormat(PMPageFormat pageFormat)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMValidatePageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMValidatePageFormat(
  PMPageFormat   pageFormat,
  Boolean *      result)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PMPrintSettings */
/*
 *  PMNewPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMNewPrintSettings(PMPrintSettings * printSettings)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMDisposePrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePrintSettings(PMPrintSettings printSettings)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMDefaultPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPrintSettings(PMPrintSettings printSettings)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMValidatePrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMValidatePrintSettings(
  PMPrintSettings   printSettings,
  Boolean *         result)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Classic Support */
/*
 *  PMGeneral()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGeneral(Ptr pData)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMConvertOldPrintRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMConvertOldPrintRecord(
  Handle             printRecordHandle,
  PMPrintSettings *  printSettings,
  PMPageFormat *     pageFormat)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMMakeOldPrintRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMMakeOldPrintRecord(
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat,
  Handle *          printRecordHandle)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Driver Information */
/*
 *  PMIsPostScriptDriver()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMIsPostScriptDriver(Boolean * isPostScript)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetLanguageInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetLanguageInfo(PMLanguageInfo * info)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetDriverCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverCreator(OSType * creator)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetDriverReleaseInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverReleaseInfo(VersRec * release)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetPrinterResolutionCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrinterResolutionCount(UInt32 * count)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetPrinterResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrinterResolution(
  PMTag           tag,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetIndexedPrinterResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetIndexedPrinterResolution(
  UInt32          index,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  PMEnableColorSync and PMDisableColorSync are valid within */
/*  BeginPage/EndPage block */
/************************/
/* ColorSync & PostScript Support */
/*
 *  PMEnableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnableColorSync(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMDisableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisableColorSync(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  The PMPostScriptxxx calls are valid within a */
/*  BeginPage/EndPage block */
/************************/
/*
 *  PMPostScriptBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptBegin(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPostScriptEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptEnd(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  These PMPostScriptxxx calls are valid within a */
/*  PMPostScriptBegin/PMPostScriptEnd block */
/************************/
/*
 *  PMPostScriptHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptHandle(Handle psHandle)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPostScriptData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptData(
  Ptr    psPtr,
  Size   len)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMPostScriptFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptFile(FSSpec * psFile)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Error */
/*
 *  PMError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMError(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetError(OSStatus printError)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* PM_USE_SESSION_APIS */

/* PMPageFormat */
/*
 *  PMCopyPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCopyPageFormat(
  PMPageFormat   formatSrc,
  PMPageFormat   formatDest)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  Flattening a page format should only be necessary if you intend to preserve */
/*  the object settings along with a document. A page format will persist outside of a */
/*  PMBegin/PMEnd block. This will allow you to use any accessors on the object without */
/*  the need to flatten and unflatten. Keep in mind accessors make no assumption */
/*  on the validity of the value you set. This can only be done thru PMValidatePageFormat */
/*  in a PMBegin/PMEnd block or with PMSessionValidatePageFormat with a valid session. */
/*  It is your responsibility for disposing of the handle. */
/************************/
/*
 *  PMFlattenPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormat(
  PMPageFormat   pageFormat,
  Handle *       flatFormat)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMUnflattenPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormat(
  Handle          flatFormat,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PMPageFormat Accessors */
/************************/
/* PMSetxxx calls only saves the value inside the printing object. They make no assumption on the */
/* validity of the value. This should be done using PMValidatePageFormat/PMSessionValidatePageFormat */
/* Any dependant settings are also updated during a validate call. */
/* For example: */
/* PMGetAdjustedPaperRect - returns a rect of a certain size */
/* PMSetScale( aPageFormat, 500.0 )  */
/* PMGetAdjustedPaperRect - returns the SAME rect as the first call  */
/**/
/* PMGetAdjustedPaperRect - returns a rect of a certain size */
/* PMSetScale( aPageFormat, 500.0 ) */
/* PMValidatePageFormat or PMSessionValidatePageFormat */
/* PMGetAdjustedPaperRect - returns a rect thats scaled 500% from the first call */
/************************/
/*
 *  PMGetPageFormatExtendedData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPageFormatExtendedData(
  PMPageFormat   pageFormat,
  OSType         dataID,
  UInt32 *       size,
  void *         extendedData)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetPageFormatExtendedData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPageFormatExtendedData(
  PMPageFormat   pageFormat,
  OSType         dataID,
  UInt32         size,
  void *         extendedData)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  A value of 100.0 means 100% (no scaling). 50.0 means 50% scaling */
/************************/
/*
 *  PMGetScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetScale(
  PMPageFormat   pageFormat,
  double *       scale)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetScale(
  PMPageFormat   pageFormat,
  double         scale)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  This is the drawing resolution of an app. This should not be confused with */
/*  the resolution of the printer. You can call PMGetPrinterResolution to see */
/*  what resolutions are avaliable for the current printer. */
/************************/
/*
 *  PMGetResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetResolution(
  PMPageFormat    pageFormat,
  PMResolution *  res)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetResolution(
  PMPageFormat          pageFormat,
  const PMResolution *  res)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  This is the physical size of the paper without regard to resolution, orientation */
/*  or scaling. It is returned as a 72dpi value. */
/************************/
/*
 *  PMGetPhysicalPaperSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPhysicalPaperSize(
  PMPageFormat   pageFormat,
  PMRect *       paperSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetPhysicalPaperSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPhysicalPaperSize(
  PMPageFormat    pageFormat,
  const PMRect *  paperSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  This is the physical size of the page without regard to resolution, orientation */
/*  or scaling. It is returned as a 72dpi value. */
/************************/
/*
 *  PMGetPhysicalPageSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPhysicalPageSize(
  PMPageFormat   pageFormat,
  PMRect *       pageSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetAdjustedPaperRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetAdjustedPaperRect(
  PMPageFormat   pageFormat,
  PMRect *       paperRect)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetAdjustedPageRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetAdjustedPageRect(
  PMPageFormat   pageFormat,
  PMRect *       pageRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetUnadjustedPaperRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetUnadjustedPaperRect(
  PMPageFormat   pageFormat,
  PMRect *       paperRect)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetUnadjustedPaperRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetUnadjustedPaperRect(
  PMPageFormat    pageFormat,
  const PMRect *  paperRect)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetUnadjustedPageRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetUnadjustedPageRect(
  PMPageFormat   pageFormat,
  PMRect *       pageRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetAdjustedPageRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetAdjustedPageRect(
  PMPageFormat    pageFormat,
  const PMRect *  pageRect)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetOrientation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetOrientation(
  PMPageFormat     pageFormat,
  PMOrientation *  orientation)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetOrientation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetOrientation(
  PMPageFormat    pageFormat,
  PMOrientation   orientation,
  Boolean         lock)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PMPrintSettings */
/*
 *  PMCopyPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCopyPrintSettings(
  PMPrintSettings   settingSrc,
  PMPrintSettings   settingDest)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  Flattening a print settings should only be necessary if you intend to preserve */
/*  the object settings along with a document. A print settings will persist outside of a */
/*  PMBegin/PMEnd block. This allows you to use any accessors on the object without */
/*  the need to flatten and unflatten. Keep in mind the accessors make no assumption */
/*  on the validity of the value. This can only be done thru PMValidatePrintSettings */
/*  in a PMBegin/PMEnd block or with PMSessionValidatePrintSettings with a valid session. */
/*  It is your responsibility for disposing of the handle. */
/************************/
/*
 *  PMFlattenPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettings(
  PMPrintSettings   printSettings,
  Handle *          flatSettings)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMUnflattenPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettings(
  Handle             flatSettings,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PMPrintSettings Accessors */
/*
 *  PMGetPrintSettingsExtendedData()
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
  void *            extendedData)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetPrintSettingsExtendedData()
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
  void *            extendedData)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetDestination()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDestination(
  PMPrintSettings      printSettings,
  PMDestinationType *  destType,
  CFURLRef *           fileURL)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetJobName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetJobName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetCopies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetCopies(
  PMPrintSettings   printSettings,
  UInt32 *          copies)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetCopies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetCopies(
  PMPrintSettings   printSettings,
  UInt32            copies,
  Boolean           lock)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetFirstPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetFirstPage(
  PMPrintSettings   printSettings,
  UInt32 *          first)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetFirstPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetFirstPage(
  PMPrintSettings   printSettings,
  UInt32            first,
  Boolean           lock)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetLastPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetLastPage(
  PMPrintSettings   printSettings,
  UInt32 *          last)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetLastPage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetLastPage(
  PMPrintSettings   printSettings,
  UInt32            last,
  Boolean           lock)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/*  The default page range is from 1-32000. The page range is something that is */
/*  set by the application. It is NOT the first and last page to print. It serves */
/*  as limits for setting the first and last page. You may pass kPMPrintAllPages for */
/*  the maxPage value to specified that all pages are available for printing. */
/************************/
/*
 *  PMGetPageRange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPageRange(
  PMPrintSettings   printSettings,
  UInt32 *          minPage,
  UInt32 *          maxPage)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/************************/
/* The first and last page are immediately clipped to the new range */
/************************/
/*
 *  PMSetPageRange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPageRange(
  PMPrintSettings   printSettings,
  UInt32            minPage,
  UInt32            maxPage)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetProfile(
  PMPrintSettings            printSettings,
  PMTag                      tag,
  const CMProfileLocation *  profile)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetColorMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetColorMode(
  PMPrintSettings   printSettings,
  PMColorMode *     colorMode)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetColorMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetColorMode(
  PMPrintSettings   printSettings,
  PMColorMode       colorMode)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMGetJobNameCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetJobNameCFString(
  PMPrintSettings   printSettings,
  CFStringRef *     name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetJobNameCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetJobNameCFString(
  PMPrintSettings   printSettings,
  CFStringRef       name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMSetCollate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetCollate(
  PMPrintSettings   printSettings,
  Boolean           collate)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMGetCollate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetCollate(
  PMPrintSettings   printSettings,
  Boolean *         collate)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMServerCreatePrinterList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMServerCreatePrinterList(
  PMServer      server,
  CFArrayRef *  printerList)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
PMPrinterGetName(PMPrinter printer)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
PMPrinterGetID(PMPrinter printer)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterIsDefault()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
PMPrinterIsDefault(PMPrinter printer)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
PMPrinterGetLocation(PMPrinter printer)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetState(
  PMPrinter         printer,
  PMPrinterState *  state)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMPrinterGetDeviceURI()
 *  
 *  Summary:
 *    Hand back the URI of the printer's device.
 *  
 *  Discussion:
 *    If defined on OS 9 this function returns kPMNotImplemented.
 *  
 *  Parameters:
 *    
 *    printer:
 *      The printer whose device URI is to be retrieved.
 *    
 *    deviceURI:
 *      On exit, if successful *'deviceURI' will contain a reference to
 *      a CFURL describing the printer's device. The caller is
 *      responsible for releasing this reference. If this call returns
 *      an error, then *'deviceURI' will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDeviceURI(
  PMPrinter   printer,
  CFURLRef *  deviceURI)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  PMPrinterIsFavorite()
 *  
 *  Summary:
 *    Return true if the printer is in the user's favorite printer list.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
PMPrinterIsFavorite(PMPrinter printer)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PMCGImageCreateWithEPSDataProvider()
 *  
 *  Summary:
 *    Create an image reference that references both the PostScript
 *    contents of an EPS file and a preview (proxy) image for that EPS
 *    file.
 *  
 *  Discussion:
 *    For OS X 10.1.0, this function ignores the passed in data
 *    provider. The passed in image reference is retained and then
 *    returned. For 10.1.1 and later, then the data provider is used
 *    and the returned image reference is different than the passed in
 *    image reference, so please be careful with your use of these
 *    references. It is likely that the data will not be read from the
 *    EPS data provider until well after this function returns. The
 *    caller should be careful not to free the underlying EPS data
 *    until the provider's release routine is invoked. Similarly the
 *    preview image's data may be needed long after you think it should
 *    be. Do not free the image data until the image data provider's
 *    release data function has been called. To make sure these data
 *    providers are properly reference counted, release your reference
 *    the EPS data provider and on the EPS image preview when they are
 *    no longer needed by your application. For Mac OS X 10.2 and
 *    later, the contents of the EPS provider at the time of this call
 *    can be dumped to a file if you first do the following, BEFORE
 *    running your application. From the command line in terminal:
 *    defaults write NSGlobalDomain com.apple.print.eps.testProvider
 *    /tmp/dump.eps causes a dump of the EPS data into a file
 *    /tmp/dump.eps.
 *  
 *  Parameters:
 *    
 *    epsDataProvider:
 *      A Core Graphics data provider that can supply the PostScript
 *      contents of the EPS file. Post OS X 10.1, there will be some
 *      checking done on the EPS data provided to the
 *      PMCGImageCreateWithEPSDataProvider() call. It is important that
 *      the EPS data begin with the EPSF required header and bounding
 *      box DSC comments.
 *    
 *    epsPreview:
 *      A Core Graphics image reference to the proxy image for the EPS
 *      file. When the image reference result of this function is
 *      rendered on screen or printed to a printer that can not render
 *      PostScript this proxy image is drawn instead.
 *  
 *  Result:
 *    an image reference capable of rendering either the EPS content or
 *    the proxy image depending upon the capabilities of the targeted
 *    context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern CGImageRef 
PMCGImageCreateWithEPSDataProvider(
  CGDataProviderRef   epsDataProvider,
  CGImageRef          epsPreview)                             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __PMCORE__ */

