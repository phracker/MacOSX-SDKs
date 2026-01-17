// ======================================================================================================================
//  PDFAnnotationLine.h
// ======================================================================================================================


#import "PDFAnnotation.h"


// Style used for line end caps.
typedef int PDFLineStyle;

enum
{
    kPDFLineStyleNone = 0, 
    kPDFLineStyleSquare = 1, 
    kPDFLineStyleCircle = 2,
    kPDFLineStyleDiamond = 3,
    kPDFLineStyleOpenArrow = 4,
    kPDFLineStyleClosedArrow = 5
};


@class NSColor, PDFBorder, PDFAnnotationLinePrivateVars;


@interface PDFAnnotationLine : PDFAnnotation
{
@private
    PDFAnnotationLinePrivateVars *_pdfPriv2;
}

// Points specifying start and end points for line annotation.
- (NSPoint) startPoint;
- (void) setStartPoint: (NSPoint) point;
- (NSPoint) endPoint;
- (void) setEndPoint: (NSPoint) point;

// Style used for ornaments at the lines start and end.
- (PDFLineStyle) startLineStyle;
- (void) setStartLineStyle: (PDFLineStyle) style;
- (PDFLineStyle) endLineStyle;
- (void) setEndLineStyle: (PDFLineStyle) style;

@end
