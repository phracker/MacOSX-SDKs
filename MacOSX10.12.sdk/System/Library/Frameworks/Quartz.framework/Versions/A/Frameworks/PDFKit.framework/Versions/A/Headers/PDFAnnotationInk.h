// =====================================================================================================================
//  PDFAnnotationInk.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationInkPrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationInk : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationInkPrivateVars	*_private2;
}

// Array of NSBezierPaths that comprise the annotation.
- (NSArray *) paths;

// Add or remove paths from the annotation.
// Path points are specified relative to the annotation's bound's origin.
- (void) addBezierPath: (PDFKitPlatformBezierPath *) path;
- (void) removeBezierPath: (PDFKitPlatformBezierPath *) path;

@end
