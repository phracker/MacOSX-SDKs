//
//  PDFAnnotationPopup.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationPopupPrivateVars;

PDFKIT_ENUM_DEPRECATED(10_5, 10_12, NA, NA)
@interface PDFAnnotationPopup : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationPopupPrivateVars	*_private2;
}

- (BOOL) isOpen;
- (void) setIsOpen: (BOOL) isOpen;

@end
