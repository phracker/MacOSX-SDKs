// =====================================================================================================================
//  PDFAnnotationLink.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFDestination, PDFAnnotationLinkPrivateVars;


@interface PDFAnnotationLink : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationLinkPrivateVars *_pdfPriv2;
}

// Destination for the link. May be nil if no destination associated with link; in this case the -[URL] may be valid.
// The preferred way though is to call -[PDFAnnotation mouseUpAction] and -[PDFAnnotation setMouseUpAction].
- (PDFDestination *) destination;
- (void) setDestination: (PDFDestination *) destination;

// URL for the link. May be nil if no URL action associated with link; in this case the -[destination] may be valid.
// The preferred way though is to call -[PDFAnnotation mouseUpAction] and -[PDFAnnotation setMouseUpAction].
- (NSURL *) URL;
- (void) setURL: (NSURL *) url;

// The highlight state dictates how the annotation is drawn. If a user has clicked on a 
// "Link" annotation, you should set highlighted to YES and redraw it. When the user lets up, set highlighted to 
// NO and redraw again.
- (void) setHighlighted: (BOOL) flag;

@end
