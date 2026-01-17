//
//  PDFAnnotationLink.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFDestination, PDFAnnotationLinkPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationLink : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationLinkPrivateVars *_private2;
}

// Destination for the link. May be nil if no destination associated with link; in this case the -[URL] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
- (PDFDestination *) destination;
- (void) setDestination: (PDFDestination *) destination;

// URL for the link. May be nil if no URL action associated with link; in this case the -[destination] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
- (NSURL *) URL;
- (void) setURL: (NSURL *) url;

@end
