// =====================================================================================================================
//  PDFBorder.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFBorderPrivateVars;

// Style in which PDFBorder is displayed.
NS_ENUM_AVAILABLE_MAC(10_4)
typedef NS_ENUM(NSInteger, PDFBorderStyle)
{
    kPDFBorderStyleSolid = 0, 
    kPDFBorderStyleDashed = 1, 
    kPDFBorderStyleBeveled = 2, 
    kPDFBorderStyleInset = 3, 
    kPDFBorderStyleUnderline = 4
};

// PDFBorder is not directly an annotation, but instead is a supportive structure common to a few annotations
NS_CLASS_AVAILABLE_MAC(10_4)
@interface PDFBorder : NSObject <NSCopying, NSCoding>
{
@private
	PDFBorderPrivateVars *_private;
}

// -------- accessors

// See styles above. Whether border is drawn solid, dashed etc.
@property(nonatomic, assign) PDFBorderStyle style;

// Width of line used to strok border.
@property(nonatomic, assign) CGFloat lineWidth;

// Array of floats specifying the dash pattern (see NSBezierPath for more detail).
@property(nonatomic, retain, nullable) NSArray* dashPattern;

// Draw method.  Not generally needed since the annotations themselves call this method when they are drawn.
// Call -[NSColor set] before calling (the various annotations do this often calling -[PDFAnnotation color] or whatever 
// is appropriate for their class.
- (void) drawInRect: (PDFRect) rect;

@end

NS_ASSUME_NONNULL_END
