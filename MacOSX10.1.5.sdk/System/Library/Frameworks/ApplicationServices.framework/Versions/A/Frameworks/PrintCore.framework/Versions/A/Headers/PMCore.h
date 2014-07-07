/*
     File:       PrintCore/PMCore.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Version:    PrintingCore-61~16
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMCORE__
#define __PMCORE__

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
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

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFURL__
#include <CoreFoundation/CFURL.h>
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
NewPMIdleUPP(PMIdleProcPtr userRoutine);

/*
 *  DisposePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposePMIdleUPP(PMIdleUPP userUPP);

/*
 *  InvokePMIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokePMIdleUPP(PMIdleUPP userUPP);

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
PMRetain(PMObject object);


/*
 *  PMRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMRelease(PMObject object);


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
PMCreateSession(PMPrintSession * printSession);


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
PMCreatePageFormat(PMPageFormat * pageFormat);


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
  PMPageFormat     pageFormat);


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
  Boolean *        result);


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
PMCreatePrintSettings(PMPrintSettings * printSettings);


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
  PMPrintSettings   printSettings);


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
  Boolean *         result);


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
  Ptr              pData);


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
  PMPageFormat *     pageFormat);


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
  Handle *          printRecordHandle);


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
  CFURLRef *    fileURL);


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
  PMPrinter *      currentPrinter);


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
  PMLanguageInfo *  info);


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
  OSType *    creator);


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
  VersRec *   release);


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
  UInt32 *    count);


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
  PMResolution *  res);


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
  PMResolution *  res);


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
PMSessionEnableColorSync(PMPrintSession printSession);


/*
 *  PMSessionDisableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisableColorSync(PMPrintSession printSession);


/*
 *  PMSessionPostScriptBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptBegin(PMPrintSession printSession);


/*
 *  PMSessionPostScriptEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionPostScriptEnd(PMPrintSession printSession);


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
  Handle           psHandle);


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
  Size             len);


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
  FSSpec *         psFile);


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
  CFArrayRef        injectionDictArray);


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
PMSessionError(PMPrintSession printSession);


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
  OSStatus         printError);


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
  CFArrayRef *     docFormats);


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
  CFTypeRef        options);


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
  UInt32           limit);


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
  Boolean *        supported);


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
  void **          graphicsContext);


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
  PMIdleUPP        idleProc);


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
  CFTypeRef        data);


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
  CFTypeRef *      data);


/*
 *  PMSessionCreatePrinterList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCreatePrinterList(
  PMPrintSession   printSession,
  CFArrayRef *     printerList,
  CFIndex *        currentIndex,
  PMPrinter *      currentPrinter);


/*
 *  PMSessionSetCurrentPrinter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetCurrentPrinter(
  PMPrintSession   session,
  CFStringRef      printerName);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetDestination(
  PMPrintSession      printSession,
  PMPrintSettings     printSettings,
  PMDestinationType   destType,
  CFStringRef         destFormat,
  CFURLRef            destLocation);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetDestinationType(
  PMPrintSession       printSession,
  PMPrintSettings      printSettings,
  PMDestinationType *  destTypeP);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyDestinationFormat(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFStringRef *     destFormatP);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyDestinationLocation(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  CFURLRef *        destLocationP);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCopyOutputFormatList(
  PMPrintSession      printSession,
  PMDestinationType   destType,
  CFArrayRef *        documentFormatP);



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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionCreatePageFormatList(
  PMPrintSession   printSession,
  PMPrinter        printer,
  CFArrayRef *     pageFormatList);


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
PMSetIdleProc(PMIdleUPP idleProc);


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
PMBegin(void);


/*
 *  PMEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnd(void);


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
  GrafPtr *        grafPort);


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
PMNewPageFormat(PMPageFormat * pageFormat);


/*
 *  PMDisposePageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePageFormat(PMPageFormat pageFormat);


/*
 *  PMDefaultPageFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPageFormat(PMPageFormat pageFormat);


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
  Boolean *      result);


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
PMNewPrintSettings(PMPrintSettings * printSettings);


/*
 *  PMDisposePrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisposePrintSettings(PMPrintSettings printSettings);


/*
 *  PMDefaultPrintSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDefaultPrintSettings(PMPrintSettings printSettings);


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
  Boolean *         result);


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
PMGeneral(Ptr pData);


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
  PMPageFormat *     pageFormat);


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
  Handle *          printRecordHandle);


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
PMIsPostScriptDriver(Boolean * isPostScript);


/*
 *  PMGetLanguageInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetLanguageInfo(PMLanguageInfo * info);


/*
 *  PMGetDriverCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverCreator(OSType * creator);


/*
 *  PMGetDriverReleaseInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDriverReleaseInfo(VersRec * release);


/*
 *  PMGetPrinterResolutionCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPrinterResolutionCount(UInt32 * count);


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
  PMResolution *  res);


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
  PMResolution *  res);


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
PMEnableColorSync(void);


/*
 *  PMDisableColorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMDisableColorSync(void);


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
PMPostScriptBegin(void);


/*
 *  PMPostScriptEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptEnd(void);


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
PMPostScriptHandle(Handle psHandle);


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
  Size   len);


/*
 *  PMPostScriptFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPostScriptFile(FSSpec * psFile);


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
PMError(void);


/*
 *  PMSetError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetError(OSStatus printError);


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
  PMPageFormat   formatDest);


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
  Handle *       flatFormat);


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
  PMPageFormat *  pageFormat);


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
  void *         extendedData);


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
  void *         extendedData);


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
  double *       scale);


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
  double         scale);


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
  PMResolution *  res);


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
  const PMResolution *  res);


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
  PMRect *       paperSize);


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
  const PMRect *  paperSize);


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
  PMRect *       pageSize);


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
  PMRect *       paperRect);


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
  PMRect *       pageRect);


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
  PMRect *       paperRect);


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
  const PMRect *  paperRect);


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
  PMRect *       pageRect);


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
  const PMRect *  pageRect);


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
  PMOrientation *  orientation);


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
  Boolean         lock);


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
  PMPrintSettings   settingDest);


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
  Handle *          flatSettings);


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
  PMPrintSettings *  printSettings);


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
  void *            extendedData);


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
  void *            extendedData);


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
  CFURLRef *           fileURL);


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
  StringPtr         name);


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
  StringPtr         name);


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
  UInt32 *          copies);


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
  Boolean           lock);


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
  UInt32 *          first);


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
  Boolean           lock);


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
  UInt32 *          last);


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
  Boolean           lock);


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
  UInt32 *          maxPage);


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
  UInt32            maxPage);


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
  const CMProfileLocation *  profile);


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
  PMColorMode *     colorMode);


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
  PMColorMode       colorMode);


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
  CFStringRef *     name);


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
  CFStringRef       name);



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

#endif /* __PMCORE__ */

