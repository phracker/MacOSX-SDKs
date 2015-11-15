// =====================================================================================================================
//  PDFAnnotationPopup.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFAnnotationPopupPrivateVars;


@interface PDFAnnotationPopup : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationPopupPrivateVars	*_pdfPriv2;
}

- (BOOL) isOpen;
- (void) setIsOpen: (BOOL) isOpen;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
