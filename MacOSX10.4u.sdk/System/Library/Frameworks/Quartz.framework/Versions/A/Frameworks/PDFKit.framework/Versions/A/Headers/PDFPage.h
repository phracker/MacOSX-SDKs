// ======================================================================================================================
//  PDFPage.h
// ======================================================================================================================


@class PDFDocument, PDFAnnotation, PDFSelection;


// Page boxes.
typedef int PDFDisplayBox;
enum
{
    kPDFDisplayBoxMediaBox = 0, 
    kPDFDisplayBoxCropBox = 1, 
    kPDFDisplayBoxBleedBox = 2, 
    kPDFDisplayBoxTrimBox = 3, 
    kPDFDisplayBoxArtBox = 4
};


@interface PDFPage : NSObject
{
@private
    struct PDFPagePrivateVars *_pdfPriv;
}

// -------- initializer

// Not the typical initializer - only for subclasses.  Generally PDFPage's are created by the PDFDocument as a result of 
// calling -[PDFDocument pageAtIndex: ]. If you subclass and create your own PDFPage you will need to handle methods 
// like -[boundsForBox], and -[drawInRect: withBox:].
- (id) initWithDocument: (PDFDocument *) document;

// -------- accessors

// The PDFDocument the page is associated with.
- (PDFDocument *) document;

// The page label.  Usually "1" for the first page, "2" for the second, etc.
- (NSString *) label;

// The bounds for the specified box (see defines above). Only the media box is required for a PDF. If the crop box is  
// requested and not present in the PDF, the media box is returned.  If other boxes are requested and not present, the 
// value for the crop box is returned. Throws a range exception if box is not in range.  Coordinates for the box are in 
// page space - you may need to transform the points if the page has a rotation on it.
- (NSRect) boundsForBox: (PDFDisplayBox) box;

// Set bounds for the specified box.  If the specified box did not previously exist, it will now. To remove a box pass 
// NSZeroRect for the bounds. Throws a range exception if box is not in range.
- (void) setBounds: (NSRect) bounds forBox: (PDFDisplayBox) box;

// Rotation on a page.  Must be 0, 90, 180 or 270 (negative rotations will be "normalized" to one of 0, 90, 180 or 270).
// Some PDF's have an inherent rotation and so -[rotation] may be non-zero when a PDF is first opened.
- (int) rotation;
- (void) setRotation: (int) angle;

// -------- annotations

// Array of PDFAnnotation objects (actually, more likely specific PDFAnnotation subclasses like PDFAnnotationLink, etc.).
- (NSArray *) annotations;

// Method to turn on or off the display of annotations when the page is drawn.
- (BOOL) displaysAnnotations;
- (void) setDisplaysAnnotations: (BOOL) display;

// Methods allowing annotations to be added or removed.
- (void) addAnnotation: (PDFAnnotation *) annotation;
- (void) removeAnnotation: (PDFAnnotation *) annotation;

// Hit-testing method returns the annotation at point (or NULL if none).  The point is in page-space.
- (PDFAnnotation *) annotationAtPoint: (NSPoint) point;

// -------- rendering

// Drawing method takes into account page rotation, draws in page space relative to and clipped to the box bounds.  If 
// -[displaysAnnotations] is true, also draws any page annotations. Does not clear the background (page white).
- (void) drawWithBox: (PDFDisplayBox) box;

// -------- text

// Number of characters on the page (including linefeeds and spaces inserted).
- (unsigned int) numberOfCharacters;

// String (with linefeeds and in some cases spaces inserted) representing the text on the page.
- (NSString *) string;
- (NSAttributedString *) attributedString;

// Returns the bounds in page-space of the character at index. In the unlikely event that more than one character are at 
// the specified point, only the first character encountered is returned.
- (NSRect) characterBoundsAtIndex: (int) index;

// Returns the index of the character at point (in page space).  Returns -1 if no character at point.
- (int) characterIndexAtPoint: (NSPoint) point;

// -------- selections

// Given a rect in page-space, returns a selection representing enclosed text on page.
- (PDFSelection *) selectionForRect: (NSRect) rect;

// Given a point in page-space, returns a selection representing a whole word at that point. May return NULL if no 
// character (and by extension no word) under point.
- (PDFSelection *) selectionForWordAtPoint: (NSPoint) point;

// Given a point in page-space, returns a selection representing a whole line at that point. May return NULL if no 
// character (and by extension no line) under point.
- (PDFSelection *) selectionForLineAtPoint: (NSPoint) point;

// Returns a selection representing text between startPt and endPt. Point are sorted first top to bottom, left to right.
- (PDFSelection *) selectionFromPoint: (NSPoint) startPoint toPoint: (NSPoint) endPoint;

// Given a range, returns a selection representing text within that range. Will raise an exception if the range length 
// is zero or if the range is outside the range of the characters on the page.
- (PDFSelection *) selectionForRange: (NSRange) range;

// -------- misc

// Returns PDF data (a proper PDF document) consisting of a single page (this page).  Note, external page links are not 
// preserved.
- (NSData *) dataRepresentation;

@end
