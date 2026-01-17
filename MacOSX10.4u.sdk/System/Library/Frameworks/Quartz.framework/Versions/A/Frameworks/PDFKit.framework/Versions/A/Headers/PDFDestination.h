// ======================================================================================================================
//  PDFDestination.h
// ======================================================================================================================


@class PDFPage, PDFDestinationPrivateVars;


@interface PDFDestination : NSObject
{
@private
    PDFDestinationPrivateVars *_pdfPriv;
}

// -------- initializer

// Initializer.  You do not often create PDFDestinations but get them from link annotations or PDF outline items.
- (id) initWithPage: (PDFPage *) page atPoint: (NSPoint) point;

// -------- accessors

// Page the destination refers to (destination page).
- (PDFPage *) page;

// Destination point on the page above (in page space).
- (NSPoint) point;

@end
