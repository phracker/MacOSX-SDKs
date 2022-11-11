#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPrinter.h>)
//
//  UIPrinter.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN
    
UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIPrinter : NSObject

/*!
 *  @enum       UIPrinterJobTypes
 *  @abstract   Job types supported by a printer.
 *  @discussion This enumeration provides the abstract job types
 *  		reported by the UIPrinter supportedJobTypes method.
 *  @constant   UIPrinterJobTypeUnknown		Unknown printer support.
 *  @constant   UIPrinterJobTypeDocument   	The printer supports standard document printing.
 *  @constant   UIPrinterJobTypeEnvelope	The printer supports printing on envelopes.
 *  @constant   UIPrinterJobTypeLabel      	The printer supports printing on cut labels.
 *  @constant   UIPrinterJobTypePhoto      	The printer supports printing with photographic print quality.
 *  @constant   UIPrinterJobTypeReceipt    	The printer supports printing receipts on continuous rolls.
 *  @constant   UIPrinterJobTypeRoll       	The printer supports printing documents or photos on continuous rolls.
 *  @constant   UIPrinterJobTypeLargeFormat     The printer supports printing larger than ISO A3 size.
 *  @constant   UIPrinterJobTypePostcard        The printer supports printing on postcards.
 */
typedef NS_OPTIONS(NSInteger, UIPrinterJobTypes) {
    UIPrinterJobTypeUnknown = 0,
    UIPrinterJobTypeDocument = 1 << 0,
    UIPrinterJobTypeEnvelope = 1 << 1,
    UIPrinterJobTypeLabel = 1 << 2,
    UIPrinterJobTypePhoto = 1 << 3,
    UIPrinterJobTypeReceipt = 1 << 4,
    UIPrinterJobTypeRoll = 1 << 5,
    UIPrinterJobTypeLargeFormat = 1 << 6,
    UIPrinterJobTypePostcard = 1 << 7
} API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);


/*!
 *  @method     printerWithURL:
 *  @abstract   Create a printer from its URL
 *  @discussion This method creates a new printer object from the printer's URL.
 *	        A UIPrinter object is returned even if the printer is not available
 *	        on the network.
 */
+ (UIPrinter *)printerWithURL:(NSURL *)url;

/*!
 *  @abstract   Return the URL of the printer.
 *  @discussion This method returns the full URL of the printer which can be
 *	        used in future calls to printerWithURL to access the same
 *	        printer.
 */
@property (readonly,copy) NSURL *URL;

/*!
 *  @abstract   Return a human-readable printer name.
 *  @discussion This method returns the printer name suitable for displaying in the UI.
 */
@property (readonly,copy) NSString *displayName;

/*!
 *  @abstract   Return a human-readable location.
 *  @discussion This method returns the printer's location. This is human-readable text that
 * 	        usually appears in the UI below the printer's name (such as "Front Office").
 *  	        Returns nil if the printer doesn't have a location string.
 *		This property's value is undefined until contactPrinter: has been called and
 *		completed successfully.
 */
@property (nullable,readonly,copy) NSString *displayLocation;

/*!
 *  @abstract   Returns the supported job types of this printer.
 *  @discussion This method returns a mask with all the UIPrinterJobTypes values that
 *		the printer supports.
 *		This property's value is undefined until contactPrinter: has been called and
 *		completed successfully.
 */
@property (readonly) UIPrinterJobTypes supportedJobTypes;

/*!
 *  @abstract   Return make (manufacturer) and model of the printer.
 *  @discussion This method returns the make and model of the printer, which
 *		is usually the manufacturer, model, and model number.
 *		This property's value is undefined until contactPrinter: has been called and
 *		completed successfully.
 */
@property (nullable, readonly,copy) NSString *makeAndModel;

/*!
 *  @abstract   Return whether this printer supports color printing.
 *  @discussion This method returns YES if the printer supports full color printing, NO
 * 		otherwise.
 *		This property's value is undefined until contactPrinter: has been called and
 *		completed successfully.
 *
 */
@property (readonly) BOOL supportsColor;

/*!
 *  @abstract   Return whether this printer supports duplex (double-sided) printing.
 *  @discussion This method returns YES if the printer supports duplex (double-sided)
 *		printing, NO otherwise.
 *		This property's value is undefined until contactPrinter: has been called and
 *		completed successfully.
 */
@property (readonly) BOOL supportsDuplex;

/*!
 *  @method     contactPrinter:
 *  @abstract   Check if printer is reachable, and update printer information.
 *  @discussion This method checks to see if this printer is available on the network,
 * 		and sets the displayName, displayLocation, supportedJobTypes, makeAndModel,
 *		supportsColor, and supportsDuplex for the printer.
 *		The operation can take up to 30 seconds.
 */
- (void)contactPrinter:(void(^ __nullable)(BOOL available))completionHandler;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPrinter.h>
#endif
