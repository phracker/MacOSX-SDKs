// ======================================================================================================================
//  PDFAnnotationSquare.h
// ======================================================================================================================


#import "PDFAnnotation.h"


@class NSColor, PDFBorder, PDFAnnotationSquarePrivateVars;


@interface PDFAnnotationSquare : PDFAnnotation
{
@private
    PDFAnnotationSquarePrivateVars	*_pdfPriv2;
}

// Fill color used for drawing annotation.
- (NSColor *) interiorColor;
- (void) setInteriorColor: (NSColor *) color;

@end
