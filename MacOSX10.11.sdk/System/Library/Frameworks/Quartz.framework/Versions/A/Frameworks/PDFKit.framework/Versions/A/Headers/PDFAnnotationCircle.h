// =====================================================================================================================
//  PDFAnnotationCircle.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationCirclePrivateVars;


@interface PDFAnnotationCircle : PDFAnnotation <NSCopying/*, NSCoding*/>
{
@private
    PDFAnnotationCirclePrivateVars *_pdfPriv2;
}

// Fill color used for drawing annotation (optional, PDF 1.4).
- (NSColor *) interiorColor;
- (void) setInteriorColor: (NSColor *) color;

@end
