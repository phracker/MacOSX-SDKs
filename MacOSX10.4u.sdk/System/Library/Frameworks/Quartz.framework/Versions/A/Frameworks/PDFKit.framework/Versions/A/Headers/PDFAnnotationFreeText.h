// ======================================================================================================================
//  PDFAnnotationFreeText.h
// ======================================================================================================================


#import <AppKit/NSText.h>
#import "PDFAnnotation.h"

@class PDFAnnotationFreeTextPrivateVars;

@interface PDFAnnotationFreeText : PDFAnnotation
{
@private
    PDFAnnotationFreeTextPrivateVars *_pdfPriv2;
}


// Font associated with the text field.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;

// Alignment of text within annotation bounds.  Supported: NSLeftTextAlignment, NSRightTextAlignment and 
// NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

@end
