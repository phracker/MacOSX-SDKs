/*
     File:       PMIOModule.h
 
     Contains:   Mac OS X Printing Manager IO Module Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __PMIOMODULE__
#define __PMIOMODULE__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFString.h>
#include <PrintCore/PMTicket.h>
#include <PrintCore/PMPluginHeader.h>
#include <PrintCore/PMErrors.h>

#ifdef __cplusplus
extern "C" {
#endif

/* context ID for IO Modules */
typedef struct OpaqueIOMContext*        IOMContext;

/* kPMPrinterURI corresponds to a CFString to a connection-specific 
address specification for the printer. For instance, on an lpd connection  
this would be an address of the form lpd://<host>/<queue name>. */
#define	kPMPrinterURI					CFSTR("Printer URI")

/* System-supported connection type names used in identifying the different connection types
and for requesting lookup information from Printer Modules. PrintCenter does not use these 
strings in its UI, instead it gets the actual UI strings from the Printer Browser Module. */
#define   kPMAppleTalkConnection        CFSTR("AppleTalk")
#define   kPMUSBConnection          	CFSTR("USB")
#define   kPMLPRConnection          	CFSTR("LPR")
#define   kPMDirServicesConnection      CFSTR("Directory Services")
#define	  kPMDNSSDConnection			CFSTR("DNSSD")
#define	  kPMBluetoothConnection		CFSTR("Bluetooth")

/* possible attributes that can be requested from an IO Module and allow clients to determine various 
characteristics about the IOM, its connection type, and the target printer.  The same attribute can 
be used for getting a value or setting it. */
#define     kPMBiDiAttr                 CFSTR("Supports BiDirectional Communication")	/* bi-directional communication capability */
#define     kPM8BitChannelAttr          CFSTR("Supports 8-bit Channel")					/* full 8-bit per byte data (vs. 7) */	
#define     kPMTransparentByteRange     CFSTR("Supports Transparent Byte Range")		/* transparent byte range */
#define     kPMJobIDAttr                CFSTR("Supports JobID")							/* in-printer-jobID	*/	
#define     kPMTimeoutAttr              CFSTR("Supports Timeout")						/* get/set timeout duration */
#define     kPMTStatusAttr              CFSTR("Supports T Status Request")				/* status on the T channel */

/* Used with the IOMGetAttribute call, a supporting IO Module will hand back
 * a copy of a CFStringRef describing the last error encountered. If there was
 * no last error, or if there is no available string then NULL is passed back.
 */
#define	    kPMLastErrorStrAttr		CFSTR("Last Error")


/* Type ID, interface ID for the IOM CFPlugin */
#define  kIOModuleTypeIDStr     "EE5A5E5C-C2DD-11D3-84B5-00050209D9C1"
#define  kIOModuleIntfIDStr     "F4F7510C-C2DD-11D3-93A5-00050209D9C1"

/* IOM API version numbers (see PMPluginHeader.h for the meaning of these defintions) */
#define  kIOMBuildVersionMajor  1
#define  kIOMBuildVersionMinor  0
#define  kIOMBaseVersionMajor   1
#define  kIOMBaseVersionMinor   0


/* IOMProcs contains the routines required to be exported by an IOM Module. */
typedef struct  IOMProcs
{
	// The plugin header is required with all plugins and must proceed object's layout.
    PMPlugInHeader              pluginHeader;
        
    // The actual IO Module routine Procs
	
	// GetConnectionInfo: returns the connection type and the path to the companion browser module
        // relative to the IOM 
        // The connection types: AppleTalk, USB, LPR, and Directory Services are reserved by Apple.
    CALLBACK_API_C( OSStatus , GetConnectionInfo )(CFStringRef *connectionType, CFStringRef *pbmPath);

	// Initialize: creates a context to store local variables during an IO session.  printerAddress of
	// the target printer is passed as CFDataRef as defined by the protocol and set by the Printer Browser Module
    CALLBACK_API_C( OSStatus , Initialize )(const CFDataRef printerAddress, IOMContext *ioModuleContextPtr);

	// Open: open IO connection with the target device.  The parameter buffSize is set
	// by the IOM to return its maximum write buffer size.
    CALLBACK_API_C( OSStatus , Open )(IOMContext ioModuleContext, PMTicketRef jobTicket, UInt32 *bufferSize);

	// Read: read data from the device over the read channel, if any.  
    CALLBACK_API_C( OSStatus , Read )(IOMContext ioModuleContext, Ptr buffer, UInt32 *size, Boolean *eoj);

	// Write: write data to the device
    CALLBACK_API_C( OSStatus , Write )(IOMContext ioModuleContext, Ptr buffer, UInt32 *size, Boolean eoj);

	// Status: get status from the device
    CALLBACK_API_C( OSStatus , Status )(IOMContext ioModuleContext, CFStringRef *status);

	// GetAttribute: checks if a defined IO attribute is supported by the target IO connection.  If the requested 
	// 'attribute' is supported and available, it's returned in 'result'.  If supported but not available, error code 
	// kAttrNotAvailable is returned.  If the attribute is not supported, kPMNotImplemented is returned.
    CALLBACK_API_C( OSStatus , GetAttribute )(IOMContext ioModuleContext, CFStringRef attribute, CFTypeRef *result);

	// SetAttribute: sets a pre-defined 'attribute' to a given value passed in 'data'.  Only supported attributes
	// can be set; otherwise kAttrNotAvailable or kPMNotImplemented is returned.
    CALLBACK_API_C( OSStatus , SetAttribute )(IOMContext ioModuleContext, CFStringRef attribute, CFTypeRef data);

	// Close: close IO connection with the target device.  The parameter 'abort' indicates whether the current job
	// is to be canceled before closing connection (true; i.e. user cancels) or not (false; i.e. normal job completion).
    CALLBACK_API_C( OSStatus , Close )(IOMContext ioModuleContext, Boolean abort);

	// Terminate: dispose of any data allocated in Initialize.
    CALLBACK_API_C( OSStatus , Terminate )(IOMContext *ioModuleContextPtr);

} IOMProcs;

// IOM interface is an object containing addresses to the module's entry points:
typedef struct
{
    const IOMProcs* vtable;

} IOMInterface;

typedef const IOMInterface*     IOMInterfaceRef;

#ifdef __cplusplus
}
#endif

#endif /* __PMIOMODULE__ */

