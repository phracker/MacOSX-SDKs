// =====================================================================================================================
//  PDFAnnotationSquare.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationSquarePrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationSquare : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationSquarePrivateVars	*_private2;
}

// Fill color used for drawing annotation (optional, PDF 1.4).
- (PDFKitPlatformColor *) interiorColor;
- (void) setInteriorColor: (PDFKitPlatformColor *) color;

@end
