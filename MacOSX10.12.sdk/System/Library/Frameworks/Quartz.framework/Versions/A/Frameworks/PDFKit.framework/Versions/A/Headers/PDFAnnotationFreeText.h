// =====================================================================================================================
//  PDFAnnotationFreeText.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationFreeTextPrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationFreeText : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationFreeTextPrivateVars *_private2;
}

// Font and font color associated with the text field.
- (PDFKitPlatformFont *) font;
- (void) setFont: (PDFKitPlatformFont *) font;

- (PDFKitPlatformColor *) fontColor;
- (void) setFontColor: (PDFKitPlatformColor *) color;

// Alignment of text within annotation bounds.  Supported: NSLeftTextAlignment, NSRightTextAlignment and 
// NSCenterTextAlignment.
- (NSTextAlignment) alignment;
- (void) setAlignment: (NSTextAlignment) alignment;

@end
