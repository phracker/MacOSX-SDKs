//
//  PDFPage.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFPage is a logical representation of a PDF document's page. Typically pages are
//  retrieved from a PDFDocument, though they can be constructed from scratch via either
//  init method or initWithImage:. Pages can have their drawing methods overridden to allow
//  custom drawing. Pages own a set of annotations, and have the ability to add, mutate, or
//  remove them. Pages also expose text-selection methods, driven in page-space positions.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDocument, PDFAnnotation, PDFSelection, PDFPagePrivate, PDFAccessibilityNode;

// Page boxes.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayBox)
{
    kPDFDisplayBoxMediaBox = 0, 
    kPDFDisplayBoxCropBox = 1, 
    kPDFDisplayBoxBleedBox = 2, 
    kPDFDisplayBoxTrimBox = 3, 
    kPDFDisplayBoxArtBox = 4
};

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFPage : NSObject <NSCopying>
{
@private
	PDFPagePrivate *_private;
}

// -------- initializer

// For subclassers, just call the standard -(id) init.
// Note: -[PDFPage init] creates a new empty page with a media box set to (0.0, 0.0), [612.0, 792.0].
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Returns a PDFPage for the passed in image. An easy way to create a PDFPage from an image to add to a PDFDocument.
- (nullable instancetype)initWithImage:(PDFKitPlatformImage *)image PDFKIT_AVAILABLE(10_5, 11_0) NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The PDFDocument the page is associated with.
@property (nonatomic, readonly, weak, nullable) PDFDocument *document;

// This is the CGPDFPage associated with the PDFPage object. With this object you can call many CoreGraphics API methods.
// May return NULL if the owning document was not created from an existing PDF file or data or if the page itself was 
// created independently.
@property (nonatomic, readonly, nullable) CGPDFPageRef pageRef;

// The page label. Usually "1" for the first page, "2" for the second, etc.
@property (nonatomic, readonly, nullable) NSString *label;

// The bounds for the specified box (see defines above). Only the media box is required for a PDF. If the crop box is
// requested and not present in the PDF, the media box is returned. If other boxes are requested and not present, the 
// value for the crop box is returned. Throws a range exception if box is not in range. Coordinates for the box are in 
// page space - you may need to transform the points if the page has a rotation on it. Also, note that the bounds 
// returned are intersected with the page's media box.
- (PDFRect)boundsForBox:(PDFDisplayBox)box;

// Set bounds for the specified box. If the specified box did not previously exist, it will now. To remove a box pass 
// NSZeroRect for the bounds (you cannot however remove the media box). Throws a range exception if box is not in range.
- (void)setBounds:(PDFRect)bounds forBox:(PDFDisplayBox)box;

// Rotation on a page. Must be 0, 90, 180 or 270 (negative rotations will be "normalized" to one of 0, 90, 180 or 270).
// Some PDF's have an inherent rotation and so -[rotation] may be non-zero when a PDF is first opened.
@property (nonatomic) NSInteger rotation;

// -------- annotations

// Array of all PDFAnnotation objects on this page.
@property (nonatomic, readonly) NSArray<PDFAnnotation*> *annotations;

// Method to turn on or off the display of annotations when the page is drawn.
@property (nonatomic) BOOL displaysAnnotations;

// Methods allowing annotations to be added or removed.
- (void)addAnnotation:(PDFAnnotation *)annotation;
- (void)removeAnnotation:(PDFAnnotation *)annotation;

// Hit-testing method returns the annotation at point (or NULL if none). The point is in page-space.
- (nullable PDFAnnotation *)annotationAtPoint:(PDFPoint)point;

// -------- rendering

// This transform correctly rotates and offsets based on the given page's rotation property and the display box type.
- (CGAffineTransform)transformForBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_12, 11_0);

// Context aware rendering:

// Drawing method takes into account page rotation, draws in page space relative to and clipped to the box bounds. If
// -[displaysAnnotations] is true, also draws any page annotations. Does not clear the background (page white).
- (void)drawWithBox:(PDFDisplayBox)box toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// Given a display box, will transform the given context to take into account the rotation of the page as well as
// the origin of the box with respect to the page's base coordinates system. This is a convenience method to call
// from within -[PDFView drawPage:toContext:] or -[PDFAnnotation drawWithBox:inContext:].
- (void)transformContext:(CGContextRef)context forBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_12, 11_0);

// Convenience function that returns an image of this page, with annotations, that fits the given size.
// Note that the produced image is "size to fit": it retains the original page aspect-ratio. The size you give
// may not match the size of the returned image, but the returned image is guaranteed to be equal or less.
- (PDFKitPlatformImage *)thumbnailOfSize:(PDFSize)size forBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_13, 11_0);

// -------- text

// Number of characters on the page (including linefeeds and spaces inserted).
@property (nonatomic, readonly) NSUInteger numberOfCharacters;

// String (with linefeeds and in some cases spaces inserted) representing the text on the page.
@property (nonatomic, readonly, nullable) NSString *string;
@property (nonatomic, readonly, nullable) NSAttributedString *attributedString;

// Returns the bounds in page-space, of the character at index.
- (PDFRect)characterBoundsAtIndex:(NSInteger)index;

// Returns the index of the character at point (in page space). Returns the index of the first character if multiple characters are at this point.
// Returns NSNotFound if no character at point. Earlier version of PDFKit (prior to Lion) returned -1 if no character at point.
- (NSInteger)characterIndexAtPoint:(PDFPoint)point;

// -------- selections

// Given a rect in page-space, returns a selection representing enclosed text on page.
- (nullable PDFSelection *)selectionForRect:(PDFRect)rect;

// Given a point in page-space, returns a selection representing a whole word at that point. May return NULL if no 
// character (and by extension no word) under point. If data dectors are enabled (-[PDFView enableDataDetectors]),
// this return the smart-selection for the content at the given point.
- (nullable PDFSelection *)selectionForWordAtPoint:(PDFPoint)point;

// Given a point in page-space, returns a selection representing a whole line at that point. May return NULL if no 
// character (and by extension no line) under point.
- (nullable PDFSelection *)selectionForLineAtPoint:(PDFPoint)point;

// Returns a selection representing text between startPt and endPt. Points are sorted first top to bottom, left to right.
- (nullable PDFSelection *)selectionFromPoint:(PDFPoint)startPoint toPoint:(PDFPoint)endPoint;

// Given a range, returns a selection representing text within that range. Will clamp any range that goes out of bounds.
// Will return NULL for an empty selection.
- (nullable PDFSelection *)selectionForRange:(NSRange)range;

// -------- misc

// Returns PDF data (a proper PDF document) consisting of a single page (this page).
// NOTE: External page links are not preserved.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself. Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
@property (nonatomic, readonly, nullable) NSData *dataRepresentation;

@end

#if defined( PDFKIT_PLATFORM_OSX )

@interface PDFPage (PDFPageDeprecated)

// -------- rendering

// This method is deprecated in favor of the of the context aware -[PDFPage drawWithBox:toContext:]. If you subclass
// PDFPage, rendering code will first call -[PDFPage drawWithBox:toContext:]. If your subclass does not override the
// context-aware function, this original -[PDFPage drawWithBox:] method will be called.
// Drawing method takes into account page rotation, draws in page space relative to and clipped to the box bounds. If
// -[displaysAnnotations] is true, also draws any page annotations. Does not clear the background (page white).
- (void)drawWithBox:(PDFDisplayBox)box PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// This method is deprecated in favor of the of the context aware -[PDFPage transformContext:forBox:]. If you subclass
// PDFPage, rendering code will first call -[PDFPage transformContext:forBox:]. If your subclass does not override the
// context-aware function, this original -[PDFPage transformContextForBox:] method will be called.
// Given a display box, will transform the current context to take into account the rotation of the page as well as
// the origin of the box with respect to the page's base coordinates system.  This is a convenient method to call from
// within -[PDFView drawPage] or from within the draw method a PDFAnnotation subclass.
- (void)transformContextForBox:(PDFDisplayBox)box PDFKIT_DEPRECATED(10_5, 10_12, NA, NA);

@end

#endif


NS_ASSUME_NONNULL_END
