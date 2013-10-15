/*
 File:       PMTicketDeprecated.h
 
 Contains:   Mac OS X Printing Manager Deprecated Job Ticket Interfaces.
 
 Version:    Technology: Mac OS X
 Release:    1.0
 
 Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 */
 
#ifndef __PMTICKETDEPRECATED__
#define __PMTICKETDEPRECATED__

#if !__LP64__

#ifdef __cplusplus
extern "C" {
#endif

#include <PrintCore/PMTicket.h>

#define kPMColorSyncMatchingStr		    "AP_ColorSyncColorMatching"
#define kPMColorSyncMatching		    CFSTR( kPMColorSyncMatchingStr )

#define kPMPSErrorOnScreenStr		kPMPrintSettingsPrelude "PMPSErrorOnScreen"
#define kPMPSErrorOnScreenKey		CFSTR( kPMPSErrorOnScreenStr )

#define kPMPageCustomDialogHdlStr           kPMPageFormatPrelude "CustomDialogRecord"
#define kPMPageCustomDialogHdlKey           CFSTR( kPMPageCustomDialogHdlStr )      	/* CFData - Handle to the print record using for custom dialog calls. Not stored when flattened. (OS8 Only) */

#define kPMQualityStr                       kPMPrintSettingsPrelude "PMQuality"
#define kPMQualityKey                       CFSTR( kPMQualityStr )                      /* CFNumber - kCFNumberSInt32Type, Enum, draft, normal, best */

#define kPMPaperTypeStr                     kPMPrintSettingsPrelude "PMPaperType"
#define kPMPaperTypeKey                     CFSTR( kPMPaperTypeStr )                    /* CFNumber - kCFNumberSInt32Type, Enum, draft, normal, best */

#define kPMPaperSourceStr                   kPMPrintSettingsPrelude "PMPaperSource"
#define kPMPaperSourceKey                   CFSTR( kPMPaperSourceStr )                  /* CFNUmber - kCFNumberSInt32Type, Enum, paper sources. */

#define kPMColorModeStr                     kPMPrintSettingsPrelude "PMColorMode"
#define kPMColorModeKey                     CFSTR( kPMColorModeStr )                    /* CFNumber - kCFNumberSInt32Type, Enum, B/W, Grayscale, Color, HiFi Color. */

#define kPMPrintScalingHorizontalStr        kPMPrintSettingsPrelude "PMScaling"
#define kPMPrintScalingHorizontalKey        CFSTR( kPMPrintScalingHorizontalStr )       /* CFNumber - kCFNumberDoubleType, Horizontal scaling factor applied to original page size. */

#define kPMPrintScalingVerticalStr          kPMPrintSettingsPrelude "PMVerticalScaling"
#define kPMPrintScalingVerticalKey          CFSTR( kPMPrintScalingVerticalStr )         /* CFNumber - kCFNumberDoubleType, Vertical scaling factor applied to original page size. */

#define kPMPrintScalingAlignmentStr         kPMPrintSettingsPrelude "PMScalingAlignment"
#define kPMPrintScalingAlignmentKey         CFSTR( kPMPrintScalingAlignmentStr )        /* CFNumber - kCFNumberSInt32Type, Enum (PMScalingAlignment) */

#define kPMPrintBackupRecordHdlStr          kPMPrintSettingsPrelude "BackupPrintRecordHandle"
#define kPMPrintBackupRecordHdlKey          CFSTR( kPMPrintBackupRecordHdlStr )         /* CFData - Print record handle, allowing easy access during most calls. Not used when flattened. (OS8 Only) */

#define kPMPrintBackupRecordDataStr         kPMPrintSettingsPrelude "BackupPrintRecord"
#define kPMPrintBackupRecordDataKey         CFSTR( kPMPrintBackupRecordDataStr )        /* CFData - Print record stored in complete form - used when flattening Ticket w/ record. (OS8 only) */

#define kPMPrintCustomDialogHdlStr          kPMPrintSettingsPrelude "CustomDialogRecord"
#define kPMPrintCustomDialogHdlKey          CFSTR( kPMPrintCustomDialogHdlStr )         /* CFData - Handle to the print record using for custom dialog calls. Not stored when flattened. (OS8 Only) */

#define kPMPrintOrientationStr              kPMPrintSettingsPrelude "PMOrientation"
#define kPMPrintOrientationKey              CFSTR( kPMPrintOrientationStr )             /* CFNumber - kCFNumberSInt32Type, PMOrientation, 1 = portrait, 2 = landscape, etc. */


/* Ticket: Converter Setup Ticket
    Contains controls for converter. Generally, the Printer Module and Job Manager will set
    tags in this ticket to control the various settings of the conversion process. 
*/
#define kPMConverterSetupPrelude            "com.apple.print.ConverterSetup."
#define kPMBandingRequestedStr              kPMConverterSetupPrelude "PMBandingRequested"
#define kPMBandingRequestedKey              CFSTR( kPMBandingRequestedStr )             /* CFBoolean, turns on banding if it's available. */
#define kPMRequiredBandHeightStr            kPMConverterSetupPrelude "PMRequiredBandHeight"
#define kPMRequiredBandHeightKey            CFSTR( kPMRequiredBandHeightStr )           /* CFNumber, number of scan lines needed for each band. Could be whole page, in which case banding is disabled. */
#define kPMDepthSwitchingEnabledStr         kPMConverterSetupPrelude "PMDepthSwitching"
#define kPMDepthSwitchingEnabledKey         CFSTR( kPMDepthSwitchingEnabledStr )        /* CFBoolean. If true, the printer module wants converter to switch between b/w bands and color bands when possible. */
#define kPMWhiteSkippingEnabledStr          kPMConverterSetupPrelude "PMWhiteSpaceSkipping"
#define kPMWhiteSkippingEnabledKey          CFSTR( kPMWhiteSkippingEnabledStr )         /* CFBoolean. If true, the printer module wants converter to skip over white space if possible. */
#define kPMConverterResHorizontalStr        kPMConverterSetupPrelude "PMConversionResHorizontal"
#define kPMConverterResHorizontalKey        CFSTR( kPMConverterResHorizontalStr )       /* CFNumber, CFNumberDoubleType indicating horizontal final rendering resolution. */
#define kPMConverterResVerticalStr          kPMConverterSetupPrelude "PMConversionResVertcial"
#define kPMConverterResVerticalKey          CFSTR( kPMConverterResVerticalStr )         /* CFNumber, CFNumberDoubleType indicating vertical final rendering resolution. */
#define kPMRequestedPixelFormatStr          kPMConverterSetupPrelude "PMPixelFormat"
#define kPMRequestedPixelFormatKey          CFSTR( kPMRequestedPixelFormatStr )         /* CFNumber, CFNumberLongType, indicates the pixel format requested of the converter. */
#define kPMRequestedPixelLayoutStr          kPMConverterSetupPrelude "PMPixelLayout"
#define kPMRequestedPixelLayoutKey          CFSTR( kPMRequestedPixelLayoutStr )         /* CFNumber, CFNumberLongType, indicates the pixel layout requested of the converter. */
#define kPMCVColorSyncProfileIDStr			kPMConverterSetupPrelude "PMProfileID"
#define kPMCVColorSyncProfileIDKey			CFSTR( kPMCVColorSyncProfileIDStr )			/* CFNumber, kCFNumberSInt32Type, the profile ID for the profile to be used with this job. */

/* Tickets may be locked by the printing system, so we provide a function to determine if */
/* the ticket is indeed locked. Any attempted changes to a locked ticket will result in */
/* "kPMTicketLocked" error. */
/* NOTE: Locking is deprecated in 10.5 and later.  . */
EXTERN_API_C( OSStatus )
PMTicketGetLockedState          (PMTicketRef            ticket,
                                 Boolean *              lockedState);

EXTERN_API_C( OSStatus )
PMTicketSetMetaItem             (PMTicketRef            ticket,
                                 CFStringRef            key,
                                 CFTypeRef              item);

EXTERN_API_C( OSStatus )
PMTicketGetMetaItem             (PMTicketRef            ticket,
                                 CFStringRef            key,
                                 CFTypeRef *            item);


/* A couple of functions that will help in managing the "locked" state of any ticket */
/* item. These functions only work for items directly stored in the current ticket, not */
/* for items in sub-tickets. NOTE: In MacOS 10.5 and later, locking is not supported. */
EXTERN_API_C( OSStatus )
PMTicketIsItemLocked            (PMTicketRef            ticket,
                                 CFStringRef            key,
                                 Boolean *              locked);

EXTERN_API_C( OSStatus )
PMTicketLockItem                (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key);

EXTERN_API_C( OSStatus )
PMTicketUnlockItem              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key);

// PPDDict is obsolete for 64 bit usage. 
EXTERN_API_C( OSStatus )
PMTicketGetPPDDict	            (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFMutableDictionaryRef	*dict);

EXTERN_API_C( OSStatus )
PMSessionGetTicketFromSession( PMPrintSession session, CFStringRef key, PMTicketRef* theTicket );

EXTERN_API_C( OSStatus )
PMSessionGetTemplateFromSession( PMPrintSession session, CFStringRef key, PMTemplateRef* theTemplate );

#ifdef __cplusplus
}
#endif


#endif /* !__LP64 */

#endif // __PMTICKETDEPRECATED__
