//
//  PDFAnnotationTextWidget.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation by setting the subtype to "/Widget" and assign the key-
//  value pair { @"/FT" : @"/Tx" }. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationTextWidgetPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationTextWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationTextWidgetPrivateVars	*_private2;
}

// -------- accessors

// String value associated with text field.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;

// Attributed string associated with text field (font / fontColor).
- (NSAttributedString*) attributedStringValue;
- (void) setAttributedStringValue: (NSAttributedString*) value;

- (PDFKitPlatformColor *) backgroundColor;
- (void) setBackgroundColor: (PDFKitPlatformColor *) color;
- (NSInteger) rotation;
- (void) setRotation: (int) rotation;

// Font characteristics associated with the text field.
- (PDFKitPlatformFont *) font;
- (void) setFont: (PDFKitPlatformFont *) font;

- (PDFKitPlatformColor *) fontColor;
- (void) setFontColor: (PDFKitPlatformColor *) color;

// Alignment of text. Supported: NSLeftTextAlignment, NSRightTextAlignment and NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

// Maximum characters allowed (optional, zero indicates no specified maximum).
- (NSUInteger) maximumLength;
- (void) setMaximumLength: (NSUInteger) maxLen;

// Internal name for the field (optional). Used for ResetForm actions.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

// Configuring multiline PDF text fields
- (BOOL) isMultiline;
- (void) setIsMultiline: (BOOL) multiline;

@end
