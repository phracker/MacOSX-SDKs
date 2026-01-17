// =====================================================================================================================
//  PDFAnnotationCircle.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationCirclePrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationCircle : PDFAnnotation <NSCopying/*, NSCoding*/>
{
@private
    PDFAnnotationCirclePrivateVars *_private2;
}

// Fill color used for drawing annotation (optional, PDF 1.4).
- (PDFKitPlatformColor *) interiorColor;
- (void) setInteriorColor: (PDFKitPlatformColor *) color;

@end
