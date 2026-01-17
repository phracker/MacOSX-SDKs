// =====================================================================================================================
//  PDFAnnotation.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFPage.h>


@class PDFAction, PDFBorder, PDFPage, PDFAnnotationPopup, PDFAnnotationPrivateVars;


@interface PDFAnnotation : NSObject <NSCopying, NSCoding>
{
@private
    PDFAnnotationPrivateVars *_pdfPriv;
}

// This is the base class for all annotations. A PDFAnnotation object by itself is not useful, only subclasses (like 
// PDFAnnotationCircle, PDFAnnotationText) are interesting. In parsing a PDF however, any unknown or unsupported 
// annotations will be represented as this base class.

// -------- initializer

// You should only call this method for the subclasses, otherwise you will get a type of nil Ñ which is not a legal 
// annotation.
- (id) initWithBounds: (NSRect) bounds;

// -------- accessors

// Returns the page the annotation is associated with (may return nil if annotation not associated with a page).
- (PDFPage *) page;

// Returns the annotation type (called "Subtype" in the PDF specification since "Annot" is the type). Examples include: 
// "Text", "Link", "Line", etc.  Required.
- (NSString *) type;

// Required for all annotations.  The bounding box in page-space of the annotation.
- (NSRect) bounds;
- (void) setBounds: (NSRect) bounds;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Optional (-[modificationDate] may return nil).  Modification date of the annotation.
- (NSDate *) modificationDate;
- (void) setModificationDate: (NSDate *) date;

// Optional (-[userName] may return nil).  Name of the user who created the annotation.
- (NSString *) userName;
- (void) setUserName: (NSString *) name;

// Optional (-[popup] may return nil).  Not used with links or widgets, a popup annotation associated with this 
// annotation.  The bounds and open state of the popup indicate the placement and open state of the popup window.
- (PDFAnnotationPopup *) popup;
- (void) setPopup: (PDFAnnotationPopup *) popup;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Indicates whether the annotation should be displayed on screen (depending upon -[shouldPrint] it may still print).
- (BOOL) shouldDisplay;
- (void) setShouldDisplay: (BOOL) display;

// Indicates whether the annotation should be printed or not.
- (BOOL) shouldPrint;
- (void) setShouldPrint: (BOOL) print;

// Optional border or border style that describes how to draw the annotation border (if any).  For the "geometry" 
// annotations (Circle, Ink, Line, Square), the border indicates the line width and whether to draw with a dash pattern 
// or solid pattern.  PDFAnnotationMarkup ignores the border.
- (PDFBorder *) border;
- (void) setBorder: (PDFBorder *) border;

// For many annotations ("Circle", "Square") the stroke color.  Used for other annotations as well.
- (NSColor *) color;
- (void) setColor: (NSColor *) color;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Optional action performed when a user releases the mouse within an annotation. PDF readers ignore actions except 
// for those associated with Link or button Widget annotations. 
- (PDFAction *) mouseUpAction;
- (void) setMouseUpAction: (PDFAction *) action;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// A string of text associated with an annotation. Often displayed in a window when the annotation is clicked on 
// ("FreeText" and "Text" especially).
- (NSString *) contents;
- (void) setContents: (NSString *) contents;

// String used for tooltips.  The base class returns [self contents], sub-classes may override as appropriate.
- (NSString *) toolTip;

// Returns YES if the annotation has an appearance stream.  Annotations with appearance streams are drawn using their 
// stream. As a result setting many parameters (like -[setColor:] above) will have no visible effect.
- (BOOL) hasAppearanceStream;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// All appearance streams for the target annotation are removed.  Without an appearance stream, annotations are drawn 
// strictly according to their parameters (color, border, font, etc.).  When a PDF is saved, PDF Kit will always 
// write out an appearance stream(s) for each annotation.  If the PDF is reloaded, you will need to remove the 
// appearance streams in order to continue to edit the annotations parameters.
- (void) removeAllAppearanceStreams;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- drawing

// Draw method.  Draws in page-space relative to origin of "box" passed in.
- (void) drawWithBox: (PDFDisplayBox) box;

@end
