/*
	NSPrintInfo.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

@class NSMutableDictionary, NSPrinter;

// Valid values for the NSPrintOrientation attribute.
typedef enum {
    NSPortraitOrientation = 0,
    NSLandscapeOrientation = 1
} NSPrintingOrientation;

// Valid values for the NSPrintHorizontalPagination and NSPrintVerticalPagination attributes.
typedef enum {
    NSAutoPagination = 0,
    NSFitPagination = 1,
    NSClipPagination = 2
} NSPrintingPaginationMode;

// Valid values for the NSPrintJobDisposition attribute.
APPKIT_EXTERN NSString *NSPrintSpoolJob;
APPKIT_EXTERN NSString *NSPrintPreviewJob;
APPKIT_EXTERN NSString *NSPrintSaveJob;
APPKIT_EXTERN NSString *NSPrintCancelJob;

// Keys for page setup attributes that are recognized by NSPrintInfo.
APPKIT_EXTERN NSString *NSPrintPaperName; // an NSString
APPKIT_EXTERN NSString *NSPrintPaperSize; // an NSValue containing an NSSize, in points
APPKIT_EXTERN NSString *NSPrintOrientation; // an NSNumber containing NSPortraitOrientation or NSLandscapeOrientation
APPKIT_EXTERN NSString *NSPrintScalingFactor; // an NSNumber containing a floating-point percentage

// Keys for pagination attributes that are recognized by NSPrintInfo.
APPKIT_EXTERN NSString *NSPrintLeftMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString *NSPrintRightMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString *NSPrintTopMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString *NSPrintBottomMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString *NSPrintHorizontallyCentered; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintVerticallyCentered; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintHorizontalPagination; // an NSNumber containing NSAutoPagination, NSFitPagination, or NSClipPagination
APPKIT_EXTERN NSString *NSPrintVerticalPagination; // an NSNumber containing NSAutoPagination, NSFitPagination, or NSClipPagination

// Keys for print job attributes that are recognized by NSPrintInfo.
APPKIT_EXTERN NSString *NSPrintPrinter;	// an NSPrinter
APPKIT_EXTERN NSString *NSPrintCopies; // an NSNumber containing the number of copies of the print job to be printed
APPKIT_EXTERN NSString *NSPrintAllPages; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintFirstPage; // an NSNumber containing the one-based index of the first job in the page to print
APPKIT_EXTERN NSString *NSPrintLastPage; // an NSNumber containing the one-based index of the last job in the page to print
APPKIT_EXTERN NSString *NSPrintMustCollate; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintReversePageOrder; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintJobDisposition; // an NSString equal to NSPrintSpoolJob, NSPrintPreviewJob, NSPrintSaveJob, or NSPrintCancelJob
APPKIT_EXTERN NSString *NSPrintSavePath; // an NSString containing a path to which the job file will be saved, for NSPrintSaveJob
APPKIT_EXTERN NSString *NSPrintPagesAcross AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSNumber containing the number of logical pages to be placed across a physical sheet
APPKIT_EXTERN NSString *NSPrintPagesDown AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSNumber containing the number of logical pages to be placed down a physical sheet
APPKIT_EXTERN NSString *NSPrintTime AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSDate containing the time at which printing should begin
APPKIT_EXTERN NSString *NSPrintDetailedErrorReporting AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString *NSPrintFaxNumber AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSString containing a fax number
APPKIT_EXTERN NSString *NSPrintPrinterName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSString containing the name of a printer

// Keys for page adornment attributes that are recognized by NSPrintInfo.
APPKIT_EXTERN NSString *NSPrintHeaderAndFooter AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // an NSNumber containing a boolean value

@interface NSPrintInfo : NSObject<NSCopying, NSCoding> {
    @private
    NSMutableDictionary *_attributes;
    id _moreVars;
}

// Set or get the "shared" instance of NSPrintInfo.  The shared print info object is the one that is used automatically by -[NSPageLayout runModal] and +[NSPrintOperation printOperationWithView:].
+ (void)setSharedPrintInfo:(NSPrintInfo *)printInfo;
+ (NSPrintInfo *)sharedPrintInfo;

// Given a dictionary that contains attribute entries, initialize.  Attributes that are recognized by the NSPrintInfo class will be silently validated in the context of the printer selected by the attributes dictionary, or the default printer if the attributes dictionary selects no printer.  Attributes that are not recognized by the NSPrintInfo class will be preserved, and returned in the dictionary returned by the -dictionary method, but otherwise ignored.  This is the designated initializer for this class.
- (id)initWithDictionary:(NSDictionary *)attributes;

// Return a dictionary that contains attribute entries.  This dictionary may contain attributes that were not specified in the dictionary originally passed to this object by -initWithDictionary.  Changes to this dictionary will be reflected in the values returned by subsequent invocations of other of this class' methods.
- (NSMutableDictionary *)dictionary;

// Set or get the values of the paper attributes.  Because an NSPrintInfo's paper name, paper size, and orientation attributes must be kept consistent, invocation of any of the setting methods in this group may affect the values returned by subsequent invocations of any of the getting methods in this group.  For example, paper name and paper size must always agree, and the value returned by -paperSize always takes orientation into account.
- (void)setPaperName:(NSString *)name;
- (void)setPaperSize:(NSSize)size;
- (void)setOrientation:(NSPrintingOrientation)orientation;
- (NSString *)paperName;
- (NSSize)paperSize;
- (NSPrintingOrientation)orientation;

// Set or get the values of the pagination attributes.
- (void)setLeftMargin:(float)margin;
- (void)setRightMargin:(float)margin;
- (void)setTopMargin:(float)margin;
- (void)setBottomMargin:(float)margin;
- (float)leftMargin;
- (float)rightMargin;
- (float)topMargin;
- (float)bottomMargin;
- (void)setHorizontallyCentered:(BOOL)flag;
- (void)setVerticallyCentered:(BOOL)flag;
- (BOOL)isHorizontallyCentered;
- (BOOL)isVerticallyCentered;
- (void)setHorizontalPagination:(NSPrintingPaginationMode)mode;
- (void)setVerticalPagination:(NSPrintingPaginationMode)mode;
- (NSPrintingPaginationMode)horizontalPagination;
- (NSPrintingPaginationMode)verticalPagination;

// Set or get the value of the job disposition attribute.
- (void)setJobDisposition:(NSString *)disposition;
- (NSString *)jobDisposition;

// Set or get the printer specified by this object.
- (void)setPrinter:(NSPrinter *)printer;
- (NSPrinter *)printer;

// Validate all of the attributes encapsulated by this object.  This method is invoked automatically before the object is used by an NSPrintOperation.  This method may be overridden to perform validation of attributes that are not recognized by the NSPrintInfo class.
- (void)setUpPrintOperationDefaultValues;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

// Return the imageable area of a sheet of paper specified by this object, taking into account the current printer, paper size, and orientation settings, but not scaling.  "Imageable area" is the maximum area that can possibly be marked on by the printer hardware, not the area defined by the current margin settings.  The rectangle is in a coordinate space measured by points, with (0, 0) being the lower-left corner of the oriented sheet and (paperWidth, paperHeight) being the upper-right corner of the oriented sheet.  The imageable bounds may extend past the edges of the sheet when, for example, a printer driver specifies it so that borderless printing can be done reliably.
- (NSRect)imageablePageBounds;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

// Return the human-readable name of the currently selected paper size, suitable for presentation in user interfaces.  This will typically be different from the name returned by -paperName, which is almost never suitable for presentation to to the user.
- (NSString *)localizedPaperName;

#endif

// Return the default printer, if one has been selected by the user, nil otherwise.
+ (NSPrinter *)defaultPrinter;

// A method that was deprecated in Mac OS 10.2.  +[NSPrintInfo setDefaultPrinter:] does nothing.
+ (void)setDefaultPrinter:(NSPrinter *)printer;

// A method that was deprecated in Mac OS 10.2.  NSPrintInfo's implementation of this method recognizes only a small fixed set of paper names, and does not take the details of any particular printer into account.  You should use -[NSPrinter pageSizeForPaper:] instead.
+ (NSSize)sizeForPaperName:(NSString *)name;

@end

// Keys for attributes that were deprecated in Mac OS 10.2.  NSPrintInfo does not recognizes these attributes.  For backward binary compatibility, -[NSPrintInfo setUpPrintOperationDefaultValues] does however set default values for the NSPrintJobFeatures (an empty dictionary) and NSPrintPagesPerSheet (1) attributes.
APPKIT_EXTERN NSString *NSPrintFormName;
APPKIT_EXTERN NSString *NSPrintJobFeatures;
APPKIT_EXTERN NSString *NSPrintManualFeed;
APPKIT_EXTERN NSString *NSPrintPagesPerSheet;
APPKIT_EXTERN NSString *NSPrintPaperFeed;

// Keys for attributes that were deprecated in Mac OS X Public Beta.  NSPrintInfo does not recognizes these attributes.
APPKIT_EXTERN NSString *NSPrintFaxCoverSheetName;
APPKIT_EXTERN NSString *NSPrintFaxHighResolution;
APPKIT_EXTERN NSString *NSPrintFaxModem;
APPKIT_EXTERN NSString *NSPrintFaxReceiverNames;
APPKIT_EXTERN NSString *NSPrintFaxReceiverNumbers;
APPKIT_EXTERN NSString *NSPrintFaxReturnReceipt;
APPKIT_EXTERN NSString *NSPrintFaxSendTime;
APPKIT_EXTERN NSString *NSPrintFaxTrimPageEnds;
APPKIT_EXTERN NSString *NSPrintFaxUseCoverSheet;

// A job disposition that was deprecated in Mac OS X Public Beta.  NSPrintInfo treats this job disposition as synonymous with NSPrintSpoolJob.
APPKIT_EXTERN NSString *NSPrintFaxJob;
