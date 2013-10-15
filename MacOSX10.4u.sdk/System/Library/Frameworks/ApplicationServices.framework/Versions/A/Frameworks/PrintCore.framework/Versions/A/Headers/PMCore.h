/*
     File:       PrintCore/PMCore.h
 
     Contains:   Carbon Printing Manager Interfaces.
 
     Version:    PrintingCore-177.13~362
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
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

#if PM_USE_SESSION_APIS
#pragma mark
#pragma mark Session
#pragma mark
/*
 *  PMRetain()
 *  
 *  Summary:
 *    Increases a printing objects refcount by 1.
 *  
 *  Discussion:
 *    You should retain a printing object when you receive it from
 *    elsewhere (that is, you did not create or copy it) and you want
 *    it to persist. If you retain a printing object you are
 *    responsible for releasing it.
 *  
 *  Parameters:
 *    
 *    object:
 *      A Carbon Printing Manager object, such as a PMPrintSession
 *      object, a PMPageFormat object, a PMPrintSettings object, or
 *      PMPrinter object.
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
 *  Summary:
 *    Decreases a printing objects refcount by 1.
 *  
 *  Discussion:
 *    Your application should use the PMRelease function to release any
 *    printing objects it creates or retains. When an object’s
 *    reference count reaches 0, the object is deallocated. To
 *    terminate a printing session created with the function
 *    PMCreateSession, pass the associated PMPrintSession object to
 *    PMRelease. To release printing objects created with the functions
 *    PMCreatePageFormat and PMCreatePrintSettings, pass the associated
 *    PMPageFormat and PMPrintSettings objects to PMRelease. You can
 *    pass a NULL object but be aware a kPMInvalidParameter error will
 *    be returned.
 *  
 *  Parameters:
 *    
 *    object:
 *      A Carbon Printing Manager object, such as a PMPrintSession
 *      object, a PMPageFormat object, a PMPrintSettings object, or
 *      PMPrinter object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMRelease(PMObject object)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMCreateSession()
 *  
 *  Summary:
 *    Creates and initializes a printing session object and creates a
 *    context for printing operations.
 *  
 *  Discussion:
 *    A session is created with a refcount of 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreateSession(PMPrintSession * printSession)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMCreatePageFormat()
 *  
 *  Summary:
 *    Allocates memory for a new PMPageFormat object in your
 *    application’s memory space.
 *  
 *  Discussion:
 *    A pageformat is created with a refcount of 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreatePageFormat(PMPageFormat * pageFormat)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMCreatePrintSettings()
 *  
 *  Summary:
 *    Allocates memory for a new PMPrintSettings object in your
 *    application’s memory space.
 *  
 *  Discussion:
 *    A printSettings is created with a refcount of 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreatePrintSettings(PMPrintSettings * printSettings)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#pragma mark -
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


#pragma mark
#pragma mark Session: ColorSync
#pragma mark -
/*
 *  PMSessionEnableColorSync()
 *  
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect.
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
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionDisableColorSync(PMPrintSession printSession)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#pragma mark
#pragma mark Session: Error
#pragma mark -
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


#pragma mark
#pragma mark Session: Other routines
#pragma mark -
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
 *  PMSessionGetCGGraphicsContext()
 *  
 *  Summary:
 *    Return the CGContextRef for the current page in the printing
 *    session.
 *  
 *  Discussion:
 *    This function returns the CGContextRef for the printing session.
 *    This function must be called for each page. To use
 *    PMSessionGetCGGraphicsContext you MUST call
 *    PMSessionBeginCGDocument or PMSessionBeginCGDocumentNoDialog
 *    instead of PMSessionBeginDocument or
 *    PMSessionBeginDocumentNoDialog.
 *  
 *  Parameters:
 *    
 *    printSession:
 *      The session for the print job.
 *    
 *    context:
 *      A pointer to a caller supplied CGContextRef variable. If this
 *      function succeeds then *context will be filled in with the
 *      printing CGContextRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionGetCGGraphicsContext(
  PMPrintSession   printSession,
  CGContextRef *   context)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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
 *  PMSessionSetCurrentPMPrinter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionSetCurrentPMPrinter(
  PMPrintSession   session,
  PMPrinter        printer)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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


#pragma mark -
/*
 *  PMSessionBeginCGDocumentNoDialog()
 *  
 *  Summary:
 *    Begin a new print job that uses only drawing to a CoreGraphics
 *    context.
 *  
 *  Discussion:
 *    This is an updated version of the function
 *    PMSessionBeginDocumentNoDialog. The functionality is identical to
 *    PMSessionBeginDocumentNoDialog except that during a print job,
 *    the caller cannot obtain a Quickdraw grafPort for the printing
 *    context but can only obtain a Quartz graphics context
 *    (CGContextRef). This function should be used in conjunction with
 *    PMSessionGetCGGraphicsContext instead of
 *    PMSessionGetGraphicsContext.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginCGDocumentNoDialog(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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


#endif  /* PM_USE_SESSION_APIS */

#pragma mark -
#pragma mark PageFormat
#pragma mark
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


/*
 *  PMCreatePageFormatWithPMPaper()
 *  
 *  Summary:
 *    Create a pageformat with a specific paper.
 *  
 *  Parameters:
 *    
 *    pageFormat:
 *      On return, will contain the pageformat which was created
 *    
 *    paper:
 *      The paper that will be associate with the pageformat
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCreatePageFormatWithPMPaper(
  PMPageFormat *  pageFormat,
  PMPaper         paper)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMFlattenPageFormat()
 *  
 *  Summary:
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormat(
  PMPageFormat   pageFormat,
  Handle *       flatFormat)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMFlattenPageFormatToCFData()
 *  
 *  Discussion:
 *    Returns a flatten page format object in a CFDataRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormatToCFData(
  PMPageFormat   pageFormat,
  CFDataRef *    flatFormat)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMFlattenPageFormatToURL()
 *  
 *  Discussion:
 *    Returns a flatten page format object in a CFURLRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPageFormatToURL(
  PMPageFormat   pageFormat,
  CFURLRef       flattenFileURL)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#pragma mark -
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
 *  PMGetResolution()
 *  
 *  Summary:
 *    Obtains the current application drawing resolution.
 *  
 *  Discussion:
 *    This is the drawing resolution of an app. This should not be
 *    confused with the resolution of the printer. You can call
 *    PMGetPrinterResolution to see what resolutions are avaliable for
 *    the current printer.
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
 *  PMGetScale()
 *  
 *  Summary:
 *    Obtains the scaling factor currently applied to the page and
 *    paper rectangles.
 *  
 *  Discussion:
 *    A value of 100.0 means 100% (no scaling). 50.0 means 50% scaling
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
 *  PMGetUnadjustedPageRect()
 *  
 *  Summary:
 *    Obtains the size of the imageable area in points, unaffected by
 *    orientation, resolution, or scaling.
 *  
 *  Discussion:
 *    This is the physical size of the page without regard to
 *    resolution, orientation or scaling. It is returned as a 72dpi
 *    value.
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
 *  PMGetUnadjustedPaperRect()
 *  
 *  Summary:
 *    Obtains a rectangle that specifies the size of the paper in
 *    points, unaffected by rotation, resolution, or scaling.
 *  
 *  Discussion:
 *    This is the physical size of the paper without regard to
 *    resolution, orientation or scaling. It is returned as a 72dpi
 *    value.
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


#pragma mark -
/************************/
/* PMSetxxx calls only save the value inside the printing object. They make no assumption on the */
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


/*
 *  PMUnflattenPageFormatWithCFData()
 *  
 *  Discussion:
 *    Returns a page format object given a CFDataRef to a previously
 *    flatten page format.
 *  
 *  Parameters:
 *    
 *    flattenCFData:
 *      A CFDataRef containing a flatten print settings.
 *    
 *    pageFormat:
 *      On return, a newly created page format object create with the
 *      data contained in 'flattenCFData'. The printing framework will
 *      create the object. The app is responsible for disposing of it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormatWithCFData(
  CFDataRef       flattenCFData,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMUnflattenPageFormatWithURL()
 *  
 *  Discussion:
 *    Returns a page format object given a CFURLRef to a file
 *    containing a previously flatten page format.
 *  
 *  Parameters:
 *    
 *    flattenFileURL:
 *      A CFURLRef containing a flatten page format.
 *    
 *    pageFormat:
 *      On return, a newly created page format object create with the
 *      data contained in 'flattenFileURL'. The printing framework will
 *      create the object. The app is responsible for disposing of it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPageFormatWithURL(
  CFURLRef        flattenFileURL,
  PMPageFormat *  pageFormat)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#pragma mark -
#pragma mark PrintSettings
#pragma mark
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



/*
 *  PMFlattenPrintSettings()
 *  
 *  Summary:
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettings(
  PMPrintSettings   printSettings,
  Handle *          flatSettings)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PMFlattenPrintSettingsToCFData()
 *  
 *  Discussion:
 *    Returns a flatten print settings object in a CFDataRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettingsToCFData(
  PMPrintSettings   printSettings,
  CFDataRef *       flatSetting)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMFlattenPrintSettingsToURL()
 *  
 *  Discussion:
 *    Returns a flatten print settings object in a CFURLRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMFlattenPrintSettingsToURL(
  PMPrintSettings   printSettings,
  CFURLRef          flattenFileURL)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#pragma mark -
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
 *  PMGetDuplex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetDuplex(
  PMPrintSettings   printSettings,
  PMDuplexMode *    duplexSetting)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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
 *  PMGetPageRange()
 *  
 *  Summary:
 *    Obtains the valid range of pages that can be printed.
 *  
 *  Discussion:
 *    The default page range is 1 - (all pages). The page range is
 *    something that is set by the application. It is NOT the first and
 *    last page to print. It serves as limits for setting the first and
 *    last page.
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


#pragma mark -
/*
 *  PMPrintSettingsGetJobName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintSettingsGetJobName(
  PMPrintSettings   printSettings,
  CFStringRef *     name)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrintSettingsSetJobName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintSettingsSetJobName(
  PMPrintSettings   printSettings,
  CFStringRef       name)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrintSettingsGetValue()
 *  
 *  Parameters:
 *    
 *    printSettings:
 *      The printsettings to retrieve the value from
 *    
 *    key:
 *      The key to look for
 *    
 *    value:
 *      The return value. Its either the value for the key or NULL
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintSettingsGetValue(
  PMPrintSettings   printSettings,
  CFStringRef       key,
  CFTypeRef *       value)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrintSettingsSetValue()
 *  
 *  Parameters:
 *    
 *    printSettings:
 *      The printsettings in which to set the value
 *    
 *    key:
 *      The key to store the value in
 *    
 *    value:
 *      The value to store in the key. If NULL, the ticket item is
 *      removed.
 *    
 *    locked:
 *      A boolean value indicating whether the item being set should be
 *      locked.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintSettingsSetValue(
  PMPrintSettings   printSettings,
  CFStringRef       key,
  CFTypeRef         value,
  Boolean           locked)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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
 *  PMSetDuplex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetDuplex(
  PMPrintSettings   printSettings,
  PMDuplexMode      duplexSetting)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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


/*
 *  PMSetPageRange()
 *  
 *  Summary:
 *    Sets the valid range of pages that can be printed.
 *  
 *  Discussion:
 *    The first and last page are immediately clipped to the new range.
 *    You may pass kPMPrintAllPages for the maxPage value to specified
 *    that all pages are available for printing.
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
 *  Discussion:
 *    Application must be rendering with QuickDraw for this to have
 *    effect.
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


/*
 *  PMUnflattenPrintSettingsWithCFData()
 *  
 *  Discussion:
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
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettingsWithCFData(
  CFDataRef          flattenCFData,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMUnflattenPrintSettingsWithURL()
 *  
 *  Discussion:
 *    Returns a print settings object given a CFURLRef to a file
 *    containing a previously flatten print settings.
 *  
 *  Parameters:
 *    
 *    flattenFileURL:
 *      A CFURLRef containing a flatten print settings.
 *    
 *    printSettings:
 *      On return, a newly created print settings object create with
 *      the data contained in 'flattenFileURL'. The printing framework
 *      will create the object. The app is responsible for disposing of
 *      it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMUnflattenPrintSettingsWithURL(
  CFURLRef           flattenFileURL,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#pragma mark -
#pragma mark Printer
#pragma mark
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
 *  PMPrinterCreateFromPrinterID()
 *  
 *  Summary:
 *    Create a PMPrinter instance from the supplied printerID.
 *  
 *  Discussion:
 *    Returns a PMPrinter instance for the printer whose ID is
 *    printerID. The caller is responsible for releasing this instance
 *    with PMRelease. The PMPrinter instance returned will be NULL if
 *    there is no printer available which corresponds to the supplied
 *    printerID.
 *  
 *  Parameters:
 *    
 *    printerID:
 *      The printerID for the printer for which you want the PMPrinter.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern PMPrinter 
PMPrinterCreateFromPrinterID(CFStringRef printerID)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrinterCopyDescriptionURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterCopyDescriptionURL(
  PMPrinter     printer,
  CFStringRef   descriptionType,
  CFURLRef *    fileURL)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrinterCopyDeviceURI()
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
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterCopyDeviceURI(
  PMPrinter   printer,
  CFURLRef *  deviceURI)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  PMPrinterCopyHostName()
 *  
 *  Summary:
 *    Hand back the host name of the printer's server.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterCopyHostName(
  PMPrinter      printer,
  CFStringRef *  hostNameP)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPrinterCopyPresets()
 *  
 *  Summary:
 *    Provides a list of print settings presets for the specified
 *    printer.
 *  
 *  Discussion:
 *    A printer may have associated with it a list of preset settings.
 *    Each setting is optimized for a particular printing situation.
 *    This function returns all of the presets for a given printer. To
 *    obtain more information about a particular preset see
 *    PMPresetGetAttributes(). To apply a preset to some print
 *    settings, use PMPresetApplyToPrintSettings().
 *  
 *  Parameters:
 *    
 *    printer:
 *      Obtain the presets for this printer.
 *    
 *    presetList:
 *      On exit, *'presetList' is set to reference an array of presets.
 *      The caller must call CFRelease when it no longer needs the
 *      array. Each element of the array is a PMPPreset. If this
 *      function fails, returning a non-zero error code, then
 *      *'presetList' will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterCopyPresets(
  PMPrinter     printer,
  CFArrayRef *  presetList)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPrinterGetCommInfo()
 *  
 *  Summary:
 *    Provides information about the comm channel characteristics for
 *    the printer.
 *  
 *  Discussion:
 *    This function is typically relevant only to PostScript capable
 *    printers. All PostScript printers, regardless of what
 *    communications channel is used to send data to them, support data
 *    in the range 0x20 - 0x7F. Many comm channels can support data
 *    outside this range. The Boolean returned in *supportsTransparentP
 *    indicates whether the comm channel to this printer supports bytes
 *    in the range 0x0 to 0x1F. The Boolean returned in
 *    *supportsEightBitP indicates whether the comm channel to this
 *    printer supports bytes with the high bit set, i.e. bytes in the
 *    range 0x80 - 0xFF.
 *  
 *  Parameters:
 *    
 *    printer:
 *      Obtain the comm information for this printer.
 *    
 *    supportsTransparentP:
 *      Storage for the returned Boolean indicating whether the comm
 *      channel to this printer is transparent to bytes in the range
 *      0x0 - 0x1F
 *    
 *    supportsEightBitP:
 *      Storage for the returned Boolean indicating whether the comm
 *      channel to this printer can bytes in the range 0x80 - 0xFF
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetCommInfo(
  PMPrinter   printer,
  Boolean *   supportsTransparentP,
  Boolean *   supportsEightBitP)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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


/*
 *  PMPrinterGetMimeTypes()
 *  
 *  Summary:
 *    Return the array of mime type supported by the printer for a
 *    given set of print settings.
 *  
 *  Parameters:
 *    
 *    printer:
 *      The printer.
 *    
 *    settings:
 *      The print settings for the print job. The part of the print
 *      settings that effects the available mime type is the
 *      destination. This parameter can be NULL.
 *    
 *    mimeTypes:
 *      If this function returns without error then *'mimeTypes' is
 *      filled in with a reference to an array of CFStrings. Each
 *      CFString names a mime type supported by the printer with the
 *      specified print settings. The caller must not release this
 *      reference without first doing a retain. If this function
 *      returns an error then 'mimeTypes' will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetMimeTypes(
  PMPrinter         printer,
  PMPrintSettings   settings,
  CFArrayRef *      mimeTypes)                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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
 *  PMPrinterGetPaperList()
 *  
 *  Summary:
 *    Returns the list of papers available for a given printer.
 *  
 *  Parameters:
 *    
 *    printer:
 *      Obtain the paper list for this printer. Passing NULL will
 *      return the paper list for the generic printer
 *    
 *    paperList:
 *      If successful noErr is returned and *paperList is a CFArray of
 *      PMPapers representing the list of papers available for the
 *      printer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetPaperList(
  PMPrinter     printer,
  CFArrayRef *  paperList)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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
 *  PMPrinterIsRemote()
 *  
 *  Summary:
 *    Hand back a boolean indicating whether the printer is hosted on a
 *    remote print server.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterIsRemote(
  PMPrinter   printer,
  Boolean *   isRemoteP)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark Preset
#pragma mark
/*
 *  PMPresetCopyName()
 *  
 *  Summary:
 *    Hand back a copy of the localized name for the specified preset.
 *  
 *  Parameters:
 *    
 *    preset:
 *      The preset whose name is needed.
 *    
 *    name:
 *      On exit, if this routine succeeds, *'name' is filled in with a
 *      reference to a localized string with the preset's name. If this
 *      routine fails, then *'name' is set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPresetCopyName(
  PMPreset       preset,
  CFStringRef *  name)                                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPresetCreatePrintSettings()
 *  
 *  Summary:
 *    Create a print settings conforming to the specified print
 *    settings preset.
 *  
 *  Parameters:
 *    
 *    preset:
 *      A preset specifying a set of initial print settings.
 *    
 *    session:
 *      A valid print session.
 *    
 *    printSettings:
 *      On exit, *'printSettings' is set to a newly created print
 *      settings that contains the settings specified by 'preset'. The
 *      caller is responsible for calling PMRelease when the print
 *      settings are no longer needed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPresetCreatePrintSettings(
  PMPreset           preset,
  PMPrintSession     session,
  PMPrintSettings *  printSettings)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPresetGetAttributes()
 *  
 *  Summary:
 *    Hand back the meta-data describing a given preset.
 *  
 *  Discussion:
 *    Each preset has associated with it a dictionary containing
 *    meta-data. The meta-data provides the preset's id, the preset's
 *    localized names, and descriptions of the environment for which
 *    the preset it intended.
 *  
 *  Parameters:
 *    
 *    preset:
 *      A print settings preset as obtained from PMPrinterCopyPresets().
 *    
 *    attributes:
 *      On exit, *'attributes' is set to reference a dictionary
 *      containing the preset's meta-data. The caller is responsible
 *      for retaining this reference if it is to be used beyond the
 *      lifetime of 'preset'. If this function fails, returning a
 *      non-zero error code, then *'attributes' is set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPresetGetAttributes(
  PMPreset           preset,
  CFDictionaryRef *  attributes)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark Paper
#pragma mark
/*
 *  PMGetPageFormatPaper()
 *  
 *  Summary:
 *    Returns the paper associated with a pageformat.
 *  
 *  Parameters:
 *    
 *    format:
 *      Obtain the paper for this pageformat.
 *    
 *    paper:
 *      If successful noErr is returned and *paper will contain a
 *      PMPaper object describing the current paper associated with the
 *      pageformat.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPageFormatPaper(
  PMPageFormat   format,
  PMPaper *      paper)                                       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperCreate()
 *  
 *  Summary:
 *    Create a new paper instance.
 *  
 *  Parameters:
 *    
 *    printer:
 *      The new paper size is appropriate for this printer.
 *    
 *    id:
 *      A unique identifier for this paper type.
 *    
 *    name:
 *      The name to display to the user for this paper type.
 *    
 *    width:
 *      The width, in points, of the paper.
 *    
 *    height:
 *      The height, in points, of the paper.
 *    
 *    margins:
 *      The unprintable margins on the paper.
 *    
 *    paperP:
 *      if this function is successful, returning noErr, then *'paperP'
 *      is set to be a reference to a newly created PMPaper instance.
 *      The caller is responsible for calling PMRelease when the
 *      instance is no longer needed. If this functions fails, it will
 *      return a non-zero error and set *'paperP' to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
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
  PMPaper *               paperP)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperGetID()
 *  
 *  Summary:
 *    Returns the id for a given paper.
 *  
 *  Parameters:
 *    
 *    paper:
 *      Obtain the id for this paper.
 *    
 *    paperID:
 *      If successful noErr is returned and *paperID is set to the id
 *      of the paper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperGetID(
  PMPaper        paper,
  CFStringRef *  paperID)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperGetHeight()
 *  
 *  Summary:
 *    Returns the height for a given paper.
 *  
 *  Parameters:
 *    
 *    paper:
 *      Obtain the height for this paper.
 *    
 *    paperHeight:
 *      If successful noErr is returned and *paperHeight is set to the
 *      height of the paper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperGetHeight(
  PMPaper   paper,
  double *  paperHeight)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperGetMargins()
 *  
 *  Summary:
 *    Returns the margins for a given paper.
 *  
 *  Parameters:
 *    
 *    paper:
 *      Obtain the margin information for this paper.
 *    
 *    paperMargins:
 *      If successful noErr is returned and *paperMargins is set to the
 *      margins of the paper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperGetMargins(
  PMPaper           paper,
  PMPaperMargins *  paperMargins)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperGetName()
 *  
 *  Summary:
 *    Returns the name for a given paper.
 *  
 *  Parameters:
 *    
 *    paper:
 *      Obtain the name for this paper.
 *    
 *    paperName:
 *      If successful noErr is returned and *paperName is set to the
 *      name of the paper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperGetName(
  PMPaper        paper,
  CFStringRef *  paperName)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPaperGetWidth()
 *  
 *  Summary:
 *    Returns the width for a given paper.
 *  
 *  Parameters:
 *    
 *    paper:
 *      Obtain the width for this paper.
 *    
 *    paperWidth:
 *      If successful noErr is returned and *paperWidth is set to the
 *      width of the paper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPaperGetWidth(
  PMPaper   paper,
  double *  paperWidth)                                       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark PDF Workflow
#pragma mark
/*
 *  PMWorkflowCopyItems()
 *  
 *  Summary:
 *    Hand back an array of dictionaries describing the PDF Workflow
 *    items installed on the system
 *  
 *  Parameters:
 *    
 *    workflowItems:
 *      If this function returns without error then *'workflowItems'
 *      will be filled in with a reference to an array. It is the
 *      caller's responsability to release the array when done with it.
 *      Each element in the array describes a PDF Workflow item or a
 *      folder holding workflow items. A dictionary describing a
 *      workflow item has, at least, the following keys and values:
 *      displayName - The user's diaplayable name for the workflow item
 *      itemURL - A CFURLRef pointing to the workflow item. A
 *      dictionary describing a workflow folder has at least the
 *      following keys: displayName - The user's diaplayable name for
 *      the workflow item folderURL - A CFURLRef pointing to the
 *      folder. items - A CFArrayRef describing the workflow items in
 *      the folder. If this function returns a non-zero error code then
 *      *'workflowItems' will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMWorkflowCopyItems(CFArrayRef * workflowItems)               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMWorkflowSubmitPDFWithOptions()
 *  
 *  Summary:
 *    Submit a PDF file for workflow processing.
 *  
 *  Discussion:
 *    The print dialog uses this function is conjunction with
 *    PMWorkflowGetItems to implement the PDF workflow button. Caller's
 *    can use PMWorkflowGetItems to obtain a CFURLRef that can be
 *    passed to PMWorkflowPDF or they can create a CFURLRef to another
 *    file system item.
 *  
 *  Parameters:
 *    
 *    workflowItem:
 *      A file system URL pointing to the workflow item that will
 *      handle the PDF file. Here are the different types of workflow
 *      items currently supported: Folder alias:   The PDF is moved to
 *      the resolved folder. Application or application alias: The
 *      application is sent an open event along with a reference to the
 *      PDF file. Compiled data fork AppleScript: The applescript is
 *      run with an open event along with a reference to the PDF file.
 *      executable tool: The tool is run with the following parameters:
 *      title options pdfFile
 *    
 *    title:
 *      The user displayable name of the document.
 *    
 *    options:
 *      A string of CUPS style key-value pairs that may be passed to
 *      the PDF Workflow item. This parameter can be NULL in which case
 *      an empty string of options is used.
 *    
 *    pdfFile:
 *      A file system URL pointing to the file to be processed by the
 *      workflow item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMWorkflowSubmitPDFWithOptions(
  CFURLRef      workflowItem,
  CFStringRef   title,
  const char *  options,
  CFURLRef      pdfFile)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMWorkflowSubmitPDFWithSettings()
 *  
 *  Summary:
 *    Submit a PDF file for workflow processing.
 *  
 *  Discussion:
 *    The print dialog uses this function is conjunction with
 *    PMWorkflowGetItems to implement the PDF workflow button. Caller's
 *    can use PMWorkflowGetItems to obtain a CFURLRef that can be
 *    passed to PMWorkflowPDF or they can create a CFURLRef to another
 *    file system item.
 *  
 *  Parameters:
 *    
 *    workflowItem:
 *      A file system URL pointing to the workflow item that will
 *      handle the PDF file. Here are the different types of workflow
 *      items currently supported: Folder alias:   The PDF is moved to
 *      the resolved folder. Application or application alias: The
 *      application is sent an open event along with a reference to the
 *      PDF file. Compiled data fork AppleScript: The applescript is
 *      run with an open event along with a reference to the PDF file.
 *      executable tool: The tool is run with the following parameters:
 *      title options pdfFile
 *    
 *    settings:
 *      The prints settings to apply to the PDF.
 *    
 *    pdfFile:
 *      A file system URL pointing to the file to be processed by the
 *      workflow item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMWorkflowSubmitPDFWithSettings(
  CFURLRef          workflowItem,
  PMPrintSettings   settings,
  CFURLRef          pdfFile)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark Job Submission
#pragma mark
/*
 *  PMPrinterPrintWithProvider()
 *  
 *  Summary:
 *    Submit a print data to a specified printer.
 *  
 *  Parameters:
 *    
 *    printer:
 *      The printer.
 *    
 *    settings:
 *      The print settings for the print job.
 *    
 *    format:
 *      The physical page size and orientation on to which the document
 *      should be printed. This parameter can be NULL.
 *    
 *    mimeType:
 *      The mime type of the file to be printed. This parameter can not
 *      be NULL. Use PMPrinterPrintWithFile() if aut-typing is desired.
 *    
 *    provider:
 *      The data provider that supplies the print data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterPrintWithProvider(
  PMPrinter           printer,
  PMPrintSettings     settings,
  PMPageFormat        format,
  CFStringRef         mimeType,
  CGDataProviderRef   provider)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPrinterPrintWithFile()
 *  
 *  Summary:
 *    Submit a file for printing to a specified printer.
 *  
 *  Discussion:
 *    One reason this function may fail is if the specified printer can
 *    not handle the file's mime type. Use PMPrinterGetMimeTypes() to
 *    check whether a mime type is supported. This function is
 *    implemented using PMPrinterPrintWithProvider().
 *  
 *  Parameters:
 *    
 *    printer:
 *      The printer.
 *    
 *    settings:
 *      The print settings for the print job.
 *    
 *    format:
 *      The physical page size and orientation on to which the document
 *      should be printed. This parameter can be NULL.
 *    
 *    mimeType:
 *      The mime type of the file to be printed. If this parameter is
 *      NULL then the supplied file will be auto-typed.
 *    
 *    fileURL:
 *      A file URL specifying the file to be printed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterPrintWithFile(
  PMPrinter         printer,
  PMPrintSettings   settings,
  PMPageFormat      format,
  CFStringRef       mimeType,
  CFURLRef          fileURL)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMPrintSettingsToOptions()
 *  
 *  Summary:
 *    Convert print settings to a CUPS style options string.
 *  
 *  Parameters:
 *    
 *    settings:
 *      The print settings that should be converted to a CUPS style
 *      options string.
 *    
 *    options:
 *      On exit *'options' will be filled in with a malloc'd C string
 *      describing the passed in print settings. It is the caller's
 *      responsibility to free this memory when done with it. If this
 *      function fails returning a non-zero error code then *'options'
 *      will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrintSettingsToOptions(
  PMPrintSettings   settings,
  char **           options)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark PPD related
#pragma mark
/*
 *  PMCopyAvailablePPDs()
 *  
 *  Summary:
 *    Hand back the list of PPDs in the specified PPD domain.
 *  
 *  Parameters:
 *    
 *    domain:
 *      The domain to search for PPDs.
 *    
 *    ppds:
 *      If this function completes without error, *'ppds' is set to an
 *      array of CFURLs. Each CFURL specifies the location of a PPD
 *      file or a compressed PPD file. The caller is responsible for
 *      releasing the array. If this function returns a non-zero error
 *      code then *'ppds' is set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCopyAvailablePPDs(
  PMPPDDomain   domain,
  CFArrayRef *  ppds)                                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMCopyLocalizedPPD()
 *  
 *  Summary:
 *    Hand back a reference to a localized PPD.
 *  
 *  Parameters:
 *    
 *    ppd:
 *      A PPD reference. Typically this is a CFURLRef returned from
 *      PMCopyAvailablePPDs().
 *    
 *    localizedPPD:
 *      If this function completes without error, *'localizedPPD' will
 *      be set to a CFURLRef referencing the PPD that should be used
 *      given the current user's language preferences. If this function
 *      returns an error then *'localizedPPD' will be set to to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCopyLocalizedPPD(
  CFURLRef    ppd,
  CFURLRef *  localizedPPD)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  PMCopyPPDData()
 *  
 *  Summary:
 *    Hand back the uncompressed PPD data for a PPD or compressed PPD
 *    file.
 *  
 *  Parameters:
 *    
 *    ppd:
 *      A reference to a PPD or compressed PPD file. This reference is
 *      usually obtained from PMCopyAvailablePPDs() or from
 *      PMCopyLocalizedPPD().
 *    
 *    data:
 *      If this function completes without error then *'data' is set to
 *      reference the uncompressed PPD data from the PPD file. If this
 *      function returns a non-zero error then *'data is set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMCopyPPDData(
  CFURLRef     ppd,
  CFDataRef *  data)                                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#pragma mark
#pragma mark EPS related
#pragma mark
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



#pragma mark -
#pragma mark DEPRECATED
#pragma mark
/* Callbacks */
/*****************************************/
/*  All Idle UPP routines are deprecated */
/*****************************************/
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

#if PM_USE_SESSION_APIS
/*
 *  PMSessionSetIdleProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    PMPrinterPrintWithProvider
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionIsDocumentFormatSupported(
  PMPrintSession   printSession,
  CFStringRef      docFormat,
  Boolean *        supported)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#else
/*
 *  PMSetIdleProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMBegin(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMEnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnd(void)                                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetGrafPtr()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionGetGraphicsContext or PMSessionGetCGGraphicsContext
 *    instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMValidatePrintSettings(
  PMPrintSettings   printSettings,
  Boolean *         result)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#pragma mark
#pragma mark DEPRECATED
#pragma mark
/* Classic Support */
/*
 *  PMGeneral()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGeneral(Ptr pData)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMConvertOldPrintRecord()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Use PMPrinterIsPostScriptCapable instead..
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Use PMSessionEnableColorSync instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMEnableColorSync(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMDisableColorSync()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMSessionDisableColorSync instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetError(OSStatus printError)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif  /* PM_USE_SESSION_APIS */

/*
 *  PMSetJobName()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsSetJobName instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetJobNameCFString()
 *  
 *  Discussion:
 *    Use PMPrintSettingsGetJobName instead. Please be aware that
 *    PMGetJobNameCFString will return a copy of the job name which
 *    you'll need to release while PMPrintSettingsGetJobName will not.
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
 *  PMGetJobName()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrintSettingsGetJobName instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetJobName(
  PMPrintSettings   printSettings,
  StringPtr         name)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetUnadjustedPaperRect()
 *  
 *  Discussion:
 *    To set a particular paper size create a PMPaper first then call
 *    PMCreatePageFormatWithPMPaper.
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
 *  PMGetPhysicalPaperSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMGetUnadjustedPaperRect instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMGetPhysicalPaperSize(
  PMPageFormat   pageFormat,
  PMRect *       paperSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMSetPhysicalPaperSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    To set a particular paper size create a PMPaper first then call
 *    PMCreatePageFormatWithPMPaper.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetPhysicalPaperSize(
  PMPageFormat    pageFormat,
  const PMRect *  paperSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMGetPhysicalPageSize()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMGetUnadjustedPageRect instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSetColorMode(
  PMPrintSettings   printSettings,
  PMColorMode       colorMode)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  PMPrinterGetDescriptionURL()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Use PMPrinterCopyDescriptionURL instead. Please be aware that
 *    PMPrinterGetDescriptionURL will return a copy of the URL which
 *    you'll need to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework but deprecated in 10.4
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
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMPrinterGetDeviceURI(
  PMPrinter   printer,
  CFURLRef *  deviceURI)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#pragma mark
#pragma mark DEPRECATED

#ifdef __cplusplus
}
#endif

#endif /* __PMCORE__ */

