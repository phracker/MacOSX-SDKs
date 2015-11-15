// =====================================================================================================================
//  PDFAnnotationFreeText.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationFreeTextPrivateVars;


@interface PDFAnnotationFreeText : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationFreeTextPrivateVars *_pdfPriv2;
}

// Font and font color associated with the text field.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (NSColor *) fontColor;
- (void) setFontColor: (NSColor *) color;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Alignment of text within annotation bounds.  Supported: NSLeftTextAlignment, NSRightTextAlignment and 
// NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

@end
