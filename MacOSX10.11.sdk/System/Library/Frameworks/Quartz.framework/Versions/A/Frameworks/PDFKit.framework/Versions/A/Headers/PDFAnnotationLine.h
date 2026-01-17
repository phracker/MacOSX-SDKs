// =====================================================================================================================
//  PDFAnnotationLine.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationLinePrivateVars;


// Style used for line end caps.
typedef NSInteger PDFLineStyle;
enum
{
    kPDFLineStyleNone = 0, 
    kPDFLineStyleSquare = 1, 
    kPDFLineStyleCircle = 2,
    kPDFLineStyleDiamond = 3,
    kPDFLineStyleOpenArrow = 4,
    kPDFLineStyleClosedArrow = 5
};


@interface PDFAnnotationLine : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationLinePrivateVars *_pdfPriv2;
}

// Points specifying start and end points for line annotation (required).
// Points are specified relative to the annotation's bound's origin.
- (NSPoint) startPoint;
- (void) setStartPoint: (NSPoint) point;
- (NSPoint) endPoint;
- (void) setEndPoint: (NSPoint) point;

// Style used for ornaments at the lines start and end (optional, PDF 1.4).
- (PDFLineStyle) startLineStyle;
- (void) setStartLineStyle: (PDFLineStyle) style;
- (PDFLineStyle) endLineStyle;
- (void) setEndLineStyle: (PDFLineStyle) style;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Fill color used for drawing ornaments at end and start of lines (optional, PDF 1.4).
- (NSColor *) interiorColor;
- (void) setInteriorColor: (NSColor *) color;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@end
