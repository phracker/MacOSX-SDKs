// =====================================================================================================================
//  PDFAnnotationInk.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationInkPrivateVars;


@interface PDFAnnotationInk : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationInkPrivateVars	*_pdfPriv2;
}

// Array of NSBezierPaths that comprise the annotation.
- (NSArray *) paths;

// Add or remove paths from the annotation.
// Path points are specified relative to the annotation's bound's origin.
- (void) addBezierPath: (NSBezierPath *) path;
- (void) removeBezierPath: (NSBezierPath *) path;

@end
