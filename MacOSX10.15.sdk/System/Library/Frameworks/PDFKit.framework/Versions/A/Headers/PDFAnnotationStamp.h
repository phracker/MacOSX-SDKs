//
//  PDFAnnotationStamp.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationStampPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_5, 10_12, NA, NA)
@interface PDFAnnotationStamp : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationStampPrivateVars	*_private2;
}

// Name of stamp annotation. Standard stamps include names like, "Approved", "Draft", "TopSecret", etc.
// The name must be representable as ASCII. Very little is rendered if the annotation has no appearance stream.
- (NSString *) name;
- (void) setName: (NSString *) name;

@end
