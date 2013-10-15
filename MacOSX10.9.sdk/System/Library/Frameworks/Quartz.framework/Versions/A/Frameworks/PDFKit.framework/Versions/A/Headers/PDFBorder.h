// =====================================================================================================================
//  PDFBorder.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


@class PDFBorderPrivateVars;


// Style in which PDFBorder is displayed.
typedef NSInteger PDFBorderStyle;
enum
{
    kPDFBorderStyleSolid = 0, 
    kPDFBorderStyleDashed = 1, 
    kPDFBorderStyleBeveled = 2, 
    kPDFBorderStyleInset = 3, 
    kPDFBorderStyleUnderline = 4
};


@interface PDFBorder : NSObject <NSCopying, NSCoding>
{
@private
	PDFBorderPrivateVars *_pdfPriv;
}

// -------- accessors

// See styles above. Whether border is drawn solid, dashed etc.
- (PDFBorderStyle) style;
- (void) setStyle: (PDFBorderStyle) style;

// Width of line used to strok border.
- (CGFloat) lineWidth;
- (void) setLineWidth: (CGFloat) width;

// For rounded-rect borders, the corner radii.  Widget annotations generally do not specify a corder radius.
//- (CGFloat) horizontalCornerRadius;						DEPRECATED
//- (void) setHorizontalCornerRadius: (CGFloat) radius;		DEPRECATED
//- (CGFloat) verticalCornerRadius;							DEPRECATED
//- (void) setVerticalCornerRadius: (CGFloat) radius;		DEPRECATED

// Array of floats specifying the dash pattern (see NSBezierPath for more detail).
- (NSArray *) dashPattern;
- (void) setDashPattern: (NSArray *) pattern;

// Draw method.  Not generally needed since the annotations themselves call this method when they are drawn.
// Call -[NSColor set] before calling (the various annotations do this often calling -[PDFAnnotation color] or whatever 
// is appropriate for their class.
- (void) drawInRect: (NSRect) rect;

@end
