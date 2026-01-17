// =====================================================================================================================
//  PDFAnnotationLine.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

// Style used for line end caps.
NS_ENUM_DEPRECATED(10_4, 10_12, NA, NA)
typedef NS_ENUM(NSInteger, PDFLineStyle)
{
    kPDFLineStyleNone = 0,
    kPDFLineStyleSquare = 1,
    kPDFLineStyleCircle = 2,
    kPDFLineStyleDiamond = 3,
    kPDFLineStyleOpenArrow = 4,
    kPDFLineStyleClosedArrow = 5
};

@class PDFAnnotationLinePrivateVars;

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationLine : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationLinePrivateVars *_private2;
}

// Points specifying start and end points for line annotation (required).
// Points are specified relative to the annotation's bound's origin.
- (PDFPoint) startPoint;
- (void) setStartPoint: (PDFPoint) point;
- (PDFPoint) endPoint;
- (void) setEndPoint: (PDFPoint) point;

// Style used for ornaments at the lines start and end (optional, PDF 1.4).
- (PDFLineStyle) startLineStyle;
- (void) setStartLineStyle: (PDFLineStyle) style;
- (PDFLineStyle) endLineStyle;
- (void) setEndLineStyle: (PDFLineStyle) style;

// Fill color used for drawing ornaments at end and start of lines (optional, PDF 1.4).
- (PDFKitPlatformColor *) interiorColor;
- (void) setInteriorColor: (PDFKitPlatformColor *) color;

@end
