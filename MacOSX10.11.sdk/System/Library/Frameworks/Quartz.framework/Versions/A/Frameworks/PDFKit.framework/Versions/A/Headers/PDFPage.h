// =====================================================================================================================
//  PDFPage.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


@class PDFDocument, PDFAnnotation, PDFPagePrivateVars, PDFSelection;


// Page boxes.
typedef NSInteger PDFDisplayBox;
enum
{
    kPDFDisplayBoxMediaBox = 0, 
    kPDFDisplayBoxCropBox = 1, 
    kPDFDisplayBoxBleedBox = 2, 
    kPDFDisplayBoxTrimBox = 3, 
    kPDFDisplayBoxArtBox = 4
};


@interface PDFPage : NSObject <NSCopying>
{
@private
	PDFPagePrivateVars *_pdfPriv;
}

// -------- initializer

// For subclassers, just call the standard -(id) init.  
// Note: -[PDFPage init] create a new empty page with a media box set to (0.0, 0.0), [612.0, 792.0].

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Returns a PDFPage for the NSImage passed in. An easy way to create a PDFPage from an image to add to a PDFDocument.
- (id) initWithImage: (NSImage *) image;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5


// -------- accessors

// The PDFDocument the page is associated with.
- (PDFDocument *) document;

// This is the CGPDFPage associated with the PDFPage object.  With this object you can call many CoreGraphics API.
// May return NULL if the owning document was not created from an existing PDF file or data or if the page itself was 
// created independently.
- (CGPDFPageRef) pageRef;

// The page label.  Usually "1" for the first page, "2" for the second, etc.
- (NSString *) label;

// The bounds for the specified box (see defines above). Only the media box is required for a PDF. If the crop box is  
// requested and not present in the PDF, the media box is returned.  If other boxes are requested and not present, the 
// value for the crop box is returned. Throws a range exception if box is not in range.  Coordinates for the box are in 
// page space - you may need to transform the points if the page has a rotation on it. Also, note that the bounds 
// returned are intersected with the page's media box.
- (NSRect) boundsForBox: (PDFDisplayBox) box;

// Set bounds for the specified box.  If the specified box did not previously exist, it will now. To remove a box pass 
// NSZeroRect for the bounds (you cannot however remove the media box). Throws a range exception if box is not in range.
- (void) setBounds: (NSRect) bounds forBox: (PDFDisplayBox) box;

// Rotation on a page.  Must be 0, 90, 180 or 270 (negative rotations will be "normalized" to one of 0, 90, 180 or 270).
// Some PDF's have an inherent rotation and so -[rotation] may be non-zero when a PDF is first opened.
- (NSInteger) rotation;
- (void) setRotation: (NSInteger) angle;

// -------- annotations

// Array of PDFAnnotation objects (actually, specific PDFAnnotation subclasses like PDFAnnotationLink, etc.).
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

// Drawing method takes into account page rotation, draws in page space relative to and clipped to the box bounds. If 
// -[displaysAnnotations] is true, also draws any page annotations. Does not clear the background (page white).
- (void) drawWithBox: (PDFDisplayBox) box;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Given a display box, will transform the current context to take into account the rotation of the page as well as 
// the origin of the box with repect to the page's base coordinates system.  This is a convenient method to call from 
// within -[PDFView drawPage] or from within the draw method a PDFAnnotation subclass.
- (void) transformContextForBox: (PDFDisplayBox) box;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- text

// Number of characters on the page (including linefeeds and spaces inserted).
- (NSUInteger) numberOfCharacters;

// String (with linefeeds and in some cases spaces inserted) representing the text on the page.
- (NSString *) string;
- (NSAttributedString *) attributedString;

// Returns the bounds in page-space of the character at index. In a case where there is more than one character are at 
// the specified point, only the first character encountered is returned.
- (NSRect) characterBoundsAtIndex: (NSInteger) index;

// Returns the index of the character at point (in page space).  Returns NSNotFound if no character at point.
// Earlier version of PDF Kit (prior to Lion) returned -1 if no character at point.
- (NSInteger) characterIndexAtPoint: (NSPoint) point;

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

// Returns PDF data (a proper PDF document) consisting of a single page (this page).
// NOTE: External page links are not preserved.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself.  Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
- (NSData *) dataRepresentation;

@end
