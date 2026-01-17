//
//  PDFAnnotationText.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

#import <PDFKit/PDFAnnotationUtilities.h>

@class PDFAnnotationTextPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationText : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationTextPrivateVars *_private2;
}

// The type of icon displayed in the PDF. Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph", "Paragraph" and "Insert".
- (PDFTextAnnotationIconType) iconType;
- (void) setIconType: (PDFTextAnnotationIconType) type;

@end
