// ======================================================================================================================
//  PDFOutline.m
// ======================================================================================================================


@class PDFDocument, PDFDestination, PDFOutlinePrivateVars;


@interface PDFOutline : NSObject
{
@private
    PDFOutlinePrivateVars *_pdfPriv;
}

// -------- initializer

// May return NULL if document does not contain an outline. Equivalent to calling -[PDFDocument outlineRoot];
- (id) initWithDocument: (PDFDocument *) document;

// -------- accessors

// The PDFDocument the outline is asscoiated with.
- (PDFDocument *) document;

// Number of PDFOutline children this PDFOutline has.
- (int) numberOfChildren;

// PDFOutline child at index.  Will throw exception if index is out of range.
- (PDFOutline *) childAtIndex: (int) index;

// The label for the outline.  The root PDFOutline has no label and is only a container for children PDFOutlines.
- (NSString *) label;

// The destination asscoiated with the outline item.  The root PDFOutline has no destination.
- (PDFDestination *) destination;

@end
