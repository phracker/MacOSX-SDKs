/*
	NSPrintInfo.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

/*
NSPrintInfo is a data container for parameters that help control the generation of PostScript output.  It is passed to the NSPrintOperation object, which makes a copy of it to use during the operation.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

@class NSMutableDictionary, NSPrinter;

typedef enum _NSPrintingOrientation {
    NSPortraitOrientation		= 0,
    NSLandscapeOrientation		= 1
} NSPrintingOrientation;

typedef enum _NSPrintingPaginationMode {
    NSAutoPagination			= 0,
    NSFitPagination			= 1, // Force image to fit on one page
    NSClipPagination			= 2  // Let image be clipped by page
} NSPrintingPaginationMode;


@interface NSPrintInfo : NSObject <NSCopying, NSCoding>
{
/*All instance variables are private*/
@private
    NSMutableDictionary *dictionary;
    void *_reservedPrintInfo1;
}


/* Set/get the paper attributes.  The set methods in this group may change other values in the group to keep all three values (type, size, and orientation) consistent.  To avoid this behavior, set the values in the dictionary directly.
 */
- (void)setPaperName:(NSString *)name;
- (NSString *)paperName;
- (void)setPaperSize:(NSSize)aSize;
- (NSSize)paperSize;
- (void)setOrientation:(NSPrintingOrientation)orientation;
- (NSPrintingOrientation)orientation;

/* Covers for a number of the keys on the dictionary.
*/
- (void)setLeftMargin:(float)margin;
- (void)setRightMargin:(float)margin;
- (void)setTopMargin:(float)margin;
- (void)setBottomMargin:(float)margin;
- (float)leftMargin;
- (float)rightMargin;
- (float)topMargin;
- (float)bottomMargin;
- (void)setHorizontallyCentered:(BOOL)flag;
- (BOOL)isHorizontallyCentered;
- (void)setVerticallyCentered:(BOOL)flag;
- (BOOL)isVerticallyCentered;
- (void)setHorizontalPagination:(NSPrintingPaginationMode)mode;
- (NSPrintingPaginationMode)horizontalPagination;
- (void)setVerticalPagination:(NSPrintingPaginationMode)mode;
- (NSPrintingPaginationMode)verticalPagination;

/* If job features are not implemented on this new printer, flush them when the printer is set. */
- (void)setPrinter:(NSPrinter *)pr;
- (NSPrinter *)printer;

- (void)setJobDisposition:(NSString *)disposition;
- (NSString *)jobDisposition;

/* Called when a print operation is about to start.  It allows this object to set default values for any keys that are not already set.
*/
- (void)setUpPrintOperationDefaultValues;

/* The dictionary containing the key/values for this object.
*/
- (NSMutableDictionary *)dictionary;

/* Create a PrintInfo from an existing NSDictionary.  Designated initializer.
*/
- (id)initWithDictionary:(NSDictionary *)aDict;

/* Set/get the shared PrintInfo instance.  This defines the settings for the PageLayout panel and print operations that will be used if no PrintInfo is specified for those operations.  This PrintInfo instance can be thought of as being "shared" among documents in the app.  This should never be set to nil.
*/
+ (void)setSharedPrintInfo:(NSPrintInfo *)printInfo;
+ (NSPrintInfo *)sharedPrintInfo;


/* Set/get the user's default printer.
*/
+ (NSPrinter *)defaultPrinter;
+ (void)setDefaultPrinter:(NSPrinter *)pr;

/* Get the size of a paper name */
+ (NSSize)sizeForPaperName:(NSString *)name;

@end


/* The list below defines the keys in the dictionary, and the types that they are assumed to be.  Values that are not objects are stored as NSValues.

			Dictionary Key		   Type			Description
			--------------		   ----			-----------	*/
APPKIT_EXTERN NSString *NSPrintPaperName;	// NSString		Paper name: Letter, Legal, etc.
APPKIT_EXTERN NSString *NSPrintPaperSize;	// NSSize		Height and width of paper
APPKIT_EXTERN NSString *NSPrintFormName;	// NSString
APPKIT_EXTERN NSString *NSPrintMustCollate;	// BOOL
APPKIT_EXTERN NSString *NSPrintOrientation;	// NSPrintingOrientation Portrait/Landscape
APPKIT_EXTERN NSString *NSPrintLeftMargin;	// float		Margins, in points:
APPKIT_EXTERN NSString *NSPrintRightMargin;	// float
APPKIT_EXTERN NSString *NSPrintTopMargin;	// float
APPKIT_EXTERN NSString *NSPrintBottomMargin;	// float
APPKIT_EXTERN NSString *NSPrintHorizontallyCentered;	// BOOL			Pages are centered horizontally.
APPKIT_EXTERN NSString *NSPrintVerticallyCentered;	// BOOL			Pages are centered horizontally.
APPKIT_EXTERN NSString *NSPrintHorizontalPagination;// NSPrintingPaginationMode
APPKIT_EXTERN NSString *NSPrintVerticalPagination;	// NSPrintingPaginationMode

APPKIT_EXTERN NSString *NSPrintScalingFactor;	// float		Scale before pagination.
APPKIT_EXTERN NSString *NSPrintAllPages;	// BOOL			Include all pages in the job.
APPKIT_EXTERN NSString *NSPrintReversePageOrder;// BOOL		Print last page first.
APPKIT_EXTERN NSString *NSPrintFirstPage;	// int			First page to print in job.
APPKIT_EXTERN NSString *NSPrintLastPage;	// int			Last page to print in job.
APPKIT_EXTERN NSString *NSPrintCopies;		// int			Number of copies to spool.
APPKIT_EXTERN NSString *NSPrintPagesPerSheet;	// int
APPKIT_EXTERN NSString *NSPrintJobFeatures;	// NSMutableDictionary	Key = Name.  Value = Setting.
						// Feature names come from the NSPrinter/PPD info.
						// Example:  Key=@"Resolution" Value=@"600dpi"
APPKIT_EXTERN NSString *NSPrintPaperFeed;	// NSString		Generally, the input slot.
APPKIT_EXTERN NSString *NSPrintManualFeed;	// @"NSPrintManualFeed" refers to manual feed.
APPKIT_EXTERN NSString *NSPrintPrinter;	// NSPrinter		Printer to use for print job.
APPKIT_EXTERN NSString *NSPrintJobDisposition;	// NSString		What to do with the print stream:
APPKIT_EXTERN NSString *NSPrintSavePath;	// NSString		Path if disposition = @"NSSave".

#ifndef WIN32
APPKIT_EXTERN NSString *NSPrintFaxReceiverNames;// NSArray of NSStrings  Names of receivers of the fax.
APPKIT_EXTERN NSString *NSPrintFaxReceiverNumbers;// NSArray of NSStrings  Phone numbers of receivers.
							     // Must parallel NSFaxReceiverNames.
APPKIT_EXTERN NSString *NSPrintFaxSendTime;	// NSDate		When to send the fax.
APPKIT_EXTERN NSString *NSPrintFaxUseCoverSheet;// BOOL		Whether to use a cover sheet.
APPKIT_EXTERN NSString *NSPrintFaxCoverSheetName;// NSString		The cover sheet to use.
APPKIT_EXTERN NSString *NSPrintFaxReturnReceipt;// BOOL		Whether to send mail when fax is sent.
APPKIT_EXTERN NSString *NSPrintFaxHighResolution;// BOOL		Whether to send at low resolution.
APPKIT_EXTERN NSString *NSPrintFaxTrimPageEnds;// BOOL			Whether to trim page ends or send complete pages.
APPKIT_EXTERN NSString *NSPrintFaxModem;	// NSPrinter		The fax modem to use.
#endif /* WIN32 */

/* Valid values for job disposition */
APPKIT_EXTERN NSString *NSPrintSpoolJob;	// @"NSPrintSpoolJob"	Normal print job.

#ifndef WIN32
APPKIT_EXTERN NSString *NSPrintFaxJob;		// @"NSPrintFaxJob"	Fax job.
#endif /* WIN32 */

APPKIT_EXTERN NSString *NSPrintPreviewJob;	// @"NSPrintPreviewJob"	Send to Preview app.
APPKIT_EXTERN NSString *NSPrintSaveJob;	// @"NSPrintSaveJob"	Save to a file.
APPKIT_EXTERN NSString *NSPrintCancelJob;	// @"NSPrintCancelJob"	Save to a file.
