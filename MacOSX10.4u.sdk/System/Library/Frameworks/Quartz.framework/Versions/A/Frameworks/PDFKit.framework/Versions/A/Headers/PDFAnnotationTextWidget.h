// ======================================================================================================================
//  PDFAnnotationTextWidget.h
// ======================================================================================================================


#import <AppKit/NSText.h>
#import "PDFAnnotation.h"


@class NSColor, PDFAnnotationTextWidgetPrivateVars;


@interface PDFAnnotationTextWidget : PDFAnnotation
{
@private
    PDFAnnotationTextWidgetPrivateVars	*_pdfPriv2;
}

// -------- accessors

// String value associated with text field.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;

// Font associated with the text field.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;

// Alignment of text.  Supported: NSLeftTextAlignment, NSRightTextAlignment and NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;
@end
