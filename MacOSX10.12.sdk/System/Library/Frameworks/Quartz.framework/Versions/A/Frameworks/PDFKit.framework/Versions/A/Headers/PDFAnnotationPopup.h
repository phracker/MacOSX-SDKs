// =====================================================================================================================
//  PDFAnnotationPopup.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationPopupPrivateVars;


NS_CLASS_DEPRECATED_MAC(10_5, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationPopup : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationPopupPrivateVars	*_private2;
}

- (BOOL) isOpen;
- (void) setIsOpen: (BOOL) isOpen;

@end
