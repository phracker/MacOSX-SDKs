/*
     File:       PMTicket.h
 
     Contains:   Mac OS X Printing Manager Job Ticket Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMTICKET__
#define __PMTICKET__

#ifndef	__PMERRORS__
#include <PrintCore/PMErrors.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* SECTION I: DATA TYPES, STUCTURES, and CONSTANTS */
/* General opaque Ticket object reference. This is returned when you create a PageFormat, */
/* PrintSettings, DocumentInfo, JobInfo, or JobTicket. A list of Job Tickets or other */
/* tickets can be saved as a list of references. */
typedef struct OpaquePMTicketRef*       PMTicketRef;
typedef struct OpaquePMTemplateRef*     PMTemplateRef;
/* Constant that will be useful in calling Job Ticket functions. */
#define kPMDontFetchItem    NULL            /* Used to ask GetItem if an item exists. */

/* The following constant determines if the ticket code sets an item in the top level ticket */
/* or down in some sub-ticket within the top level ticket. If passed as the document number, */
/* the ticket code will simply set the item in the ticket passed. If the document number is */
/* non "kTopLevel" but the page number is "kTopLevel", the ticket code will set the item in the */
/* document level sub-ticket. If both parameters are non "kTopLevel", the ticket code will set */
/* the item in the correct sub ticket for the document and page. */
/* For now, all calls should use kPMTopLevel for document and page numbers, or the passed in */
/* docment and page numbers if they are available. In the future we expect to enable embedded */
/* document and page tickets. */
#define kPMTopLevel ((UInt32)0)

/* There are several different types of tickets that use the same accessor functions and  */
/*  allow the programmer to use different keys to access the proper fields in each ticket. */
/*      A Job Ticket has the following structure: */
/*          Job Ticket */
/*              Job Ticket Fields */
/*              Page Format Ticket (required) */
/*                  Paper Info Ticket (required) */
/*              Print Settings Ticket (required) */
/*                  Paper Info Ticket (required) */

/* DOWNSTREAM TICKETS - Heading from PC or PJC to other modules. */
#define kPMJobTicket                CFSTR( "com.apple.print.JobTicket" )
#define kPMDocumentTicket           CFSTR( "com.apple.print.DocumentTicket" )
#define kPMPageTicket               CFSTR( "com.apple.print.PageTicket" )
#define kPMPageFormatTicket         CFSTR( "com.apple.print.PageFormatTicket" )
#define kPMPrintSettingsTicket      CFSTR( "com.apple.print.PrintSettingsTicket" )
#define kPMDestinationTicket        CFSTR( "com.apple.print.DestinationTicket" )
#define kPMConverterSetupTicket     CFSTR( "com.apple.print.ConverterSetupTicket" )

/* UPSTREAM TICKETS - Expected to be created by low level modules and passed up. */
#define kPMPrinterInfoTicket        CFSTR( "com.apple.print.PrinterInfoTicket" )
#define kPMModuleInfoTicket         CFSTR( "com.apple.print.ModuleInfoTicket" )

/* OTHER TICKETS, going either direction */
#define kPMTicketList               CFSTR( "com.apple.print.TicketList" ) 
#define kPMPaperInfoTicket          CFSTR( "com.apple.print.PaperInfoTicket" ) 
/* An enum to keep track in a programmatic way of which type of ticket we're working */
/* with. These do not need to match up with the order of tickets listed in the ticket */
/* types in PMTicket.h because we convert from string to enum in an internal function. */
/* NOTE: If this list is added to, a couple different functions in PMTicket.c and */
/*       PMTicketInternal.c need to be updated. */
/* Warning: Don't user these tags when creating tickets.  Use the CFSTRs above. */

typedef SInt16 PMTicketType;
enum {
    kPMTicketTypeUnknown        = -1,
    kPMJobTicketType            = 1,
    kPMDocumentTicketType       = 2,
    kPMPageTicketType           = 3,
    kPMPageFormatTicketType     = 4,
    kPMPrintSettingsTicketType  = 5,
    kPMPrinterInfoTicketType    = 6,
    kPMDestinationTicketType    = 7,
    kPMConverterSetupTicketType = 8,
    kPMModuleInfoTicketType     = 9,
    kPMTicketListType           = 10,
    kPMPaperInfoTicketType      = 11
};

typedef SInt16 PMTicketErrors;

/* BATCH PROCESSING ENUMS AND STRUCTURES  */
/* - Look in this section for help creating statically defined tickets. */
/* We have the ability to create a Ticket from an array of key/item pairs that define */
/* the keys and items for the entries in the ticket. To facilitate easy conversion of */
/* these key/item pairs, we've defined a few constants to help in the batch processing of */
/* these arrays. These are basically key types that are allowed for batch processing. */

typedef UInt16 PMTicketItemType;
enum {
    kPMItemInvalidType          = 0,
    kPMItemCStringType          = 1,                            /* a C string pointed to by a char* */
    kPMItemSInt32Type           = 2,                            /* a C signed 32 bit integer. */
    kPMItemBooleanType          = 3,                            /* A Boolean */
    kPMItemCStrListType         = 4,                            /* A list of c-strings. */
    kPMItemPMRectType           = 5,                            /* A pointer to a PMRect */
    kPMItemSInt32ListType       = 6,                            /* A pointer to a SInt32List */
    kPMItemPMRectListType       = 7                             /* A pointer to a PMRectList */
};


/* A structure that holds a list of CString pointers, along with a definition for a constant list. */

struct CStrList {
    SInt32                          count;                      /* Number of CString pointers in the array. */
    const char **                   strArray;                   /* Pointer to first CString pointer. */
};
typedef struct CStrList                 CStrList;

typedef const CStrList                  ConstCStrList;
/* A structure to hold a list of Signed 32 bit integers.  */

struct SInt32List {
    SInt32                          count;                      /* Number of Signed 32 bit values in array. */
    const SInt32 *                  sInt32Array;                /* Pointer to the first 32 bit value in array. */
};
typedef struct SInt32List               SInt32List;

typedef const SInt32List                ConstSInt32List;
/* A structure to hold a list of PMRect structures. PMRect is defined in PMDefinitions.h */
/* and is basically a set of four doubles (top, left, bottom, and right). */

struct PMRectList {
    SInt32                          count;                      /* Number of PMRect pointers in the array. */
    const PMRect **                 pmRectArray;                /* Pointer to the first PMRect pointer. */
};
typedef struct PMRectList               PMRectList;

typedef const PMRectList                ConstPMRectList;
/* CF types can't be statically initialized, but CString and Pascal strings can be. */
/* We have created utilities to convert from static C and Pascal based data into CF types. */
/* The structure below will serve as a statically defined "Ticket Item" that can then be */
/* converted into a job ticket item. An array of these structures would be made into a ticket. */

struct PMTicketItemStruct {
    char *                          key;                        /* The CString for the key. */
    PMTicketItemType                itemType;                   /* What type of item is being defined in union below. */
    Boolean                         locked;                     /* Can other callers change this after it's entered in a ticket? */
    union {                                                     /* The item data itself. */
        const void *                    GenericData;            /* Generic data */
        const char *                    cString;                /* kPMItemCStringType */
        SInt32                          sInt32;                 /* kPMItemSInt32Type */
        UInt32                          boolean;                /* kPMItemBooleanType */
        ConstCStrList *                 cStrlist;               /* kPMItemCStrListType */
        PMRect *                        rect;                   /* kPMItemPMRectType */
        ConstSInt32List *               sInt32List;             /* kPMItemSInt32ListType */
        ConstPMRectList *               pmRectList;             /* kPMItemPMRectListType */
    }                                 value;
};
typedef struct PMTicketItemStruct       PMTicketItemStruct;
/* END OF BATCH PROCESSING ENUMS AND STRUCTURES */

/* ENUMS for Ticket Values */

/* The values for kPMCoverPageKey */

enum {
	kPMCoverPageNone = 1,	
	// Print a cover page before printing the document.
    kPMCoverPageBefore = 2,
	// Print a cover page after printing the document.
	kPMCoverPageAfter = 3
};
/* If the kPMDuplexingKey is not in a ticket then kPMDuplexDefault should be assumed.
 */
#define	kPMCoverPageDefault	(kPMCoverPageNone)

// Values for the kPMPSErrorHandlerKey 
enum {
	kPSNoErrorHandler		=	0,
	kPSErrorHandler			=	1
};

/* If the kPMCopyCollateKey is not present, then kPMCopyCollateDefault should be assumed. */
#define kPMCopyCollateDefault	(true)



/* END OF SECTION I: DATA TYPES, STUCTURES, and CONSTANTS */


/* SECTION II: TICKET KEYS */
/* - Look in this section for particular predefined keys for various tickets. */
/* Each key is defined to store it's data as a particular CF type, but there are some  */
/*  utilities defined to fetch data in different formats. For instance, it would be simple */
/*  to read in the Job Name as a CFString, or as a 'C' string. */

/* Ticket: PAPER INFO TICKET
    This ticket contains a single Paper Info set, with all the information necessary to 
    describe a paper type available from the Printer Module.
*/
#define kPMPaperInfoPrelude                 "com.apple.print.PaperInfo."
#define kPMPaperNameStr                     kPMPaperInfoPrelude "PMPaperName"
#define kPMPaperNameKey                     CFSTR( kPMPaperNameStr )                    /* CFString for the iso name of the paper, e.g. na-letter */
#define kPMPPDPaperNameStr					kPMPaperInfoPrelude "ppd.PMPaperName"
#define kPMPPDPaperNameKey                  CFSTR( kPMPPDPaperNameStr )                 /* CFString intended to be the ppd code name for the paper, e.g Letter */

/* The kPMPPDPaperCodeNameKey key stores a CFStringRef which is the true PPD code name for a paper. May not be available for some papers. Only available for
papers created on Mac OS X 10.5 and later. */
#define kPMPPDPaperCodeNameStr	"PMPPDPaperCodeName"
#define kPMPPDPaperCodeNameKey	CFSTR( kPMPPDPaperCodeNameStr )
	
#define kPMUnadjustedPaperRectStr			kPMPaperInfoPrelude "PMUnadjustedPaperRect"
#define kPMUnadjustedPaperRectKey           CFSTR( kPMUnadjustedPaperRectStr )          /* CFArray of 4 CFNumbers of kCFNumberDoubleType for paper size in points. */
#define kPMUnadjustedPageRectStr            kPMPaperInfoPrelude "PMUnadjustedPageRect"
#define kPMUnadjustedPageRectKey            CFSTR( kPMUnadjustedPageRectStr )           /* CFArray of 4 CFNumbers of kCFNumberDoubleType for page size within the paper, in points. */
#define kPMMatchPaperStr            		kPMPaperInfoPrelude "PMMatchPaper"
#define kPMMatchPaperKey            		CFSTR( kPMMatchPaperStr )           		/* CFBoolean tells if we need to find a closest match for this paper */
#define kPMConstrainedPaperStr            	kPMPaperInfoPrelude "PMConstrainedPaper"
#define kPMConstrainedPaperKey            	CFSTR( kPMConstrainedPaperStr )           	/* CFBoolean tells if this paper is constrained */
#define kPMCustomPaperStr            	kPMPaperInfoPrelude "PMCustomPaper"
#define kPMCustomPaperKey            	CFSTR( kPMCustomPaperStr )           	/* CFBoolean tells if this paper is a custom paper */

/* Ticket: PAGE FORMAT TICKET
    Describes the application's drawing environment, including resolution, scaling, and
    orientation. All information in the page format ticket is saved with the user's document,
    so the single paper info stored inside the page format ticket describes the logical page
    an application may draw to. This logical page is then mapped to a physical page defined
    in the Print Settings Ticket.
*/
#define kPMPageFormatPrelude                "com.apple.print.PageFormat."
#define kPMAdjustedPaperRectStr             kPMPageFormatPrelude "PMAdjustedPaperRect"
#define kPMAdjustedPaperRectKey             CFSTR( kPMAdjustedPaperRectStr )            /* CFArray of 4 CFNumbers of kCFNumberDoubleType for scaled and rotated page rectangle. */
#define kPMAdjustedPageRectStr              kPMPageFormatPrelude "PMAdjustedPageRect"
#define kPMAdjustedPageRectKey              CFSTR( kPMAdjustedPageRectStr )             /* CFArray of 4 CFNumbers of kCFNumberDoubleType for scaled and rotated page rectangle, in points. */
#define kPMDrawingResHorizontalStr          kPMPageFormatPrelude "PMHorizontalRes"
#define kPMDrawingResHorizontalKey          CFSTR( kPMDrawingResHorizontalStr )         /* CFNumber - kCFNumberDoubleType, Drawing resolution in horizontal direction. */
#define kPMDrawingResVerticalStr            kPMPageFormatPrelude "PMVerticalRes"
#define kPMDrawingResVerticalKey            CFSTR( kPMDrawingResVerticalStr )           /* CFNumber - kCFNumberDoubleType, Drawing resolution in vertical direction. */
#define kPMPageScalingHorizontalStr         kPMPageFormatPrelude "PMScaling"
#define kPMPageScalingHorizontalKey         CFSTR( kPMPageScalingHorizontalStr )        /* CFNumber - kCFNumberDoubleType, Horizontal scaling factor applied to original page size - 1 = 100% */
#define kPMPageScalingVerticalStr           kPMPageFormatPrelude "PMVerticalScaling"
#define kPMPageScalingVerticalKey           CFSTR( kPMPageScalingVerticalStr )          /* CFNumber - kCFNumberDoubleType, Vertical scaling factor applied to original page size - 1 = 100%. */
#define kPMPageOrientationStr               kPMPageFormatPrelude "PMOrientation"
#define kPMPageOrientationKey               CFSTR( kPMPageOrientationStr )              /* CFNumber - kCFNumberSInt32Type, PMOrientation, 1 = portrait, 2 = landscape, 3 = reverse portrait, 4 = reverse landscape. */
#define kPMFormattingPrinterStr          	kPMPageFormatPrelude "FormattingPrinter"
#define kPMFormattingPrinterKey          	CFSTR( kPMFormattingPrinterStr )      		/* CFString - name of the formating printer */

/* Ticket: PRINT SETTINGS TICKET
    Contains the user's print dialog selections. Includes items set by the application to
    further refine the output produced on the printer. Information in this ticket may also
    be saved with the decument, but are likely to be overwritten by any saved settings. 
    Logical page information is mapped to the physical page defined in this ticket.
*/
#define kPMPrintSettingsPrelude             "com.apple.print.PrintSettings."
#define kPMDestinationTypeStr               kPMPrintSettingsPrelude "PMDestinationType"
#define kPMDestinationTypeKey               CFSTR( kPMDestinationTypeStr )              /* CFNumber, kCFNumberSInt32Type kPMDestinationPrinter kPMDestinationFile kPMDestinationFax. */
#define kPMOutputFilenameStr                kPMPrintSettingsPrelude "PMOutputFilename"
#define kPMOutputFilenameKey                CFSTR( kPMOutputFilenameStr )               /* CFString - URL for the output filename. */
#define kPMCopiesStr                        kPMPrintSettingsPrelude "PMCopies"
#define kPMCopiesKey                        CFSTR( kPMCopiesStr )                       /* CFNumber, kCFNumberSInt32Type, number of copies to print. */
#define kPMCopyCollateStr                   kPMPrintSettingsPrelude "PMCopyCollate"
#define kPMCopyCollateKey                   CFSTR( kPMCopyCollateStr )                  /* CFBoolean, Turns on collating */
#define kPMOutputOrderStr		   "OutputOrder"
#define kPMOutputOrderKey		    CFSTR(kPMOutputOrderStr)			/* CFString, Reverse or Normal. default is Printer Specific */

#define kPMPageSetStr		   	    "page-set"
#define kPMPageSetKey			    CFSTR(kPMPageSetStr)	/* CFString, even, odd, or all. default is all */

#define kPMPageRangeStr                     kPMPrintSettingsPrelude "PMPageRange"
#define kPMPageRangeKey                     CFSTR( kPMPageRangeStr )                    /* CFArray of kCFNumberSInt32Type, each pair indicating valid range of pages that the application is able to print. Does not signify user choices. */
#define kPMFirstPageStr                     kPMPrintSettingsPrelude "PMFirstPage"
#define kPMFirstPageKey                     CFSTR( kPMFirstPageStr )                    /* CFNumber - kCFNumberSInt32Type, first page selected by user to print. */
#define kPMLastPageStr                      kPMPrintSettingsPrelude "PMLastPage"
#define kPMLastPageKey                      CFSTR( kPMLastPageStr )                     /* CFNumber - kCFNumberSInt32Type, last page selected by user to print. */
#define kPMPrintSelectionOnlyStr            kPMPrintSettingsPrelude "PMPrintSelectionOnly"
#define kPMPrintSelectionOnlyKey            CFSTR( kPMPrintSelectionOnlyStr )            /* CFBoolean - True if only current selection should be printed. */
#define kPMBorderStr                        kPMPrintSettingsPrelude "PMBorder"
#define kPMBorderKey                        CFSTR( kPMBorderStr )                       /* CFBoolean - If true, we do borders. */
#define kPMBorderTypeStr                    kPMPrintSettingsPrelude "PMBorderType"
#define kPMBorderTypeKey                    CFSTR( kPMBorderTypeStr )                   /* CFNumber - kCFNumberSInt32Type, Enum (PMBorderType) */
#define kPMLayoutNUpStr                     kPMPrintSettingsPrelude "PMLayoutNUp"
#define kPMLayoutNUpKey                     CFSTR( kPMLayoutNUpStr )                    /* CFBoolean, Turns on N-Up layout. */
#define kPMLayoutRowsStr                    kPMPrintSettingsPrelude "PMLayoutRows"
#define kPMLayoutRowsKey                    CFSTR( kPMLayoutRowsStr )                   /* CFNumber - kCFNumberSInt32Type, indicates number of layout rows. */
#define kPMLayoutColumnsStr                 kPMPrintSettingsPrelude "PMLayoutColumns"
#define kPMLayoutColumnsKey                 CFSTR( kPMLayoutColumnsStr )                /* CFNumber - kCFNumberSInt32Type, indicates number of layout columns. */
#define kPMLayoutDirectionStr               kPMPrintSettingsPrelude "PMLayoutDirection"
#define kPMLayoutDirectionKey               CFSTR( kPMLayoutDirectionStr )              /* CFNumber - kCFNumberSInt32Type, Enum (PMLayoutDirection) */
#define kPMLayoutTileOrientationStr         kPMPrintSettingsPrelude "PMLayoutTileOrientation"
#define kPMLayoutTileOrientationKey         CFSTR( kPMLayoutTileOrientationStr )        /* CFNumber - kCFNumberSInt32Type, PMOrientation, 1 = portrait, 2 = landscape, etc. */
#define kPMJobStateStr                      kPMPrintSettingsPrelude "PMJobState"
#define kPMJobStateKey                      CFSTR( kPMJobStateStr )                     /* CFNumber - kCFNumberSInt32Type, Enum, active = 0, pending, hold until, hold indefinitely, aborted, finished */
#define kPMJobHoldUntilTimeStr              kPMPrintSettingsPrelude "PMJobHoldUntilTime"
#define kPMJobHoldUntilTimeKey              CFSTR( kPMJobHoldUntilTimeStr )             /* CFDate - Time we expect to print the job. */
#define kPMJobPriorityStr                   kPMPrintSettingsPrelude "PMJobPriority"
#define kPMJobPriorityKey                   CFSTR( kPMJobPriorityStr )                  /* CFNumber - kCFNumberSInt32Type, Enum, Low = 0, normal, urgent */
#define kPMDuplexingStr                     kPMPrintSettingsPrelude "PMDuplexing"
#define kPMDuplexingKey                     CFSTR( kPMDuplexingStr )                    /* CFNumber - kCFNumberSInt32Type, Enum, kPMDuplexNone,  kPMDuplexNoTumble, kPMDuplexTumble, kPMSimplexTumble */
#define kPMDuplexingRequiresFlippedMarginAdjustStr   kPMPrintSettingsPrelude "PMDuplexingRequiresFlippedMargins"
#define kPMDuplexingRequiresFlippedMarginAdjustKey CFSTR( kPMDuplexingRequiresFlippedMarginAdjustStr )	
                                                                                        /* CFBoolean indicating, when duplexing and the OS is flipping
                                                                                            the coordinate system to provide support for the destination
                                                                                            tumble mode, whether the raster supplied to the printer
                                                                                            should begin at a different distance from the top of the sheet
                                                                                            than is normally generated. */
#define kPMHasCustomDuplexPDEStr   			kPMPrintSettingsPrelude "HasCustomDuplexPDE"
#define kPMHasCustomDuplexPDEKey 			CFSTR( kPMHasCustomDuplexPDEStr )	
                                                                                        /* CFBoolean indicating that the Tioga Printer Module has its own Duplex PDE. */
#define kPMColorSpaceModelStr                     kPMPrintSettingsPrelude "PMColorSpaceModel"
#define kPMColorSpaceModelKey                     CFSTR( kPMColorSpaceModelStr )                    /* CFNumber - kCFNumberSInt32Type, Enum, see PMColorSpaceModel. */
#define kPMColorSyncProfileIDStr            kPMPrintSettingsPrelude "PMColorSyncProfileID"
#define kPMColorSyncProfileIDKey            CFSTR( kPMColorSyncProfileIDStr )           /* CFNumber - kCFNumberSInt32Type, ID of profile to use. */
#define kPMPreviewStr                       kPMPrintSettingsPrelude "PMPreview"
#define kPMPreviewKey                       CFSTR( kPMPreviewStr )                      /* CFString - YES means the user clicked on the Preview button */
#define kPMPrimaryPaperFeedStr				kPMPrintSettingsPrelude "PMPrimaryPaperFeed"
#define kPMPrimaryPaperFeedKey				CFSTR( kPMPrimaryPaperFeedStr )				/* CFArray - main & option PPD key for input paper feed */
#define kPMSecondaryPaperFeedStr			kPMPrintSettingsPrelude "PMSecondaryPaperFeed"
#define kPMSecondaryPaperFeedKey			CFSTR( kPMSecondaryPaperFeedStr )			/* CFArray - main & option PPD key for input paper feed */
#define kPMPSErrorHandlerStr				kPMPrintSettingsPrelude "PMPSErrorHandler"
#define kPMPSErrorHandlerKey				CFSTR( kPMPSErrorHandlerStr )				/* CFNumber - kCFNumberSInt32Type  */
#define kPMPSTraySwitchStr					kPMPrintSettingsPrelude "PMPSTraySwitch"
#define kPMPSTraySwitchKey					CFSTR( kPMPSTraySwitchStr )					/* CFArray - main & option PPD key for tray switching */

#define kPMTotalBeginPagesStr		    		kPMPrintSettingsPrelude "PMTotalBeginPages"
#define kPMTotalBeginPagesKey		    	CFSTR( kPMTotalBeginPagesStr )			/* CFNumber the total number of times beginpage was called */
#define kPMTotalSidesImagedStr		    		kPMPrintSettingsPrelude "PMTotalSidesImaged"
#define kPMTotalSidesImagedKey		    	CFSTR( kPMTotalSidesImagedStr )			/* CFNumber the total number of sides that will printed. Does not take into account duplex and collation */

#define kPMFaxNumberStr						"phone"
#define kPMFaxNumberKey		    			CFSTR( kPMFaxNumberStr )			/* CFString - fax number to dial */
#define kPMFaxToStr							"faxTo"
#define kPMFaxToKey		    				CFSTR( kPMFaxToStr )				/* CFString - entire fax to line */
#define kPMFaxPrefixStr						"faxPrefix"
#define kPMFaxPrefixKey		    			CFSTR( kPMFaxPrefixStr )			/* CFString - fax prefix to dial */
#define kPMFaxSubjectStr					"faxSubject"
#define kPMFaxSubjectKey		    		CFSTR( kPMFaxSubjectStr )			/* CFString - fax subject linee*/
#define kPMFaxCoverSheetStr					"faxCoverSheet"
#define kPMFaxCoverSheetKey			   		CFSTR( kPMFaxCoverSheetStr )		/* CFString - fax cover sheet */
#define kPMFaxCoverSheetMessageStr			"faxCoverSheetMessage"
#define kPMFaxCoverSheetMessageKey	   		CFSTR( kPMFaxCoverSheetMessageStr )	/* CFString - fax cover sheet message*/
#define kPMFaxToneDialingStr				"faxToneDialing"
#define kPMFaxToneDialingKey		   		CFSTR( kPMFaxToneDialingStr )		/* CFString - fax use tone dialing */
#define kPMFaxUseSoundStr					"faxUseSound"
#define kPMFaxUseSoundKey		    		CFSTR( kPMFaxUseSoundStr )			/* CFString - fax use sound */
#define kPMFaxWaitForDialToneStr			"faxWaitForDialTone"
#define kPMFaxWaitForDialToneKey		    CFSTR( kPMFaxWaitForDialToneStr )	/* CFString - fax wait for dial tone */

#define kPMFaxToLabelStr					"faxToLabel"
#define kPMFaxToLabelKey					CFSTR( kPMFaxToLabelStr )			/* CFString - To: label */
#define kPMFaxFromLabelStr					"faxFromLabel"
#define kPMFaxFromLabelKey					CFSTR( kPMFaxFromLabelStr )			/* CFString - From: label */
#define kPMFaxDateLabelStr					"faxDateLabel"
#define kPMFaxDateLabelKey					CFSTR( kPMFaxDateLabelStr )			/* CFString - Date: label */
#define kPMFaxSubjectLabelStr				"faxSubjectLabel"
#define kPMFaxSubjectLabelKey				CFSTR( kPMFaxSubjectLabelStr )		/* CFString - Subject: label */
#define kPMFaxSheetsLabelStr				"faxSheetsLabel"
#define kPMFaxSheetsLabelKey				CFSTR( kPMFaxSheetsLabelStr )		/* CFString - Sheets to Follow: label */



#define kPMCoverPageStr                     kPMPrintSettingsPrelude "PMCoverPage"
#define kPMCoverPageKey                     CFSTR( kPMCoverPageStr )                    /* CFNumber - kCFNumberSInt32Type, Enum, kPMCoverPageNone,  kPMCoverPageBefore, kPMCoverPageAfter */
#define kPMCoverPageSourceStr				kPMPrintSettingsPrelude "PMCoverPageSource"
#define kPMCoverPageSourceKey				CFSTR( kPMCoverPageSourceStr )				/* CFArray - main & option PPD key for cover page paper source */

#define kPMDestinationPrinterIDStr		"DestinationPrinterID"
#define kPMDestinationPrinterIDKey		CFSTR( kPMDestinationPrinterIDStr )	/* CFStringRef - the printer ID corresponding to the destination printer */


/* Ticket: PAGE TICKET
    Future Feature. Intended to hold Page Format and Print Settings ticket for a single
    page of the document. Not yet implemented.
*/
#define kPMPageTicketPrelude                "com.apple.print.PageTicket."

/* Ticket: DOCUMENT TICKET
    Future Feature. Intended to hold multiple Page Tickets and separate Page Format
    and Print Settings tickets for a single document. Not yet implemented. For now,
    the keys listed here will be included at the Job Ticket Level.
*/
#define kPMDocumentTicketPrelude            "com.apple.print.DocumentTicket."
#define kPMSpoolFormatStr                   kPMDocumentTicketPrelude "PMSpoolFormat"
#define kPMSpoolFormatKey                   CFSTR( kPMSpoolFormatStr )                  /* CFString. Indicates format of data stored in the spool file. */
#define kPMPrinterModuleFormatStr           kPMDocumentTicketPrelude "PMDocPMInputFormat"
#define kPMPrinterModuleFormatKey           CFSTR( kPMPrinterModuleFormatStr )          /* CFString. Indicates format of data going to the Printer Module. */

/* Ticket: JOB TICKET
    Holds a Page Format and Print Settings ticket, as well as a few other fields that 
    are Job Specific, such as information about the user that submitted the job. The
    fidelity bit controls what happens when the system encounters settings that can't
    be obeyed.
    In the future a Job Ticket may hold multiple document tickets in addition to the 
    Print Settings and Page Format tickets.
*/
#define kPMJobTicketPrelude                 "com.apple.print.JobInfo."
#define kPMJobNameStr                       kPMJobTicketPrelude "PMJobName"
#define kPMJobNameKey                       CFSTR( kPMJobNameStr )                      /* CFString, The name of the job to be displayed in the queue window. */
#define kPMApplicationNameStr				kPMJobTicketPrelude "PMApplicationName"
#define kPMApplicationNameKey				CFSTR( kPMApplicationNameStr)				/* CFString, The application's name */
#define kPMUserLanguageStr                  kPMJobTicketPrelude "PMUserLanguage"
#define kPMUserLanguageKey                  CFSTR(kPMUserLanguageStr )                  /* CFNumber - kCFNumberSInt32Type, TBD how this is interpreted. */
#define kPMJobOwnerStr                      kPMJobTicketPrelude "PMJobOwner"
#define kPMJobOwnerKey                      CFSTR( kPMJobOwnerStr )                     /* CFString - Name of the user who submitted the job. */
#define kPMJobTemplateStr                   kPMJobTicketPrelude "PMJobTemplate"
#define kPMJobTemplateKey                   CFSTR( kPMJobTemplateStr )                  /* CFDictionary - PMTemplateRef, actually. See PMTemplate.h */

#define kPMOutputTypeStr		    		kPMJobTicketPrelude "PMOutputType"
#define kPMOutputTypeKey		    		CFSTR( kPMOutputTypeStr )					/* CFString, Mime type from the kPMOutputTypeListKey array the printer module should generate. */
#define kPMJobTagsStr                      kPMJobTicketPrelude "PMJobTags"				
#define kPMJobTagsKey                      CFSTR( kPMJobTagsStr )						/* CFArray - keywords associated with the job */

/* Ticket: LIST TICKET
    Contains a list of other tickets. There is no restriction on the type of tickets
    that can be stored in a list, any ticket will do. 
*/
#define kPMTicketListPrelude                "com.apple.print.TicketList."



/* Ticket: Printer Info Ticket
    Created by the Printer Module to describe features and settings of the current
    printer. This is information largely used by the Printer Module itself and the Print
    Dialog Extensions associated with the PM. All "range" type values that would be 
    verified at dialog time should go in a separate Template.
*/
#define kPMPrinterInfoPrelude               "com.apple.print.PrinterInfo."
#define kPMPrinterLongNameStr               kPMPrinterInfoPrelude "PMPrinterLongName"
#define kPMPrinterLongNameKey               CFSTR( kPMPrinterLongNameStr )              /* CFString, Full name of the printer. */
#define kPMPrinterShortNameStr              kPMPrinterInfoPrelude "PMPrinterShortName"
#define kPMPrinterShortNameKey              CFSTR( kPMPrinterShortNameStr )             /* CFString, Shorter name to use when you have less space. */
#define kPMMakeAndModelNameStr              kPMPrinterInfoPrelude "PMMakeAndModelName"
#define kPMMakeAndModelNameKey              CFSTR( kPMMakeAndModelNameStr )             /* CFString, Product name is used for ???? */
#define kPMPrinterAddressStr                kPMPrinterInfoPrelude "PMPrinterAddress"
#define kPMPrinterAddressKey                CFSTR( kPMPrinterAddressStr )               /* CFData, Product address.  */
#define kPMSupportsColorStr                 kPMPrinterInfoPrelude "PMSupportsColor"
#define kPMSupportsColorKey                 CFSTR( kPMSupportsColorStr )                /* CFBoolean, If Non-zero, printer/PM can do color. */
#define kPMDoesCopiesStr                    kPMPrinterInfoPrelude "PMDoesCopies"
#define kPMDoesCopiesKey                    CFSTR(kPMDoesCopiesStr )                    /* CFBoolean, If Non-zero, printer/PM can do copies */
#define kPMDoesCopyCollateStr               kPMPrinterInfoPrelude "PMDoesCopyCollate"
#define kPMDoesCopyCollateKey               CFSTR( kPMDoesCopyCollateStr )              /* CFBoolean, If Non-zero, printer/PM can collate. */
#define kPMDoesReverseOrderStr              kPMPrinterInfoPrelude "PMDoesReverseOrder"
#define kPMDoesReverseOrderKey              CFSTR( kPMDoesReverseOrderStr )             /* CFBoolean, If Non-zero, printer/PM can reverse the printing order. */
#define kPMInputFileTypeListStr             kPMPrinterInfoPrelude "PMInputFileTypeList"
#define kPMInputFileTypeListKey             CFSTR( kPMInputFileTypeListStr )            /* CFArray of CFStrings indicating file types. See PMDefinitions.h for complete list. */
#define kPMOutputTypeListStr		    kPMPrinterInfoPrelude "PMOutputTypeList"
#define kPMOutputTypeListKey		    CFSTR(kPMOutputTypeListStr)			/* CFArray of CFStrings indicating the MIME type for the data is can send to an IO module. */
#define kPMPPDNameStr		    	    kPMPrinterInfoPrelude "PPD"
#define kPMPPDNameKey			    CFSTR(kPMPPDNameStr)			/* CFString, containing the URL of the PPD to associate with printer. */



/* Postscript printing related tags */
#define kPMPostScriptLevelStr               kPMPrinterInfoPrelude "PMPostScriptLevel"
#define kPMPostScriptLevelKey               CFSTR( kPMPostScriptLevelStr )              /* CFNumber - kCFNumberSInt32Type, indicates PostScript Language level. Contains one of the values from the enum below */

#define kPMPostScriptVersionStr				kPMPrinterInfoPrelude "PMPSVersion"
#define kPMPostScriptVersionKey				CFSTR( kPMPostScriptVersionStr )			// CFString e.g."2040.113"

#define kPMPostScriptRevisionStr			kPMPrinterInfoPrelude "PMPSRevision"
#define kPMPostScriptRevisionKey			CFSTR( kPMPostScriptRevisionStr ) 			// CFNumber - kCFNumberSInt32Type, contains the PostScript revision which is an integer.

#define kPMPostScriptTrueTypeFontRasterizerStr		kPMPrinterInfoPrelude "PMPSTTRasterizer"
#define kPMPostScriptTrueTypeFontRasterizerKey		CFSTR( kPMPostScriptTrueTypeFontRasterizerStr ) 	// CFNumber - kCFNumberSInt32Type, contains one of the values from the enum below.

/* Enum for the possible font rasterizers. */
enum {
    ///  unknown
    kPMPSTTRasterizerUnknown = 0,
    ///  none
    kPMPSTTRasterizerNone = 1,
    ///  accept 68k
    kPMPSTTRasterizerAccept68K = 2,
    /// type 42
    kPMPSTTRasterizerType42 = 3
};

/* Enum for possible PostScript Language Levels. */
enum {
    /// Level 2 Compatible, may take advantage of Level 3 features
    kPMPSTargetLanguageLevel2and3 = -3,
    /// Level 1 Compatible, may take advantage of Level 2 and 3 features
    kPMPSTargetLanguageLevel1and2 = -2,
    /// language level of target is unknown
    kPMPSTargetLanguageLevelUnknown = -1,
    /// level 1
    kPMPSTargetLanguageLevel1 = 1,
    /// level 2
    kPMPSTargetLanguageLevel2 = 2,
    /// level 3
    kPMPSTargetLanguageLevel3 = 3,
    // default
    kPMPSTargetLanguageLevelDefault = kPMPSTargetLanguageLevelUnknown
};


// Note, we've removed the PMLanguageInfoKey because it's not valid to store strings or structures, everything needs to be a CFType.
#define kPMTotalMemInstalledStr             kPMPrinterInfoPrelude "PMTotalMemInstalled"
#define kPMTotalMemInstalledKey             CFSTR( kPMTotalMemInstalledStr )            /* CFNumber - kCFNumberSInt32Type, Memory on the Printer itself. */
#define kPMTotalMemAvailableStr             kPMPrinterInfoPrelude "PMTotalMemAvailable"
#define kPMTotalMemAvailableKey             CFSTR( kPMTotalMemAvailableStr )            /* CFNumber - kCFNumberSInt32Type, Remaining memory available for use. */
/* PPD related tags */
#define kPMDescriptionFileStr               kPMPrinterInfoPrelude "PMDescriptionFile"
#define kPMDescriptionFileKey               CFSTR( kPMDescriptionFileStr )              /* CFString, PPD file name or other description file. */
#define kPMCompiledPPDStr                   kPMPrinterInfoPrelude "PMCompiledPPD"
#define kPMCompiledPPDKey                   CFSTR( kPMCompiledPPDStr )                  /* CFData, Compiled PPD file to ease parsing after the fact. Not sure we need. */
/* ColorSync related tags */
#define kPMColorDeviceIDStr                 kPMPrinterInfoPrelude "PMColorDeviceID"
#define kPMColorDeviceIDKey                 CFSTR( kPMColorDeviceIDStr )                /* CFString, representing a CFUUID - must be unique per device */
#define kPMColorSyncProfilesStr				kPMPrinterInfoPrelude "PMColorSyncProfiles"
#define kPMColorSyncProfilesKey				CFSTR( kPMColorSyncProfilesStr )			/* CFArray - of CFDicts, one for each factory profile. */

/* Installable options string. */
#define kPMInstallableOptionStr             kPMPrinterInfoPrelude "PMInstallableOption" 
#define kPMInstallableOptionKey             CFSTR( kPMInstallableOptionStr )            /* CFData, Installable options from PPD file. */ 

/* Suggested app drawing resolutions */
#define kPMPrinterSuggestedResStr           kPMPrinterInfoPrelude "PMPrinterSuggestedRes"
#define kPMPrinterSuggestedResKey           CFSTR( kPMPrinterSuggestedResStr ) 			/* CFArray -  array of pairs of kCFNumberDoubleType - One pair for each recommended resolution*/ 

/* Min and max range of resolutions */
#define kPMPrinterMinResStr                 kPMPrinterInfoPrelude "PMPrinterMinRes"
#define kPMPrinterMinResKey                 CFSTR( kPMPrinterMinResStr ) 				/* CFArray - 2 CFNumber, kCFNumberDoubleType, min resolution of printer */ 

#define kPMPrinterMaxResStr                 kPMPrinterInfoPrelude "PMPrinterMaxRes"
#define kPMPrinterMaxResKey                 CFSTR( kPMPrinterMaxResStr ) 				/* CFArray - 2 CFNumber, kCFNumberDoubleType, max resolution of printer */ 

/* driver creator code */
#define kPMDriverCreatorStr					kPMPrinterInfoPrelude "PMDriverCreator"		
#define kPMDriverCreatorKey					CFSTR(kPMDriverCreatorStr)					// CFNumber - kCFNumberSInt32Type creator signiture  for  driver

/* Printer Resident font data handle */
#define kPMPrinterFontStr                   kPMPrinterInfoPrelude "Printer Fonts"		
#define kPMPrinterFontKey                   CFSTR( kPMPrinterFontStr )                  /* CFData, Printer resident fonts from printer query. */

#define kPMPrinterIsPostScriptDriverStr		kPMPrinterInfoPrelude "PMIsPostScriptDriver"
#define kPMPrinterIsPostScriptDriverKey		CFSTR(kPMPrinterIsPostScriptDriverStr)		// CFBoolean - PJCIsPostScriptDriver

/*!
 * The value of this key is a CFBoolean representing the result of querying the PostScript printer
 * about its ability to accept binary data. It is possible for the underlying communications
 * to support binary data, both high bit characters and control characters, but for a
 * spooler on the other end of the channel to not accept binary data. This value represents
 * the spooler/printer's abilities.
 */
#define kPMIsBinaryOKStr			kPMPrinterInfoPrelude "PMIsBinaryOK"
#define kPMIsBinaryOKKey			CFSTR(kPMIsBinaryOKStr)

/*!
 * The value of this key is a CFBoolean indicating whether the communications channel can
 * transmit characters in the range 0x80 - )xFF inclusive without them being damaged or
 * interpreted as channel control characters.
 */
#define kPM8BitCommStr			kPMPrinterInfoPrelude "PM8BitComm"
#define kPM8BitCommKey			CFSTR(kPM8BitCommStr)		// CFBoolean - Can the comm channel take bytes with the high bit set?

/*!
 * The value of this key is a CFBoolean indicating whether the communications channel can
 * transmit characters in the range 0x00 - 0x1F inclusive without them being damaged or
 * interpreted as channel control characters.
 */
#define kPMTransparentCommStr			kPMPrinterInfoPrelude "PMTransparentComm"
#define kPMTransparentCommKey			CFSTR(kPMTransparentCommStr)



#define kPMPageToPaperMappingTypeStr	    "com.apple.print.PageToPaperMappingType"
#define kPMPageToPaperMappingTypeKey	    CFSTR(kPMPageToPaperMappingTypeStr) /* a CFNumber - values from PMPageToPaperMappingType */
#define kPMPageToPaperMediaNameStr	    "com.apple.print.PageToPaperMappingMediaName" 
#define kPMPageToPaperMediaNameKey	    CFSTR(kPMPageToPaperMediaNameStr) /* a CFString - the untranslated media name for the destination sheet */

#define kPMPageToPaperMappingAllowScalingUpStr	    "com.apple.print.PageToPaperMappingAllowScalingUp"
#define kPMPageToPaperMappingAllowScalingUpKey	    CFSTR(kPMPageToPaperMappingAllowScalingUpStr) /* a CFBoolean - if true, allow scaling up to fit
												    destination sheet, otherwise do not scale
												    up if destination sheet is larger than formatting
												    sheet. Default value: false. */

/* Possible values for the kPMColorMatchingModeKey*/
#define kPMVendorColorMatchingStr	    "AP_VendorColorMatching"
#define kPMVendorColorMatching		    CFSTR( kPMVendorColorMatchingStr )
#define kPMApplicationColorMatchingStr      "AP_ApplicationColorMatching"
#define kPMApplicationColorMatching	    CFSTR( kPMApplicationColorMatchingStr )

#define kPMColorMatchingModeStr		    "AP_ColorMatchingMode"
#define kPMColorMatchingModeKey		    CFSTR( kPMColorMatchingModeStr )   /* Value is CFStringRef - one of kPMColorSyncMatching (deprecated), 
										kPMVendorColorMatching, kPMApplicationColorMatching */

#define kPMSupportsVendorMatchingModeStr    "APSupportsCustomColorMatching"
#define kPMSupportsVendorMatchingModeKey    CFSTR( kPMSupportsVendorMatchingModeStr )

#define kPMsRGBCustomColorMatchingProfileStr		"sRGB"
#define kPMsRGBCustomColorMatchingProfileKey		CFSTR( kPMsRGBCustomColorMatchingProfileStr )
#define kPMAdobeRGBCustomColorMatchingProfileStr	"AdobeRGB"
#define kPMAdobeRGBCustomColorMatchingProfileKey	CFSTR( kPMAdobeRGBCustomColorMatchingProfileStr )

#define kPMCustomColorMatchingProfileStr    "APCustomColorMatchingProfile"
#define kPMCustomColorMatchingProfileKey    CFSTR( kPMCustomColorMatchingProfileStr )  /* Allowed values are kPMsRGBCustomColorMatchingProfileKey or kPMAdobeRGBCustomColorMatchingProfileKey */

/* Page to Paper Mapping Types */
typedef enum{
    kPMPageToPaperMappingNone = 1,
    kPMPageToPaperMappingScaleToFit,
}PMPageToPaperMappingType;

/* END OF SECTION II: TICKET KEYS */

/* SECTION III, FUNCTIONS: */
/* Create, or copy a Ticket. As a Ticket is created, its type is stored in the object itself */
/* and used to help the programmer make sure they are adding the correct fields to the object. */
EXTERN_API_C( OSStatus )
PMTicketCreate                  (CFAllocatorRef         allocator,
                                 CFStringRef            ticketType,
                                 PMTicketRef *          newTicket);

EXTERN_API_C( OSStatus )
PMTicketCopy                    (CFAllocatorRef         allocator,
                                 PMTicketRef            sourceTicket,
                                 PMTicketRef *          destinationTicket);

/* Retain, release, or get retain count of a Ticket. The behavior is modeled after */
/* CoreFoundation's CFRetain, CFRelease, and CFGetRetainCount APIs. */

EXTERN_API_C( OSStatus )
PMTicketGetRetainCount          (PMTicketRef            ticket,
                                 CFIndex *              retainCount);

EXTERN_API_C( OSStatus )
PMTicketRetain                  (PMTicketRef            ticket);

EXTERN_API_C( OSStatus )
PMTicketRelease                 (PMTicketRef            ticket);


/* PMTicketReleaseAndClear does the same thing as PMTicketRelease except that it sets the */
/* passed in pointer to NULL, which we think is good programming practice. Other references */
/* to the ticket may still be valid, but this one is no longer expected to be used. */
EXTERN_API_C( OSStatus )
PMTicketReleaseAndClear         (PMTicketRef *          ticket);


/* To confirm that we have a real ticket, this short function gets called. */
EXTERN_API_C( OSStatus )
PMTicketConfirmTicket           (PMTicketRef            ticket);


/* We validate an entire ticket by calling our PMTicketValidate function, passing a template  */
/* which contains constraints for all the values in the ticket. Those entries in the ticket */
/* that don't have constraints will not be checked, so developers can add their own custom */
/* data. */
EXTERN_API_C( OSStatus )
PMTicketValidate                (PMTicketRef            ticket,
                                 PMTemplateRef          verifyingTemplate,
                                 CFArrayRef *           invalidItems);


/* A couple of utility functions to find out what type of ticket is references, as well */
/* as access to the allocator function passed in for a ticket. We also provide a function */
/* to check the API version for a ticket, to protect against future conversion problems */
/* from old to new tickets. */
EXTERN_API_C( OSStatus )
PMTicketGetType                 (PMTicketRef            ticket,
                                 CFStringRef *          ticketType);

EXTERN_API_C( OSStatus )
PMTicketGetEnumType             (PMTicketRef            ticket,
                                 PMTicketType *         ticketType);

EXTERN_API_C( OSStatus )
PMTicketGetAllocator            (PMTicketRef            ticket,
                                 CFAllocatorRef *       allocator);

EXTERN_API_C( OSStatus )
PMTicketGetAPIVersion           (PMTicketRef            ticket,
                                 CFStringRef *          apiVersion);


/* To store a Ticket object it needs to be converted to XML, a serialization that */
/* creates human readable text. If the data is to be written to file anyway, a second */
/* function is provided to go "all the way." */
/* Convert to XML */
EXTERN_API_C( OSStatus )
PMTicketToXML                   (PMTicketRef            ticket,
                                 CFDataRef *            anXMLTicket);

/* Convert to XML and write to file */
EXTERN_API_C( OSStatus )
PMTicketWriteXMLToFile          (PMTicketRef            ticket,
                                 const char *           path);
				 
/* Convert to XML and write to FILE stream. */
EXTERN_API_C( OSStatus )
PMTicketWriteXML		(PMTicketRef 		ticket, FILE *			file );

/* Convert from XML */
EXTERN_API_C( OSStatus )
PMXMLToTicket                   (CFAllocatorRef         allocator,
                                 CFDataRef              anXMLTicket,
                                 PMTicketRef *          ticket,
                                 CFStringRef *          conversionError);

/* Convert from XML File */
EXTERN_API_C( OSStatus )
PMXMLURLToTicket				( CFAllocatorRef allocator, 
                                  CFURLRef anXMLURL, 
                                  PMTicketRef *ticket, 
                                  CFPropertyListFormat *format, 
                                  CFStringRef *errorString );

/* Read from file and convert to XML. */
EXTERN_API_C( OSStatus )
PMTicketReadXMLFromFile         (CFAllocatorRef         allocator,
                                 const char *           path,
                                 PMTicketRef *          ticket,
                                 CFStringRef *          errorString);


/* To add an item to a ticket, the "SetItem" call for the specific data type is used whenever  */
/* possible. This adds a new item if one doesn't exist and updates a previous item if it  */
/* already exists. The "locked" field will determine if subsequent updates are allowed. */
/* Strings: */
/* CFString */
EXTERN_API_C( OSStatus )
PMTicketSetCFString             (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFStringRef            item,
                                 Boolean                locked);

/* Pascal String */
EXTERN_API_C( OSStatus )
PMTicketSetPString              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 ConstStringPtr         value,
                                 Boolean                locked);

/* 'C' String */
EXTERN_API_C( OSStatus )
PMTicketSetCString              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 const char *           value,
                                 Boolean                locked);

/* Array of 'C' Strings */
EXTERN_API_C( OSStatus )
PMTicketSetCStringArray         (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 const char **          cStringArray,
                                 UInt32                 count,
                                 Boolean                locked);


/* Numbers: */
/* CFNumber */
EXTERN_API_C( OSStatus )
PMTicketSetCFNumber             (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFNumberRef            item,
                                 Boolean                locked);

/* SInt32 */
EXTERN_API_C( OSStatus )
PMTicketSetSInt32               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 SInt32                 value,
                                 Boolean                locked);

/* Array of SInt32 */
EXTERN_API_C( OSStatus )
PMTicketSetSInt32Array          (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 const SInt32 *         sInt32Array,
                                 UInt32                 count,
                                 Boolean                locked);

/* UInt32 */
/* NOTE: The underlying code uses SInt32s in the CF code, so this function can't set -1 */
/* as the largest unsigned number. Please avoid setting the high bit */
EXTERN_API_C( OSStatus )
PMTicketSetUInt32               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 UInt32                 value,
                                 Boolean                locked);

/* Array of UInt32 */
/* NOTE: The underlying code uses SInt32s in the CF code, so this function can't set -1 */
/* as the largest unsigned number. Please avoid setting the high bit */
EXTERN_API_C( OSStatus )
PMTicketSetUInt32Array          (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 const UInt32 *         uInt32Array,
                                 UInt32                 count,
                                 Boolean                locked);

/* Double */
EXTERN_API_C( OSStatus )
PMTicketSetDouble               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 double                 value,
                                 Boolean                locked);

/* Array of doubles */
EXTERN_API_C( OSStatus )
PMTicketSetDoubleArray			(PMTicketRef ticket, 
								 CFStringRef clientID, 
								 CFStringRef key, 
								 const double *array, 
								 UInt32 count, 
								 Boolean changeable );

/* PMResolution - Array of 2 Doubles */
EXTERN_API_C( OSStatus )
PMTicketSetPMResolution          (PMTicketRef           ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 PMResolution *         value,
                                 Boolean                locked);

/* Array of PMResolution */
EXTERN_API_C( OSStatus )
PMTicketSetPMResolutionArray     (PMTicketRef           ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 PMResolution *         pmResolutionArray,
                                 UInt32                 count,
                                 Boolean                locked);

/* PMRect - Array of 4 Doubles */
EXTERN_API_C( OSStatus )
PMTicketSetPMRect               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 PMRect *               value,
                                 Boolean                locked);

/* Array of PMRects */
EXTERN_API_C( OSStatus )
PMTicketSetPMRectArray          (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 PMRect *               pmRectArray,
                                 UInt32                 count,
                                 Boolean                locked);

/* Raw Data */
/* CFData */
EXTERN_API_C( OSStatus )
PMTicketSetCFData               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFDataRef              item,
                                 Boolean                locked);

/* UInt8 - 'C' Bytes */
EXTERN_API_C( OSStatus )
PMTicketSetBytes                (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 const UInt8 *          data,
                                 UInt32                 size,
                                 Boolean                locked);

/* Booleans */
/* CFBoolean */
EXTERN_API_C( OSStatus )
PMTicketSetCFBoolean            (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFBooleanRef           item,
                                 Boolean                locked);

/* 'C' Boolean */
EXTERN_API_C( OSStatus )
PMTicketSetBoolean              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 Boolean                value,
                                 Boolean                locked);


/* Dates */
EXTERN_API_C( OSStatus )
PMTicketSetCFDate               (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFDateRef              item,
                                 Boolean                locked);

/* Arrays */
EXTERN_API_C( OSStatus )
PMTicketSetCFArray              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFArrayRef             item,
                                 Boolean                locked);

/* Dictionaries */
EXTERN_API_C( OSStatus )
PMTicketSetCFDictionary         (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFDictionaryRef        item,
                                 Boolean                locked);

/* Templates, which are defined to be opaque. */
EXTERN_API_C( OSStatus )
PMTicketSetTemplate             (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 PMTemplateRef          item,
                                 Boolean                locked);

/* Generic CF Type */
EXTERN_API_C( OSStatus )
PMTicketSetItem                 (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 CFTypeRef              item,
                                 Boolean                locked);


/* Convert an array of static item structures into entries for a ticket and add them one at */
/* a time to the ticket. Could fail part way through. */
EXTERN_API_C( OSStatus )
PMTicketFillFromArray           (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 const PMTicketItemStruct * items,
                                 UInt32                 itemCount);


/* If an item must be copied from one ticket to another, use the "CopyItem" call to */
/* make the simple transfer. This will update the recorded date and client ID for the item. */
/* The "locked" field will determine if subsequent updates may be made. */
EXTERN_API_C( OSStatus )
PMTicketCopyItem                (PMTicketRef            sourceTicket,
                                 PMTicketRef            destTicket,
                                 CFStringRef            clientID,
                                 CFStringRef            key,
                                 Boolean                locked);


/* Disable an item using PMTicketDelete. Future callers will see "ItemNotFound" errors. */
/* This call actually tags a new set of structures to the end of an item's dictionary, in */
/* order to keep a history of the item. */
/* NOTE: In 10.5 and later, PMTicketDeleteItem and PMTicketReleaseItem */
/* produce the same result */
EXTERN_API_C( OSStatus )
PMTicketDeleteItem              (PMTicketRef            ticket,
                                 CFStringRef            clientID,
                                 CFStringRef            key);

/* Release an item when you want it completely removed from the */
/* ticket. This can only be done if the item is unlocked. */
/* NOTE: In 10.5 and later, PMTicketDeleteItem and PMTicketReleaseItem */
/* produce the same result */
EXTERN_API_C( OSStatus )
PMTicketReleaseItem             (PMTicketRef            ticket,
                                 CFStringRef            key);

/* Fetching an item back out of the ticket requires the "GetItem" call for the particular type */
/* of data you're fetching. In some cases, the caller doesn't know what type of data is being */
/* returned, so we have a generic "GetItem" call, but for all other cases developers are  */
/* encouraged to use the specific call for the data they need, thus enabling type checking and */
/* reducing errors. */
/* Returns true if item exists. */
EXTERN_API_C( Boolean )
PMTicketContainsItem            (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key);

/* Strings */
/* CFString */
EXTERN_API_C( OSStatus )
PMTicketGetCFString             (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFStringRef *          item);

/* Pascal String */
EXTERN_API_C( OSStatus )
PMTicketGetPString              (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 UInt32                 bufferSize,
                                 CFStringEncoding       encoding,
                                 StringPtr              value);

/* 'C' String */
EXTERN_API_C( OSStatus )
PMTicketGetCString              (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 UInt32                 bufferSize,
                                 CFStringEncoding       encoding,
                                 char *                 value);


/* Numbers */
/* CFNumber */
EXTERN_API_C( OSStatus )
PMTicketGetCFNumber             (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFNumberRef *          item);

/* SInt32 */
EXTERN_API_C( OSStatus )
PMTicketGetSInt32               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 SInt32 *               value);

/* UInt32 */
EXTERN_API_C( OSStatus )
PMTicketGetUInt32               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 UInt32 *               value);

/* Double */
EXTERN_API_C( OSStatus )
PMTicketGetDouble               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 double *               value);

/* PMResolution - Array of 2 doubles */
EXTERN_API_C( OSStatus )
PMTicketGetPMResolution			(PMTicketRef ticket, 
								 UInt32 nodeIndex1, 
								 UInt32 nodeIndex2, 
								 CFStringRef key, 
								 PMResolution *res );

EXTERN_API_C( OSStatus )
PMTicketGetIndexPMResolution	(PMTicketRef ticket, 
								 UInt32 nodeIndex1, 
								 UInt32 nodeIndex2, 
								 CFStringRef key, 
								 UInt32 index, 
								 PMResolution *res );

/* PMRect - Array of 4 doubles */
EXTERN_API_C( OSStatus )
PMTicketGetPMRect               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 PMRect *               value);


/* Raw Data */
/* CFData */
EXTERN_API_C( OSStatus )
PMTicketGetCFData               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFDataRef *            item);

/* UInt8 - 'C' Bytes */
/* NOTE: Caller is expected to call twice if size is unknown, passing null for data pointer */
/* and a valid pointer for the size before allocating space and calling back with both pointers */
/* set, this time with valid data pointer and valid size pointer pointing to # of bytes requested. */
EXTERN_API_C( OSStatus )
PMTicketGetBytes                (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 UInt8 *                data,
                                 UInt32 *               size);

/* Booleans */
/* CFBoolean */
EXTERN_API_C( OSStatus )
PMTicketGetCFBoolean            (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFBooleanRef *         item);

/* 'C' Boolean  */
EXTERN_API_C( OSStatus )
PMTicketGetBoolean              (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 Boolean *              value);

/* Dates */
EXTERN_API_C( OSStatus )
PMTicketGetCFDate               (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFDateRef *            item);

/* Non-numeric Arrays */
EXTERN_API_C( OSStatus )
PMTicketGetCFArray              (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFArrayRef *           item);

/* Dictionaries */
EXTERN_API_C( OSStatus )
PMTicketGetCFDictionary         (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFDictionaryRef *      item);

/* PMTemplates, which are defined to be opaque. */
EXTERN_API_C( OSStatus )
PMTicketCreateTemplate          (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 PMTemplateRef *        item);


/* The generic calls for regular items and meta items. See notes on "SetMetaItem" for more details. */
EXTERN_API_C( OSStatus )
PMTicketGetItem                 (PMTicketRef            ticket,
                                 UInt32                 nodeIndex1,
                                 UInt32                 nodeIndex2,
                                 CFStringRef            key,
                                 CFTypeRef *            item);


/* Any ticket can contain another ticket, allowing us to store multiple PageFormat tickets */
/* (one for each page) and multiple Document Info tickets (for multi-document jobs). The following */
/* functions allow us to put a ticket into another ticket as a sub-ticket, and retreive it */
/* later on. */
EXTERN_API_C( OSStatus )
PMTicketSetTicket               (PMTicketRef            ticket,
                                 PMTicketRef            ticketToAdd,
                                 UInt32                 index);

EXTERN_API_C( OSStatus )
PMTicketContainsTicket          (PMTicketRef            ticket,
                                 CFStringRef            requestedType,
                                 UInt32                 index,
                                 Boolean *              exists);

EXTERN_API_C( OSStatus )
PMTicketGetTicket               (PMTicketRef            ticket,
                                 CFStringRef            requestedType,
                                 UInt32                 index,
                                 PMTicketRef *          retrievedTicket);

EXTERN_API_C( OSStatus )
PMTicketRemoveTicket            (PMTicketRef            ticket,
                                 CFStringRef            typeToRemove,
                                 UInt32                 index);


/*!
 * @function	PMTicketCreateDict
 * @abstract	Distill a ticket into a dictionary.
 *
 * @discussion	This function extracts the key value pairs from a ticket
 *		and places them into a dictionary. Information maintained
 *		by the ticket, such as who added a value and when is lost.
 */	 
EXTERN_API_C( CFDictionaryRef )
PMTicketCreateDict		(PMTicketRef ticket);

/*!
 * @function	PMTicketCopyKeys
 * @abstract	Return the valid non-subticket keys in a ticket.
 *
 */	 
EXTERN_API_C ( CFArrayRef )
PMTicketCopyKeys		(PMTicketRef ticket);


#ifdef __cplusplus
}
#endif

#endif /* __PMTICKET__ */

