// ======================================================================================================================
//  PDFBorder.h
// ======================================================================================================================


@class PDFPage;


// Style in which PDFBorder is displayed.
typedef int PDFBorderStyle;

enum
{
    kPDFBorderStyleSolid = 0, 
    kPDFBorderStyleDashed = 1, 
    kPDFBorderStyleBeveled = 2, 
    kPDFBorderStyleInset = 3, 
    kPDFBorderStyleUnderline = 4
};

@interface PDFBorder : NSObject
{
@private
    struct PDFBorderPrivateVars *_pdfPriv;
}

// -------- accessors

// See styles above. Whether border is drawn solid, dashed etc.
- (PDFBorderStyle) style;
- (void) setStyle: (PDFBorderStyle) style;

// Width of line used to strok border.
- (float) lineWidth;
- (void) setLineWidth: (float) width;

// For rounded-rect borders, the corner radii.
- (float) horizontalCornerRadius;
- (void) setHorizontalCornerRadius: (float) radius;
- (float) verticalCornerRadius;
- (void) setVerticalCornerRadius: (float) radius;

// Array of floats specifying the dash pattern (see NSBezierPath for more detail).
- (NSArray *) dashPattern;
- (void) setDashPattern: (NSArray *) pattern;

// Draw method.
- (void) drawInRect: (NSRect) rect;

@end
