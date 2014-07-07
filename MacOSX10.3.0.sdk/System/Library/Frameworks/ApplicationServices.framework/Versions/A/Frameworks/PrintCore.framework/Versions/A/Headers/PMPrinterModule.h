/*
     File:       PMPrinterModule.h
 
     Contains:   Mac OS X Printing Manager Printer Module Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
	History:

*/
#ifndef __PMPRINTERMODULE__
#define __PMPRINTERMODULE__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFString.h>
#include <PrintCore/PMPluginHeader.h>
#include <PrintCore/PMTicket.h>
#include <PrintCore/PMTemplate.h>
#include <PrintCore/PMRaster.h>
#include <PrintCore/PMErrors.h>

#ifdef __cplusplus
extern "C" {
#endif

/* context ID for PM Modules */
typedef struct OpaquePMContext*         PMContext;

/* Opaque types for image access: */
typedef void *                          PMDrawingCtx;
typedef void *                          PMImageRef;

/* Type ID, interface ID for the IOM CFPlugin */
#define kPModuleTypeIDStr       "5D69ED5E-D5B5-11D3-9EFF-00050209D9C1"
#define kPModuleIntfIDStr       "5EDEC4FA-D5B5-11D3-AAF2-00050209D9C1"

/* PM API version numbers (see PMPluginHeader.h for the meaning of these defintions) */
#define kPMBuildVersionMajor    1
#define kPMBuildVersionMinor    0
#define kPMBaseVersionMajor     1
#define kPMBaseVersionMinor     0

/*
Keys for the printer browser specification dictionary. This CFDictionary,
created by the printer module, provides a printer browser module with the 
information it needs to browse for a given type of printer over its 
connection type, and to display it in PrintCenter's Browser Window.

kPMPrinterBrowserKindKey corresponds to a CFStringRef to a human-readable 
printer type string that can be displayed in the browser view. For a printer 
driven by Apple's PostScript printer module over an AppleTalk connection, 
this would be the string "PostScript printer".

kPMPrinterBrowserInfoKey corresponds to a CFTypeRef to connection-specific 
information used to look up a particular kind of printer over a given IO 
connection. A PostScript printer module supporting AppleTalk might specify 
the NBP lookup string "LaserWriter".

kPMPrinterBrowserIconKey corresponds to a CFDataRef to the icon family data 
for the printer icon to be displayed in the browser view. The family data 
are entirely contained within the CFDataRef; i.e., it is *not* a handle.

kPMPrinterBrowserDeviceIDKey corresponds to a CFStringRef to a USB/Firewire
IEEE-1284 DeviceID string. e.g., "COMMAND SET: PostScript;" or 
"MFG: Hewlett-Packard; MDL: DeskJet 935C;"
*/
#define kPMPrinterBrowserKindKey     CFSTR("Printer Browser Kind")    	/* CFStringRef */
#define kPMPrinterBrowserInfoKey     CFSTR("Printer Browser Info")    	/* CFTypeRef */
#define kPMPrinterBrowserIconsKey    CFSTR("Printer Browser Icons")   	/* CFDataRef */
#define kPMPrinterBrowserDeviceIDKey CFSTR("Printer Browser DeviceID")	/* CFStringRef */
#define kPMBrowserInfoNumValues      4


/* Status and Error notification: */

/* PMNotificationProcPtr is a callback routine used for reporting printing status and errors during a print job  */
/* Event is constructed with known keys defined below and passed to the printing manager in notificationDict */
/* notificationReplyDict is used for blocking recoverable errors to indicate user action */
typedef CALLBACK_API_C( OSStatus , PMNotificationProcPtr )(const void *jobContext, CFDictionaryRef notificationDict, CFDictionaryRef *notificationReplyDict);

/* Status and error event codes and keys reported by the printer module (used in PMNotificationProc) */
#define kPMEventPrinterStatus						4000L		/* non-error printer status */

#define kPMEventErrorOccurred						4001L		/* a fatal printing error has occurred.  The Printer Module MUST 
																stop printing and return immediately after sending this event.
																*/
#define kPMEventRecoverableErrorOccurred			4002L		/* an auto-recoverable error occurred.  The PM SHOULD keep trying
																to print the job without waiting for any user action.
																If the PM detects that the condition is cleared, it 
																MUST send a kPMEventRecoverableErrorCleared event, otherwise
																the condition alert will not get cleared
																*/
#define kPMEventRecoverableErrorCleared				4003L		/* auto-recoverable error has been cleared, the job is continued
																automatically and without user intervention.  This event causes the
																condition alert to close and the job state to change to "printing".
																*/
	
/* Event keys used in notification dictionaries */
#define kPMEventCodeKey				CFSTR("com.apple.printing.EventCode")		/* CFNumber (SInt32) containing the event code (above) */
#define	kPMErrorCodeKey				CFSTR("com.apple.printing.ErrorCode")		/* CFNumber (SInt32) containing the error code (i.e., OSStatus) */
#define kPMErrorExplanationKey		CFSTR("com.apple.printing.ErrorExplanation")/* CFString containing the text that shows up as bold text in the error/status alert */
#define kPMErrorTextKey				CFSTR("com.apple.printing.ErrorText")		/* CFString containing the text that shows up as regular text in the error/status alert */
#define	kPMEventContextKey			CFSTR("com.apple.printing.EventContext") 	/* CFNumber (SInt32) containing a context value. Used primarily to match a "cleared error" event with a prior "recoverable error" event */

/* prototypes for callback routines used for accessing print data */
typedef CALLBACK_API_C( OSStatus , PMJobStreamOpenProcPtr )(const void *jobContext);
typedef CALLBACK_API_C( OSStatus , PMJobStreamReadWriteProcPtr )(const void *jobContext, void *buffPtr, UInt32 *size);
typedef CALLBACK_API_C( OSStatus , PMJobStreamGetPosProcPtr )(const void *jobContext, UInt32 *markerPos);
typedef CALLBACK_API_C( OSStatus , PMJobStreamSetPosProcPtr )(const void *jobContext, SInt16 posMode, UInt32 markerPos);
typedef CALLBACK_API_C( OSStatus , PMJobStreamGetNextBandProcPtr )(const void *jobContext, PMRasterBand *pmRasterBand);

/* the printing manager maintains this struct of callback procs for printer module data access */
struct PMJobStreamProcs {
    CFIndex                         version;

    PMJobStreamOpenProcPtr          PMJobStreamOpenProc;
    PMJobStreamReadWriteProcPtr     PMJobStreamReadProc;
    PMJobStreamReadWriteProcPtr     PMJobStreamWriteProc;
    PMJobStreamGetPosProcPtr        PMJobStreamGetPosProc;
    PMJobStreamSetPosProcPtr        PMJobStreamSetPosProc;
    PMJobStreamGetPosProcPtr        PMJobStreamGetEOFProc;
};
typedef struct PMJobStreamProcs         PMJobStreamProcs;

/* prototypes for callback routines used for communication with the device/connection */
typedef CALLBACK_API_C( OSStatus , GetConnInfoProcPtr )(const void *jobContext, CFStringRef *connectionType, CFStringRef *pbmPath);
typedef CALLBACK_API_C( OSStatus , PMIOOpenProcPtr )(const void *jobContext);
typedef CALLBACK_API_C( OSStatus , PMIOReadProcPtr )(const void *jobContext, Ptr buffer, UInt32 *size, Boolean *eoj);
typedef CALLBACK_API_C( OSStatus , PMIOWriteProcPtr )(const void *jobContext, Ptr buffer, UInt32 *size, Boolean eoj);
typedef CALLBACK_API_C( OSStatus , PMIOStatusProcPtr )(const void *jobContext, CFStringRef *status);
typedef CALLBACK_API_C( OSStatus , PMIOGetAttributeProcPtr )(const void *jobContext, CFStringRef attribute, CFTypeRef *result);
typedef CALLBACK_API_C( OSStatus , PMIOSetAttributeProcPtr )(const void *jobContext, CFStringRef attribute, CFTypeRef data);
typedef CALLBACK_API_C( OSStatus , PMIOCloseProcPtr )(const void *jobContext);

/* the printing manager maintains this struct of callback procs for printer module communication with the device */
struct PMIOProcs {
    CFIndex                         version;

	// GetConnInfoProc: Get connection type string and Printer Browser Module path
    GetConnInfoProcPtr             	GetConnInfoProc;

	// PMIOOpenProc: Open connection with target printer
    PMIOOpenProcPtr                 PMIOOpenProc;
	
	// PMIOReadProc: read data from printer
    PMIOReadProcPtr                 PMIOReadProc;
	
	// PMIOWriteProc: write data to printer.  Data is not buffered no matter how small the buffer is.
	// Therefore, it is recommended that the PM do its own buffering before this call is made.
    PMIOWriteProcPtr                PMIOWriteProc;
	
	// PMIOStatusProc: get status from the printer if any.
    PMIOStatusProcPtr               PMIOStatusProc;
	
	// PMIOGetAttributeProc: get the value for a particular IOM attribute (see PMIOModule.h for a list of attributes)
    PMIOGetAttributeProcPtr         PMIOGetAttributeProc;
	
	// PMIOSetAttributeProc: set a value for a particular IOM attribute (see PMIOModule.h for a list of attributes)
    PMIOSetAttributeProcPtr         PMIOSetAttributeProc;
	
	// PMIOCloseProc: close connection with printer.
    PMIOCloseProcPtr                PMIOCloseProc;

};
typedef struct PMIOProcs          	PMIOProcs;


/* PMProcs contains the routines required to be exported by a Printer Module. */
typedef struct  PMProcs
{
        /* The plugin header is required with all plugins and must proceed object's layout. */
    PMPlugInHeader          pluginHeader;
        
    /* The actual PM Module routine Procs */

    /* CreatePrinterBrowserModuleInfo: For a given connection type in 'connectionType', returns a ticket containing printer 
	browser information about the supported printers that can be browsed for on that connection. If the connection
	is not supported by the Printer Module, kPMUnsupportedConnection error is returned. */
    CALLBACK_API_C( OSStatus , CreatePrinterBrowserModuleInfo )( CFStringRef connectionType, CFArrayRef *printerBrowserInfo);

    /* Initialize: Create a new instance of the Printer Module and place it's reference in 'printerModuleContext'.  
	Few input parameters are passed via this API that the PM should store in its local context block for use
	during the session; such as: printerAddress, jobContext (used in callbacks), pmIOProcs (used for communicating with 
	the device, and pmNotificationProc (used for reporting status and errors). */
    CALLBACK_API_C( OSStatus , Initialize )( const CFDataRef  printerAddress, const void* jobContext, const PMIOProcs *pmIOProcs, const PMNotificationProcPtr pmNotificationProc, PMContext *printerModuleContext);

    /* CreatePrintingDialogExtensionsPaths: return one or more paths of this Printer Module's Print Dialog Extension(s) 
	relative to base path /Library/Printers/ */
    CALLBACK_API_C( OSStatus , CreatePrintingDialogExtensionsPaths )(PMContext printerModuleContext, CFArrayRef *pdePaths);

    /* CreatePrinterTickets: returns printer module's template and printerinfo tickets to the caller.  
	A PrinterInfo ticket holds capability and product ID information whereas
	a Template holds range and default information about various print settings */
    CALLBACK_API_C( OSStatus , CreatePrinterTickets )(PMContext printerModuleContext, PMTicketRef *printerInfo, PMTemplateRef *jobTemplate);

    /* BeginJob: Called by the Printing Manager to initiate a job. This function is intended as a
	"setup" function, so all the information needed to set up for printing is supplied: jobTicket has the control 
	parameters for this job, as defined by the application and user; converterSetp allows the PM to setup a converter 
	via standard ticket tags. */
    CALLBACK_API_C( OSStatus , BeginJob )(PMContext printerModuleContext, const void* jobContext, PMTicketRef jobTicket, PMTicketRef *converterSetup);

    /* PrintJob: Begin sending print data to the printer. The Printing Manager calls this API when page
	boundaries in the job can not be determined (i.e PM specific format).  inDataProcs contains callbacks to
	// access the print data; see PMJobStreamProcs definitions above for more info on the callback routines.  */
    CALLBACK_API_C( OSStatus , PrintJob )(PMContext printerModuleContext, const void* jobContext, PMTicketRef jobTicket, const PMJobStreamProcs *inDataProcs);

    /* PrintPage: Send only a specific page to the printer.  The PM needs to process the data and make it ready 
	for the printer hardware.  PMJobStreamGetNextBandProc is a callback to get the next available band data.*/
    CALLBACK_API_C( OSStatus , PrintPage)( PMContext printerModuleContext, const void* jobContext, PMTicketRef jobTicket, const PMJobStreamGetNextBandProcPtr pmJobStreamGetNextBandProc);

    /* ImageAccess: This API is called when an image is encountered during conversion.  This allows the Printer Module to access and modify
	the image data (imageRef) and drawing context before the image is rasterized into the page bands.  Modified image should be
	returned in outImageRefPtr. */
    CALLBACK_API_C( OSStatus , ImageAccess )( PMContext printerModuleContext, const void* jobContext, CFStringRef grafBase, PMDrawingCtx drawingCtx, PMImageRef imageRef, PMImageRef* outImageRefPtr );

    /* CancelJob: Cancel the currently printing job.  This function may be called while the PM is executing code in PrintJob or PrintPage. */
    CALLBACK_API_C( OSStatus , CancelJob )( PMContext printerModuleContext, const void* jobContext);
                                 
    /* EndJob: Finish up the previously printed job.  */
    CALLBACK_API_C( OSStatus , EndJob)( PMContext printerModuleContext, const void* jobContext);
	
    /* Terminate: dispose of the current PM session data allocated in Initialize. */
    CALLBACK_API_C( OSStatus , Terminate)(PMContext * printerModuleContext, const void* jobContext);

}PMProcs;

/* PM interface is an object containing addresses to the module's entry points: */

typedef struct PMInterface
{
    const PMProcs*      vtable;

}PMInterface;

typedef const PMInterface*  PMInterfaceRef;


// Paper names must all be ISO or PPD standard names, so we've defined constants here for 
// developers to use in their code, mostly to make things more readable.

#define USExecutiveEnvelope		CFSTR( "Executive" )
#define Envelope9				CFSTR( "na-number-9-envelope" )
#define Envelope10				CFSTR( "na-number-10-envelope" )
#define Envelope10x15			CFSTR( "na-10x15-envelope" )
#define EnvelopeB4				CFSTR( "iso-b4-envelope" )
#define EnvelopeB5				CFSTR( "iso-b5-envelope" )
#define EnvelopeC3				CFSTR( "iso-c3-envelope" )
#define EnvelopeC4				CFSTR( "iso-c4-envelope" )
#define EnvelopeC5				CFSTR( "iso-c5-envelope" )
#define EnvelopeC6				CFSTR( "iso-c6-envelope" )
#define Envelope6x9				CFSTR( "na-6x9-envelope" )
#define Envelope7x9				CFSTR( "na-7x9-envelope" )
#define Envelope9x11			CFSTR( "na-9x11-envelope" )
#define Envelope9x12			CFSTR( "na-9x12-envelope" )
#define Envelope10x13			CFSTR( "na-10x13-envelope" )
#define Envelope10x14			CFSTR( "na-10x14-envelope" )
#define EnvelopeMonarch			CFSTR( "monarch-envelope" )
#define EnvelopeLong			CFSTR( "iso-designated-long-envelope" )

#define Invoice					CFSTR( "invoice" )
#define USLetter				CFSTR( "na-letter" )
#define USLegal					CFSTR( "na-legal" ) 
#define Tabloid					CFSTR( "tabloid" )
#define Ledger					CFSTR( "ledger" )
#define Folio					CFSTR( "folio" )
#define Quarto					CFSTR( "quarto" )

#define A0						CFSTR( "iso-a0" )
#define A1						CFSTR( "iso-a1" )
#define A2						CFSTR( "iso-a2" )
#define A3						CFSTR( "iso-a3" )
#define A4						CFSTR( "iso-a4" )
#define A5						CFSTR( "iso-a5" )
#define A6						CFSTR( "iso-a6" )
#define A7						CFSTR( "iso-a7" )
#define A8						CFSTR( "iso-a8" )
#define A9						CFSTR( "iso-a9" )

#define B0						CFSTR( "iso-b0" )
#define B1						CFSTR( "iso-b1" )
#define B2						CFSTR( "iso-b2" )
#define B3						CFSTR( "iso-b3" )
#define B4						CFSTR( "iso-b4" )
#define B5						CFSTR( "iso-b5" )
#define B6						CFSTR( "iso-b6" )
#define B7						CFSTR( "iso-b7" )
#define B8						CFSTR( "iso-b8" )
#define B9						CFSTR( "iso-b9" )
#define B10						CFSTR( "iso-b10" )

#define JISB0					CFSTR( "jis-b0" )
#define JISB1					CFSTR( "jis-b1" )
#define JISB2					CFSTR( "jis-b2" )
#define JISB3					CFSTR( "jis-b3" )
#define JISB4					CFSTR( "jis-b4" )
#define JISB5					CFSTR( "jis-b5" )
#define JISB7					CFSTR( "jis-b7" )
#define JISB8					CFSTR( "jis-b8" )
#define JISB9					CFSTR( "jis-b9" )
#define JISB10					CFSTR( "jis-b10" )

#define ASize					CFSTR( "a" )
#define BSize					CFSTR( "b" )
#define CSize					CFSTR( "c" )
#define DSize					CFSTR( "d" )
#define ESize					CFSTR( "e" )

#define iso10					CFSTR( "iso-10" )

// A string to define the default paper name. See sample code for usage.

#define DefaultPaper			CFSTR( "DefaultPaperSize" )

#ifdef __cplusplus
}
#endif

#endif /* __PMPRINTERMODULE__ */

