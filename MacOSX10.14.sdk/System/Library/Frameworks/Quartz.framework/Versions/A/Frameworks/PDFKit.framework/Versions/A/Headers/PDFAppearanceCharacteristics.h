//
//  PDFAppearanceCharacteristics.h
//  Copyright © 2017 Apple. All rights reserved.
//
//  PDFAppearanceCharacteristics represents a dictionary that is specific to widget annotation types,
//  containing additional information for constructing the annotation’s appearance.
//  It is designed to be a representation of the /MK appearance characteristics entry in
//  the annotation dictionary. Because the /MK entry is optional, all properties of
//  PDFAppearanceCharacteristics are optional as well.
//
//  Properties are based on the Adobe PDF Specification (1.7),
//  Table 8.40: Entries in an appearance characteristics dictionary
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotationUtilities.h>

NS_ASSUME_NONNULL_BEGIN

// Widget appearance characteristics keys.
typedef NSString* const PDFAppearanceCharacteristicsKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyBackgroundColor PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyBorderColor PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyRotation PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyCaption PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyRolloverCaption PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyDownCaption PDFKIT_AVAILABLE(10_13, 11_0);

@class PDFAppearanceCharacteristicsPrivate;

PDFKIT_CLASS_AVAILABLE(10_13, 11_0)
@interface PDFAppearanceCharacteristics : NSObject <NSCopying>
{
@private
    PDFAppearanceCharacteristicsPrivate *_private;
}

// -------- accessors

// For button widget annotations, need to specify the control type for PDFAppearanceCharacteristics
// as certain attributes, i.e. captions, are only available for certain flavors.
// Control type does not need to be set for text or choice widget annotations.
@property (nonatomic) PDFWidgetControlType controlType;

// The background color of the widget annotation.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// The border color of the widget annotation.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *borderColor;

// The number of *degrees* by which the widget annotation is rotated counterclockwise relative to the page.
// The value must be a multiple of 90. Default value: 0.
@property (nonatomic) NSInteger rotation;

// The widget annotation’s normal caption, displayed when it is not interacting with the user.
@property (nonatomic, copy, nullable) NSString *caption;

// The widget's caption displayed when the user moves the mouse over the annotation.
// Applies only to kPDFWidgetPushButtonControl.
@property (nonatomic, copy, nullable) NSString *rolloverCaption;

// The widget's caption displayed when the user holds the mouse button while over the annotation.
// Applies only to kPDFWidgetPushButtonControl.
@property (nonatomic, copy, nullable) NSString *downCaption;

// List all appearance characteristics properties as key-value pairs; returns a deep copy of all pairs.
// Helpful for debugging.
@property (nonatomic, readonly, copy) NSDictionary *appearanceCharacteristicsKeyValues;


@end

NS_ASSUME_NONNULL_END
