// =====================================================================================================================
//  PDFAnnotationTextWidget.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationTextWidgetPrivateVars;


@interface PDFAnnotationTextWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationTextWidgetPrivateVars	*_pdfPriv2;
}

// -------- accessors

// String value associated with text field.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;
// Attributed string associated with text field ( font / fontColor)
- (NSAttributedString*) attributedStringValue;
- (void) setAttributedStringValue: (NSAttributedString*) value;

 
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (NSColor *) backgroundColor;
- (void) setBackgroundColor: (NSColor *) color;
- (int) rotation;
- (void) setRotation: (int) rotation;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Font characteristics associated with the text field.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (NSColor *) fontColor;
- (void) setFontColor: (NSColor *) color;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Alignment of text.  Supported: NSLeftTextAlignment, NSRightTextAlignment and NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Maximum characters allowed (optional, zero indicates no specified maximum).
- (NSUInteger) maximumLength;
- (void) setMaximumLength: (NSUInteger) maxLen;

// Internal name for the field (optional).  Used for ResetForm actions.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_9

// Configuring multiline PDF text fields
- (BOOL) isMultiline;
- (void) setIsMultiline: (BOOL) multiline;

#endif // MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_9

@end
