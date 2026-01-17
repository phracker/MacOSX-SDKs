// =====================================================================================================================
//  PDFAnnotationMarkup.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationMarkupPrivateVars;


// Types of markup annotations.
typedef NSInteger PDFMarkupType;
enum
{
    kPDFMarkupTypeHighlight = 0, 
    kPDFMarkupTypeStrikeOut = 1, 
    kPDFMarkupTypeUnderline = 2
};


@interface PDFAnnotationMarkup : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationMarkupPrivateVars *_pdfPriv2;
}

// Array of (n * 4) NSPoints defining n quadrilaterals in page space where n is the number of quad points. 
// The points for each quad are ordered in a 'Z' pattern.  That is, the first point should represent the upper left
// point representing the start of the marked-up text, the next point will be the upper right, the third point will 
// represent the lower left of the text and the last point the lower right.
// Points are specified relative to the annotation's bound's origin.
- (NSArray *) quadrilateralPoints;
- (void) setQuadrilateralPoints: (NSArray *) points;

// Type of mark-up (highlight, strike-out or underline).  Changing the markup type also changes the annotations type to 
// one of: "Highlight", "StrikeOut", or "Underline" (these are three seperate annotation types treated here as three 
// seperate flavors of the one PDFAnnotationMarkup class).
- (PDFMarkupType) markupType;
- (void) setMarkupType: (PDFMarkupType) type;

@end
