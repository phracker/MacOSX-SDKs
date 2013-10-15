// ======================================================================================================================
//  PDFAnnotation.h
// ======================================================================================================================


#import <PDFKit/PDFPage.h>


@class NSColor, PDFBorder, PDFPage, PDFAnnotationPrivateVars;


@interface PDFAnnotation : NSObject
{
@private
    PDFAnnotationPrivateVars *_pdfPriv;
}

// This is the base class for all annotations. A PDFAnnotation object by itself is not useful, only the subclasses (like 
// PDFAnnotationCircle, PDFAnnotationText) are interesting. In parsing a PDF however, any unknown or unsupported 
// annotations will be represented as this base class.  Its -[drawRect] method merely frames the bounds of the 
// annotation and prints the annotation type (like "TrapNet") within the box.

// -------- initializer

// You should only call this method for the subclasses, otherwise you will get a type of NULL Ñ which is not a legal 
// annotation.
- (id) initWithBounds: (NSRect) bounds;

// -------- accessors

// Returns the page the annotation is associated with.
- (PDFPage *) page;

// Returns the annotation type (called "Subtype" in the PDF specification since "Annot" is the type).  Examples include:
// "Text", "Link", "Line", etc.
- (NSString *) type;

// Specifies whether it should be drawn to the display or not.
- (BOOL) shouldDisplay;
- (void) setShouldDisplay: (BOOL) display;

// Specifies whether it should be printed or not.
- (BOOL) shouldPrint;
- (void) setShouldPrint: (BOOL) print;

// A string of text associated with an annotation. Often to be displayed in a pop-up when the annotation is clicked on 
// ("FreeText" and "Text" especially).
- (NSString *) contents;
- (void) setContents: (NSString *) contents;

// String used for tooltips.  The base class returns [self contents], sub-classes may override as appropriate.
- (NSString *) toolTip;

// Required for all annotations.  The bounding box in page-space of the annotation.
- (NSRect) bounds;
- (void) setBounds: (NSRect) bounds;

// Optional border or border style that describes how to draw the annoation border (if any).
- (PDFBorder *) border;
- (void) setBorder: (PDFBorder *) border;

// For many annotations ("Circle", "Square") the stroke color.  Used for other annotations as well.
- (NSColor *) color;
- (void) setColor: (NSColor *) color;

// Returns YES if the annotation has an appearance stream.  Annotations with appearance streams are drawn using their 
// stream. As a result, setting many parameters (like 'setColor' above), will have no visible effect.
- (BOOL) hasAppearanceStream;

// -------- drawing

// Draw method.  Draws in page-space relative to origin of "box" passed in.
- (void) drawWithBox: (PDFDisplayBox) box;

@end
