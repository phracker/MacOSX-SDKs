// ======================================================================================================================
//  PDFAnnotationMarkup.h
// ======================================================================================================================


#import "PDFAnnotation.h"

// TEMP MAKE ENUM
#define kPDFMarkupTypeHighlight				0
#define kPDFMarkupTypeStrikeOut				1
#define kPDFMarkupTypeUnderline				2

@class PDFAnnotationMarkupPrivateVars;

@interface PDFAnnotationMarkup : PDFAnnotation
{
@private
    PDFAnnotationMarkupPrivateVars *_pdfPriv2;
}

// Array of (n * 4) NSPoints defining n quadrilaterals in page space where n is the number of quad points. 
// The point quads are ordered counter-clockwise.
- (NSArray *) quadrilateralPoints;
- (void) setQuadrilateralPoints: (NSArray *) points;

// Type of mark-up (highlight, strike-out or underline).  Changing the markup type also changes the annotations type to 
// one of: "Highlight", "Strikeout", or "Underline" (these are three seperate annotation types treated here as three 
// seperate flavors of the one PDFAnnotationMarkup class).
- (int) markupType;
- (void) setMarkupType: (int) type;

@end
