// ======================================================================================================================
//  PDFAnnotationInk.h
// ======================================================================================================================


#import "PDFAnnotation.h"


@class NSBezierPath, PDFAnnotationInkPrivateVars;


@interface PDFAnnotationInk : PDFAnnotation
{
@private
    PDFAnnotationInkPrivateVars	*_pdfPriv2;
}

// Array of NSBezierPaths that comprise the annotation.
- (NSArray *) paths;

// Add or remove paths from the annotation.
- (void) addBezierPath: (NSBezierPath *) path;
- (void) removeBezierPath: (NSBezierPath *) path;

@end
