// =====================================================================================================================
//  PDFAnnotationStamp.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFAnnotationStampPrivateVars;


@interface PDFAnnotationStamp : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationStampPrivateVars	*_pdfPriv2;
}

// Name of stamp annotation.  Standard stamps include names like, "Approved", "Draft", "TopSecret", etc.
// The name must be representable as ASCII.
// Very little is rendered if the annotation has no appearance stream.
- (NSString *) name;
- (void) setName: (NSString *) name;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
