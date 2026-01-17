/*
     File:       PMPrintingDialogExtensions.h
 
     Contains:   Mac OS X Printing Manager Print Dialog Extensions' Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
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

#if !__LP64__
#include <Print/PMPrintingDialogExtensionsDeprecated.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Constants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
#define kPMColorMatchingPDEKindID       CFSTR("com.apple.print.pde.ColorMatchingKind")
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

/* Key to represent information about display order for Cocoa summary info */
#define	SUMMARY_DISPLAY_ORDER		CFSTR("Summary Display Order")


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Type Definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Basic types...
*/

/* Type and Interface IDs. */
#define kDialogExtensionIntfIDStr			CFSTR("A996FD7E-B738-11D3-8519-0050E4603277")
#define kGeneralPageSetupDialogTypeIDStr	CFSTR("6E6ED964-B738-11D3-952F-0050E4603277")
#define kGeneralPrintDialogTypeIDStr		CFSTR("C1BF838E-B72A-11D3-9644-0050E4603277")
#define kAppPageSetupDialogTypeIDStr		CFSTR("B9A0DA98-E57F-11D3-9E83-0050E4603277")
#define kAppPrintDialogTypeIDStr			CFSTR("BCB07250-E57F-11D3-8CA6-0050E4603277")
#define kAppPrintThumbnailTypeIDStr			CFSTR("9320FE03-B5D5-11D5-84D1-003065D6135E")
#define kPrinterModuleTypeIDStr				CFSTR("BDB091F4-E57F-11D3-B5CC-0050E4603277")


#ifdef __cplusplus
}
#endif

#endif /* __PMPRINTINGDIALOGEXTENSIONS__ */
