// ======================================================================================================================
//  PDFAnnotationCircle.h
// ======================================================================================================================


#import "PDFAnnotation.h"


@class NSColor, PDFBorder, PDFAnnotationCirclePrivateVars;


@interface PDFAnnotationCircle : PDFAnnotation
{
@private
    PDFAnnotationCirclePrivateVars *_pdfPriv2;
}

// Fill color used for drawing annotation.
- (NSColor *) interiorColor;
- (void) setInteriorColor: (NSColor *) color;

@end
