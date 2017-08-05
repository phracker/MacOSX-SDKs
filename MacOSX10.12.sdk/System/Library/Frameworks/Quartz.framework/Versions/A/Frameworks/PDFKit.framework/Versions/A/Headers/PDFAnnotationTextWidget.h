// =====================================================================================================================
//  PDFAnnotationTextWidget.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAnnotation.h>

#import <Availability.h>


@class PDFAnnotationTextWidgetPrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationTextWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationTextWidgetPrivateVars	*_private2;
}

// -------- accessors

// String value associated with text field.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;

// Attributed string associated with text field ( font / fontColor)
- (NSAttributedString*) attributedStringValue;
- (void) setAttributedStringValue: (NSAttributedString*) value;

- (PDFKitPlatformColor *) backgroundColor;
- (void) setBackgroundColor: (PDFKitPlatformColor *) color;
- (int) rotation;
- (void) setRotation: (int) rotation;

// Font characteristics associated with the text field.
- (PDFKitPlatformFont *) font;
- (void) setFont: (PDFKitPlatformFont *) font;

- (PDFKitPlatformColor *) fontColor;
- (void) setFontColor: (PDFKitPlatformColor *) color;

// Alignment of text.  Supported: NSLeftTextAlignment, NSRightTextAlignment and NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

// Maximum characters allowed (optional, zero indicates no specified maximum).
- (NSUInteger) maximumLength;
- (void) setMaximumLength: (NSUInteger) maxLen;

// Internal name for the field (optional).  Used for ResetForm actions.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

// Configuring multiline PDF text fields
- (BOOL) isMultiline;
- (void) setIsMultiline: (BOOL) multiline;

@end
