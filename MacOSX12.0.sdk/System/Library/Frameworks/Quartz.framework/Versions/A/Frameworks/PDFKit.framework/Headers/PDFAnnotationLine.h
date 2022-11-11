//
//  PDFAnnotationLine.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

#import <PDFKit/PDFAnnotationUtilities.h>

@class PDFAnnotationLinePrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
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
