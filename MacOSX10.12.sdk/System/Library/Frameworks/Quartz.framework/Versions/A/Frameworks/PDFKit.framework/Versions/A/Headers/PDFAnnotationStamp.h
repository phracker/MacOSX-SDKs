// =====================================================================================================================
//  PDFAnnotationStamp.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationStampPrivateVars;

NS_CLASS_DEPRECATED_MAC(10_5, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationStamp : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationStampPrivateVars	*_private2;
}

// Name of stamp annotation.  Standard stamps include names like, "Approved", "Draft", "TopSecret", etc.
// The name must be representable as ASCII.
// Very little is rendered if the annotation has no appearance stream.
- (NSString *) name;
- (void) setName: (NSString *) name;

@end
