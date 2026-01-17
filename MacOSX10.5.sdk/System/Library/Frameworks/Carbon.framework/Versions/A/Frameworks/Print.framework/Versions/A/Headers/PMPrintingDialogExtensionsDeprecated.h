/*
     File:       PMPrintingDialogExtensionsDeprecated.h
 
     Contains:   Mac OS X Printing Manager Print Dialog Extensions' Deprecated Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __PMPRINTINGDIALOGEXTENSIONSDEPRECATED__
#define __PMPRINTINGDIALOGEXTENSIONSDEPRECATED__

#if !__LP64__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Print/Print.h>
#include <PrintCore/PMTicket.h>
#include <PrintCore/PMPluginHeader.h>
#include <PrintCore/PMErrors.h>

#ifdef __cplusplus
extern "C" {
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Constants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*  These constants are used by Carbon Plugin PDE's to obtain the PMTicketRef data for the corresponding
    piece of data. Needed for 32 bit only.
*/
#define kPDE_PMJobTemplateRef 		CFSTR("PMJobTemplateTicket")
#define kPDE_PMPrinterInfoRef 		CFSTR("PMPrinterInfoTicket")
#define kPDE_PMPageFormatRef	 	CFSTR("PMPageFormatTicket")
#define kPDE_PMPrintSettingsRef 	CFSTR("PMPrintSettingsTicket")

enum {
  kEventUpdatePrintButton           = FOUR_CHAR_CODE('prbt'),
};


/*
Direction of sync
*/
enum {
	kPMSyncTicketFromPane = false,
	kPMSyncPaneFromTicket = true
};

/*
Feature request flags...
*/
enum {
    kPMPDENoFlags               = 0x00000000,                   /* Empty flag word. */
    kPMPDENoSummary             = 0x00000001,                   /* Won't provide summary string. */
    kPMPDEAllFlags              = (unsigned long)(-1)           /* All flags set.*/
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Type Definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Basic types...
*/

typedef SRefCon  PMPDERef;
typedef URefCon  PMPDEContext;

typedef UInt32  PMPDEFlags;

/* Versioning info. */
/* Update following values when you append new APIs to the end of interface: */
#define kPDEBuildVersionMajor   1
#define kPDEBuildVersionMinor   0
/* Update following values when you obsolete some APIs in the interface. */
/* Since this will break the upward compatibility chain such practice is */
/* strongly discouraged - if it can be helped at all. */
#define kPDEBaseVersionMajor        1
#define kPDEBaseVersionMinor        0


/*
    Parameters for printing events:
    
    kEventPrintingPDEResize
        -->     kEventParamDirectObject     typeControlRef
        -->     kEventParamPDEHeight        typeUInt32
        
    When sent to the this event is sent to the PageSetup or Print Dialog, the PDE pane
    will be resized to match the new height.  The kEventParamDirectObject needs to be the 
    embedderUserPane that is passed into Initialize. For use with Carbon PDEs only.
*/
enum {
  kEventClassPrinting           = FOUR_CHAR_CODE('prnt'),
  kEventPrintingPDEResize       = FOUR_CHAR_CODE('rqsz'),
  kEventParamPDEHeight          = FOUR_CHAR_CODE('pdeh')
};


/* Plugin vtable call back routines descriptors */
typedef struct PlugInIntf       PlugInIntf;
typedef struct PlugInIntfVTable PlugInIntfVTable;

typedef CALLBACK_API_C( OSStatus , PrologueProcPtr ) ( PMPDEContext *context, OSType *creator,
                            CFStringRef *userOptionKind, CFStringRef *title, UInt32 *maxH, UInt32 *maxV );
typedef CALLBACK_API_C( OSStatus , InitializeProcPtr ) ( PMPDEContext context, PMPDEFlags* flags,
                            PMPDERef ref,  ControlRef embedderUserPane, PMPrintSession printSession);
typedef CALLBACK_API_C( OSStatus , SyncProcPtr ) ( PMPDEContext context, PMPrintSession printSession,
                            Boolean reinitializePlugIn);
typedef CALLBACK_API_C( OSStatus , GetSummaryTextProcPtr ) ( PMPDEContext context, CFArrayRef *titleArray,
                            CFArrayRef *summaryArray );
typedef CALLBACK_API_C( OSStatus , OpenProcPtr ) ( PMPDEContext context );
typedef CALLBACK_API_C( OSStatus , CloseProcPtr ) ( PMPDEContext context );
typedef CALLBACK_API_C( OSStatus , TerminateProcPtr ) ( PMPDEContext context, 
                            OSStatus status );

struct PlugInIntf
{
    // Plugin interface is an object containing vtable address:
    PlugInIntfVTable*   vtable;
};

struct PlugInIntfVTable
{
    // ---- API 'IMMUTABLE' Begin: ----

    // The plugin header is required with all plugins.
    // This must lead object's layout.
    PMPlugInHeader          plugInHeader;
    
    // ---- API Version 1.0 Begin: ----

    // Entry points for Printing Dialog Extension modules...

    PrologueProcPtr				Prologue;
    InitializeProcPtr			Initialize;
    SyncProcPtr					Sync;
    GetSummaryTextProcPtr		GetSummaryText;
    OpenProcPtr					Open;
    CloseProcPtr				Close;
    TerminateProcPtr			Terminate;
};

EXTERN_API_C( void )
PMUpdatePrintButton( PMDestinationType dest ); 

/* Some commonly used routines used by PDEs */
EXTERN_API_C( CFStringRef )
PMCreateLocalizedPaperSizeCFString( PMTicketRef listofPaperTickets, UInt16 paperToUse ); 

// Lower level version of the same function, this time passing the single PaperInfo.
EXTERN_API_C( CFStringRef )
PMCreatePaperSizeCFString( PMTicketRef selectedPaper ); 


#ifdef __cplusplus
}
#endif

#endif /* !__LP64__ */

#endif /* __PMPRINTINGDIALOGEXTENSIONSDEPRECATED__ */

