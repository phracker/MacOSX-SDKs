// ======================================================================================================================
//  PDFAnnotationLink.h
// ======================================================================================================================


#import "PDFAnnotation.h"


@class PDFDestination, PDFAnnotationLinkPrivateVars;


@interface PDFAnnotationLink : PDFAnnotation
{
@private
    PDFAnnotationLinkPrivateVars *_pdfPriv2;
}

// Destination for the link.
- (PDFDestination *) destination;
- (void) setDestination: (PDFDestination *) destination;

// URL for the link.
- (NSURL *) URL;
- (void) setURL: (NSURL *) url;

// The highlight state dictates how the annotation is drawn. If a user has clicked on a 
// "Link" annotation, you should set highlighted to YES and redraw it. When the user lets up, set highlighted to 
// NO and redraw again.
- (void) setHighlighted: (BOOL) flag;

@end
