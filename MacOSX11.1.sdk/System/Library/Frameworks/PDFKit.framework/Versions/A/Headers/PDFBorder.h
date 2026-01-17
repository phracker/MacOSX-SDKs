//
//  PDFBorder.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFBorder represents an array structure that is common for graphical annotations,
//  defining properties like line-stroke width, color, and dashed patterns.
//  It is designed to be a representation of the /BS entry in the annotation dictionary.
//
//  Properties are based on the Adobe PDF Specification (1.7)
//  Table 8.17: Entries in a border style dictionary.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFBorderPrivateVars;

// Style in which PDFBorder is displayed.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFBorderStyle)
{
    kPDFBorderStyleSolid = 0, 
    kPDFBorderStyleDashed = 1, 
    kPDFBorderStyleBeveled = 2, 
    kPDFBorderStyleInset = 3, 
    kPDFBorderStyleUnderline = 4
};

// Border style dictionary keys.
typedef NSString* const PDFBorderKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFBorderKey PDFBorderKeyLineWidth PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFBorderKey PDFBorderKeyStyle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFBorderKey PDFBorderKeyDashPattern PDFKIT_AVAILABLE(10_13, 11_0);

// PDFBorder is not directly an annotation, but instead is a supportive structure common to a few annotations.
PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFBorder : NSObject <NSCopying, NSCoding>
{
@private
	PDFBorderPrivateVars *_private;
}

// -------- accessors

// See styles above. Whether border is drawn solid, dashed etc.
@property (nonatomic) PDFBorderStyle style;

// Width of line used to stroke border.
@property (nonatomic) CGFloat lineWidth;

// Array of floats specifying the dash pattern (see NSBezierPath for more detail).
@property (nonatomic, copy, nullable) NSArray *dashPattern;

// List all border properties as key-value pairs; returns a deep copy of all pairs. Helpful for debugging.
@property (nonatomic, readonly, copy) NSDictionary *borderKeyValues;

// Draw method. Not generally needed since the annotations themselves call this method when they are drawn.
// Call -[NSColor set] before calling (the various annotations do this often calling -[PDFAnnotation color] or whatever 
// is appropriate for their class.
- (void)drawInRect:(PDFRect)rect;

@end

NS_ASSUME_NONNULL_END
