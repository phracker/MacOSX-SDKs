// =====================================================================================================================
//  PDFAnnotationSquare.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationSquarePrivateVars;


@interface PDFAnnotationSquare : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationSquarePrivateVars	*_pdfPriv2;
}

// Fill color used for drawing annotation (optional, PDF 1.4).
- (NSColor *) interiorColor;
- (void) setInteriorColor: (NSColor *) color;

@end
