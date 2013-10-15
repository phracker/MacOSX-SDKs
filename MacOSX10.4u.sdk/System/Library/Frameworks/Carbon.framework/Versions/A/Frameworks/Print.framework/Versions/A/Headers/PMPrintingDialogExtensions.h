/*
     File:       PMPrintingDialogExtensions.h
 
     Contains:   Mac OS X Printing Manager Print Dialog Extensions' Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __PMPRINTINGDIALOGEXTENSIONS__
#define __PMPRINTINGDIALOGEXTENSIONS__

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

/*
    Parameters for printing events:
    
    kEventPrintingPDEResize
        -->     kEventParamDirectObject     typeControlRef
        -->     kEventParamPDEHeight        typeUInt32
        
    When sent to the this event is sent to the PageSetup or Print Dialog, the PDE pane
    will be resized to match the new height.  The kEventParamDirectObject needs to be the 
    embedderUserPane that is passed into Initialize
*/
enum {
  kEventClassPrinting           = FOUR_CHAR_CODE('prnt'),
  kEventPrintingPDEResize       = FOUR_CHAR_CODE('rqsz'),
  kEventParamPDEHeight          = FOUR_CHAR_CODE('pdeh')
};

/*
Define the Kind IDs for Universal and Standard Printing Dialog Extensions.
*/
/* Implemented Universal */
#define kPMPageAttributesKindID         CFSTR("com.apple.print.pde.PageAttributesKind")
#define kPMCopiesAndPagesPDEKindID      CFSTR("com.apple.print.pde.CopiesAndPagesKind")
#define kPMLayoutPDEKindID              CFSTR("com.apple.print.pde.LayoutUserOptionKind")
#define kPMOutputOptionsPDEKindID       CFSTR("com.apple.print.pde.OutputOptionsKind")
#define kPMDuplexPDEKindID              CFSTR("com.apple.print.pde.DuplexKind")
#define kPMCustomPaperSizePDEKindID     CFSTR("com.apple.print.pde.CustomPaperSizeKind")
#define kPMCoverPagePDEKindID           CFSTR("com.apple.print.pde.CoverPageKind")
#define kPMSchedulerPDEKindID           CFSTR("com.apple.print.pde.SchedulerKind")
#define kPMImagingOptionsPDEKindID		CFSTR("com.apple.print.pde.ImagingOptionsKind")
#define kPMFaxCoverPagePDEKindID		CFSTR("com.apple.print.pde.FaxCoverPageKind")
#define kPMFaxModemPDEKindID			CFSTR("com.apple.print.pde.FaxModemKind")
#define kPMPaperHandlingPDEKindID		CFSTR("com.apple.print.pde.PaperHandlingKind")
#define kPMSummaryPanelKindID			CFSTR("com.apple.print.pde.SummaryKind")
/* Unimplemented Universal */
#define kPMPaperSourcePDEKindID         CFSTR("com.apple.print.pde.PaperSourceKind")
#define kPMPriorityPDEKindID            CFSTR("com.apple.print.pde.PriorityKind")
#define kPMRotationScalingPDEKindID     CFSTR("com.apple.print.pde.RotationScalingKind")
/* Implemented Standard */
#define kPMErrorHandlingPDEKindID		CFSTR("com.apple.print.pde.ErrorHandlingKind")
#define kPMPaperFeedPDEKindID           CFSTR("com.apple.print.pde.PaperFeedKind")
#define kPMPrinterFeaturesPDEKindID		CFSTR("com.apple.print.pde.PrinterFeaturesKind")
#define kPMInkPDEKindID					CFSTR("com.apple.print.pde.InkKind")
/* Unimplemented Standard */
#define kPMColorPDEKindID               CFSTR("com.apple.print.pde.ColorKind")
#define kPMQualityMediaPDEKindID        CFSTR("com.apple.print.pde.QualityMediaPDEKind")
/*  These constants are used by PDE's to obtain the PMTicketRef data for the corresponding
    piece of data.
*/
#define kPDE_PMPrintSettingsRef 	CFSTR("PMPrintSettingsTicket")
#define kPDE_PMPageFormatRef	 	CFSTR("PMPageFormatTicket")
#define kPDE_PMJobTemplateRef 		CFSTR("PMJobTemplateTicket")
#define kPDE_PMPrinterInfoRef 		CFSTR("PMPrinterInfoTicket")


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Type Definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Basic types...
*/
typedef SInt32                          PMPDERef;
typedef UInt32                          PMPDEContext;
typedef UInt32                          PMPDEFlags;
/* Just for testing this .... */
/*#define    TEST_PLUGINS_LINKED_IN     1 */
/* Type and Interface IDs. */
#define kDialogExtensionIntfIDStr			CFSTR("A996FD7E-B738-11D3-8519-0050E4603277")
#define kGeneralPageSetupDialogTypeIDStr	CFSTR("6E6ED964-B738-11D3-952F-0050E4603277")
#define kGeneralPrintDialogTypeIDStr		CFSTR("C1BF838E-B72A-11D3-9644-0050E4603277")
#define kAppPageSetupDialogTypeIDStr		CFSTR("B9A0DA98-E57F-11D3-9E83-0050E4603277")
#define kAppPrintDialogTypeIDStr			CFSTR("BCB07250-E57F-11D3-8CA6-0050E4603277")
#define kAppPrintThumbnailTypeIDStr			CFSTR("9320FE03-B5D5-11D5-84D1-003065D6135E")
#define kPrinterModuleTypeIDStr				CFSTR("BDB091F4-E57F-11D3-B5CC-0050E4603277")

/* Versioning info. */
/* Update following values when you append new APIs to the end of interface: */
#define kPDEBuildVersionMajor   1
#define kPDEBuildVersionMinor   0
/* Update following values when you obsolete some APIs in the interface. */
/* Since this will break the upward compatibility chain such practice is */
/* strongly discouraged - if it can be helped at all. */
#define kPDEBaseVersionMajor        1
#define kPDEBaseVersionMinor        0
/* Interface layout - object and vtable: */

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

/* Some commonly used routines used by PDEs */

EXTERN_API_C( CFStringRef )
PMCreateLocalizedPaperSizeCFString( PMTicketRef listofPaperTickets, UInt16 paperToUse ); 
// Lower level version of the same function, this time passing the single PaperInfo.
EXTERN_API_C( CFStringRef )
PMCreatePaperSizeCFString( PMTicketRef selectedPaper ); 

EXTERN_API_C( void )
PMUpdatePrintButton( PMDestinationType dest ); 

#ifdef __cplusplus
}
#endif

#endif /* __PMPRINTINGDIALOGEXTENSIONS__ */

