//
//  PDFAnnotationSquare.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationSquarePrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationSquare : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationSquarePrivateVars	*_private2;
}

// Fill color used for drawing annotation (optional, PDF 1.4).
- (PDFKitPlatformColor *) interiorColor;
- (void) setInteriorColor: (PDFKitPlatformColor *) color;

@end
