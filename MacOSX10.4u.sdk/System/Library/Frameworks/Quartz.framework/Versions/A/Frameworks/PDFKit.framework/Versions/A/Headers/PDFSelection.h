// ======================================================================================================================
//  PDFSelection.h
// ======================================================================================================================


@class PDFPage, PDFDestination, PDFSelectionPrivateVars;


@interface PDFSelection : NSObject
{
@private
    PDFSelectionPrivateVars *_pdfPriv;
}

// -------- accessors

// Array of pages covered by the selection.  These are sorted by page index.
- (NSArray *) pages;

// String representing the text covered by the selection. May contain line-feeds.
- (NSString *) string;
- (NSAttributedString *) attributedString;

// Given a PDFPage, returns the bounds in page-space of the text covered by the selection on that page.
- (NSRect) boundsForPage: (PDFPage *) page;

// -------- modifying

// Add a selection to this selection. Selections do not have to be contiguous. If the selection added overlaps with this 
// selection, overlaps are removed.
- (void) addSelection: (PDFSelection *) selection;

// Extends the selection at either end. Selections can be extended right off onto neighboring pages even to include the 
// entire PDF document.
- (void) extendSelectionAtEnd: (int) chars;
- (void) extendSelectionAtStart: (int) chars;

// -------- rendering

// Calls the below method passing kPDFDisplayBoxCropBox for box.
- (void) drawForPage: (PDFPage *) page active: (BOOL) active;

// Draws the selection in page space relative to the origin of box.  Box can be kPDFDisplayBoxMediaBox, 
// kPDFDisplayBoxCropBox, kPDFDisplayBoxBleedBox, kPDFDisplayBoxTrimBox or kPDFDisplayBoxArtBox. If active is true, it 
// is drawn using -[NSColor selectedTextBackgroundColor], otherwise it is drawn using 
// -[NSColor secondarySelectedControlColor].
- (void) drawForPage: (PDFPage *) page withBox: (PDFDisplayBox) box active: (BOOL) active;

@end
