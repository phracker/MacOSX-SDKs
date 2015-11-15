/*
	NSPrintInfo.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPDFInfo, NSPrinter;

/* Valid values for the NSPrintOrientation attribute.
*/
typedef NS_ENUM(NSInteger, NSPaperOrientation) {
    NSPaperOrientationPortrait = 0,
    NSPaperOrientationLandscape = 1
} NS_ENUM_AVAILABLE_MAC(10_9);

/* Valid values for the NSPrintHorizontalPagination and NSPrintVerticalPagination attributes.
*/
typedef NS_ENUM(NSUInteger, NSPrintingPaginationMode) {
    NSAutoPagination = 0,
    NSFitPagination = 1,
    NSClipPagination = 2
};

/* Valid values for the NSPrintJobDisposition attribute.
*/
APPKIT_EXTERN NSString * const NSPrintSpoolJob;
APPKIT_EXTERN NSString * const NSPrintPreviewJob;
APPKIT_EXTERN NSString * const NSPrintSaveJob;
APPKIT_EXTERN NSString * const NSPrintCancelJob;

/* Keys for page setup attributes that are recognized by NSPrintInfo.
*/
APPKIT_EXTERN NSString * const NSPrintPaperName; // an NSString
APPKIT_EXTERN NSString * const NSPrintPaperSize; // an NSValue containing an NSSize, in points
APPKIT_EXTERN NSString * const NSPrintOrientation; // an NSNumber containing NSPaperOrientationPortrait or NSPaperOrientationLandscape
APPKIT_EXTERN NSString * const NSPrintScalingFactor; // an NSNumber containing a floating-point percentage

/* Keys for pagination attributes that are recognized by NSPrintInfo.
*/
APPKIT_EXTERN NSString * const NSPrintLeftMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString * const NSPrintRightMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString * const NSPrintTopMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString * const NSPrintBottomMargin; // an NSNumber containing a measurement in floating-point points
APPKIT_EXTERN NSString * const NSPrintHorizontallyCentered; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintVerticallyCentered; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintHorizontalPagination; // an NSNumber containing NSAutoPagination, NSFitPagination, or NSClipPagination
APPKIT_EXTERN NSString * const NSPrintVerticalPagination; // an NSNumber containing NSAutoPagination, NSFitPagination, or NSClipPagination

/* Keys for print job attributes that are recognized by NSPrintInfo.
*/
APPKIT_EXTERN NSString * const NSPrintPrinter;	// an NSPrinter
APPKIT_EXTERN NSString * const NSPrintCopies; // an NSNumber containing the number of copies of the print job to be printed
APPKIT_EXTERN NSString * const NSPrintAllPages; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintFirstPage; // an NSNumber containing the one-based index of the first job in the page to print
APPKIT_EXTERN NSString * const NSPrintLastPage; // an NSNumber containing the one-based index of the last job in the page to print
APPKIT_EXTERN NSString * const NSPrintMustCollate; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintReversePageOrder; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintJobDisposition; // an NSString equal to NSPrintSpoolJob, NSPrintPreviewJob, NSPrintSaveJob, or NSPrintCancelJob
APPKIT_EXTERN NSString * const NSPrintPagesAcross; // an NSNumber containing the number of logical pages to be placed across a physical sheet
APPKIT_EXTERN NSString * const NSPrintPagesDown; // an NSNumber containing the number of logical pages to be placed down a physical sheet
APPKIT_EXTERN NSString * const NSPrintTime; // an NSDate containing the time at which printing should begin
APPKIT_EXTERN NSString * const NSPrintDetailedErrorReporting; // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintFaxNumber; // an NSString containing a fax number
APPKIT_EXTERN NSString * const NSPrintPrinterName; // an NSString containing the name of a printer
APPKIT_EXTERN NSString * const NSPrintSelectionOnly NS_AVAILABLE_MAC(10_6); // an NSNumber containing a boolean value
APPKIT_EXTERN NSString * const NSPrintJobSavingURL NS_AVAILABLE_MAC(10_6); // an NSURL containing the location to which the job file will be saved, for NSPrintSaveJob
APPKIT_EXTERN NSString * const NSPrintJobSavingFileNameExtensionHidden NS_AVAILABLE_MAC(10_6); // A boolean NSNumber for whether the job file's name extension should be hidden, for NSPrintSaveJob

/* Keys for page adornment attributes that are recognized by NSPrintInfo.
*/
APPKIT_EXTERN NSString * const NSPrintHeaderAndFooter; // a boolean NSNumber for whether the results of -[NSView pageHeader] and -[NSView pageFooter] should be drawn on pages

@interface NSPrintInfo : NSObject<NSCopying, NSCoding> {
    @private
    NSMutableDictionary *_attributes;
    id _moreVars;
}

/* Set or get the "shared" instance of NSPrintInfo. The shared print info object is the one that is used automatically by -[NSPageLayout runModal] and +[NSPrintOperation printOperationWithView:].
*/
+ (void)setSharedPrintInfo:(NSPrintInfo *)printInfo;
+ (NSPrintInfo *)sharedPrintInfo;

/* Given a dictionary that contains attribute entries, initialize. Attributes that are recognized by the NSPrintInfo class will be silently validated in the context of the printer selected by the attributes dictionary, or the default printer if the attributes dictionary selects no printer. Attributes that are not recognized by the NSPrintInfo class will be preserved, and returned in the dictionary returned by the -dictionary method, but otherwise ignored. This is the designated initializer for this class.
*/
- (instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)attributes;

/* Return a dictionary that contains attribute entries. This dictionary may contain attributes that were not specified in the dictionary originally passed to this object by -initWithDictionary. Changes to this dictionary will be reflected in the values returned by subsequent invocations of other of this class' methods.
*/
- (NSMutableDictionary<NSString *, id> *)dictionary;

/* Set or get the values of the paper attributes.  Because an NSPrintInfo's paper name, paper size, and orientation attributes must be kept consistent, invocation of any of the setting methods in this group may affect the values returned by subsequent invocations of any of the getting methods in this group.  For example, paper name and paper size must always agree, and the value returned by -paperSize always takes orientation into account.
*/
@property (nullable, copy) NSString *paperName;
@property NSSize paperSize;
@property NSPaperOrientation orientation;
@property CGFloat scalingFactor NS_AVAILABLE_MAC(10_6);

/* Set or get the values of the pagination attributes.
*/
@property CGFloat leftMargin;
@property CGFloat rightMargin;
@property CGFloat topMargin;
@property CGFloat bottomMargin;
@property (getter=isHorizontallyCentered) BOOL horizontallyCentered;
@property (getter=isVerticallyCentered) BOOL verticallyCentered;
@property NSPrintingPaginationMode horizontalPagination;
@property NSPrintingPaginationMode verticalPagination;

/* Set or get the value of the job disposition attribute.
*/
@property (copy) NSString *jobDisposition;

/* Set or get the destination printer specified by this object.
*/
@property (copy) NSPrinter *printer;

/* Validate all of the attributes encapsulated by this object. This method is invoked automatically before the object is used by an NSPrintOperation. This method may be overridden to perform validation of attributes that are not recognized by the NSPrintInfo class.
*/
- (void)setUpPrintOperationDefaultValues;


/* Return the imageable area of a page specified by this object, taking into account the current printer, paper, and orientation settings, but not scaling. "Imageable area" is the maximum area that can possibly be marked on by the printer hardware, not the area defined by the current margin settings. The rectangle is in a coordinate space measured by points, with (0, 0) being the lower-left corner of the oriented page and (paperWidth, paperHeight) being the upper-right corner of the oriented page. The imageable bounds may extend past the edges of the page when, for example, a printer driver specifies it so that borderless printing can be done reliably.
*/
@property (readonly) NSRect imageablePageBounds;



/* Return the human-readable name of the currently selected paper size, suitable for presentation in user interfaces.  This will typically be different from the name returned by -paperName, which is almost never suitable for presentation to to the user.
*/
@property (nullable, readonly, copy) NSString *localizedPaperName;


/* Return the default printer, if one has been selected by the user, nil otherwise.
*/
+ (nullable NSPrinter *)defaultPrinter;


/* The print info's print settings. You can put values in this dictionary to store them in any preset that the user creates while editing this print info with a print panel. Such values must be property list objects. This class is key-value coding (KVC) and key-value observing (KVO) compliant for "printSettings" so you can often bind controls in print panel accessory views directly to entries in this dictionary. You can also use this dictionary to get values that have been set by other parts of the printing system, like a printer driver's print dialog extension (the same sort of values that are returned by the Carbon Printing Manager's PMPrintSettingsGetValue() function). Other parts of the printing system often use key strings like "com.apple.print.PrintSettings.PMColorSyncProfileID" but dots like those in key strings wouldn't work well with KVC, so those dots are replaced with underscores in keys that appear in this dictionary, as in "com_apple_print_PrintSettings_PMColorSyncProfileID". You should use the same convention when adding entries to this dictionary.
*/
@property (readonly, strong) NSMutableDictionary<NSString *, id> *printSettings NS_AVAILABLE_MAC(10_5);

/* Return a Printing Manager PMPrintSession, PMPageFormat, or PMPrintSettings object, respectively. The returned object is always consistent with the state of the NSPrintInfo at the moment the method is invoked, but isn't necessarily updated immediately if other NSPrintInfo methods like -setPaperSize: and -setPaperOrientation: are invoked. The returned object will always be valid (in the Printing Manager sense). If you set any values in the returned PMPageFormat or PMPrintSettings you should afterward invoke -updateFromPMPageFormat or -updateFromPMPrintSettings, respectively. You don't also have to call PMSessionValidatePageFormat() or PMSessionValidatePrintSettings() if you do that. You should not call PMRelease() for the returned object, except of course to balance any calls of PMRetain() you do.
*/
- (void *)PMPrintSession NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_5); // the result should be cast to PMPrintSession
- (void *)PMPageFormat NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_5); // the result should be cast to PMPageFormat
- (void *)PMPrintSettings NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_5); // the result should be cast to PMPrintSettings

/* Given that the NSPrintInfo's PMPageFormat or PMPrintSettings has been changed by something other than the NSPrintInfo itself, update the NSPrintInfo to be consistent.
*/
- (void)updateFromPMPageFormat NS_AVAILABLE_MAC(10_5);
- (void)updateFromPMPrintSettings NS_AVAILABLE_MAC(10_5);



/* Set or get whether only the selected content should be printed.
*/
@property (getter=isSelectionOnly) BOOL selectionOnly NS_AVAILABLE_MAC(10_6);

/* Update the receiver with all settings and attributes present in the given NSPDFInfo. Entries in the given NSPDFInfo's attributes dictionary will be copied into the receiver's attributes dictionary ([self dictionary]). If inPDFInfo is the result of an NSPDFPanel with the NSPDFPanelRequestsParentDirectory option enabled, you must first modify inPDFInfo.URL by appending a file name. If inPDFInfo.URL points to a directory, this method will throw an exception.
*/
- (void)takeSettingsFromPDFInfo:(NSPDFInfo *)inPDFInfo NS_AVAILABLE_MAC(10_9);

@end

@interface NSPrintInfo(NSDeprecated)

/* A method that was deprecated in Mac OS 10.2. +[NSPrintInfo setDefaultPrinter:] does nothing.
*/
+ (void)setDefaultPrinter:(nullable NSPrinter *)printer NS_DEPRECATED_MAC(10_0, 10_2);

/* A method that was deprecated in Mac OS 10.2. NSPrintInfo's implementation of this method recognizes only a small fixed set of paper names, and does not take the details of any particular printer into account. You should use -[NSPrinter pageSizeForPaper:] instead.
*/
+ (NSSize)sizeForPaperName:(nullable NSString *)name NS_DEPRECATED_MAC(10_0, 10_2);

@end

/* Keys for attributes that were deprecated in Mac OS 10.2. NSPrintInfo does not recognizes these attributes. For backward binary compatibility, -[NSPrintInfo setUpPrintOperationDefaultValues] does however set default values for the NSPrintJobFeatures (an empty dictionary) and NSPrintPagesPerSheet (1) attributes.
*/
APPKIT_EXTERN NSString * const NSPrintFormName NS_DEPRECATED_MAC(10_0, 10_2);
APPKIT_EXTERN NSString * const NSPrintJobFeatures NS_DEPRECATED_MAC(10_0, 10_2);
APPKIT_EXTERN NSString * const NSPrintManualFeed NS_DEPRECATED_MAC(10_0, 10_2);
APPKIT_EXTERN NSString * const NSPrintPagesPerSheet NS_DEPRECATED_MAC(10_0, 10_2);
APPKIT_EXTERN NSString * const NSPrintPaperFeed NS_DEPRECATED_MAC(10_0, 10_2);

/* A key for an attribute that was deprecated in Mac OS 10.6. You can use NSPrintJobSavingURL instead.
*/
APPKIT_EXTERN NSString * const NSPrintSavePath NS_DEPRECATED_MAC(10_0, 10_6, "Use NSPrintJobSavingURL instead");

/* An enum NSPrintOrientation values that was deprecated in OS X 10.9. You can use NSPaperOrientation instead.
*/
typedef NS_ENUM(NSUInteger, NSPrintingOrientation) {
    NSPortraitOrientation = 0,
    NSLandscapeOrientation = 1
};

NS_ASSUME_NONNULL_END
