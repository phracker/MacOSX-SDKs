// ======================================================================================================================
//  PDFView.h
// ======================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFPage.h>


@class PDFDestination, PDFDocument, PDFPage, PDFSelection, PDFViewPrivateVars;


// Display modes.
typedef int PDFDisplayMode;
enum
{
    kPDFDisplaySinglePage = 0, 
    kPDFDisplaySinglePageContinuous = 1, 
    kPDFDisplayTwoUp = 2, 
    kPDFDisplayTwoUpContinuous = 3
};

// PDF areas of interest (bitfield, multiple bits below may be set).
typedef int PDFAreaOfInterest;
enum
{
    kPDFNoArea = 0, 
    kPDFPageArea = 1, 
    kPDFTextArea = 2, 
    kPDFAnnotationArea = 4, 
    kPDFLinkArea = 8, 
    kPDFControlArea = 16, 
    kPDFTextFieldArea = 32, 
    kPDFPopupArea = 64
};


// Notifications.
extern NSString *PDFViewDocumentChangedNotification;	// Notification when a new document is associated with view.
extern NSString *PDFViewChangedHistoryNotification;		// Notification when the page history changes.
extern NSString *PDFViewPageChangedNotification;		// Notification when a new page becomes current.
extern NSString *PDFViewScaleChangedNotification;		// Notification when the scale changes.
extern NSString *PDFViewAnnotationHitNotification;		// Notification when the user clicks on an annotation.
extern NSString *PDFViewCopyPermissionNotification;		// Notification when the user is denied copy (permissions).
extern NSString *PDFViewPrintPermissionNotification;	// Notification when the user is denied print (permissions).


@interface PDFView : NSView
{
@private
    PDFViewPrivateVars *_pdfPriv;
}

// -------- document

// Methods for associating a PDFDocument with a PDFView.
- (PDFDocument *) document;
- (void) setDocument: (PDFDocument *) document;

// -------- page navigation

// Simple page navigation methods.
- (BOOL) canGoToFirstPage;
- (IBAction) goToFirstPage: (id) sender;
- (BOOL) canGoToLastPage;
- (IBAction) goToLastPage: (id) sender;
- (BOOL) canGoToNextPage;
- (IBAction) goToNextPage: (id) sender;
- (BOOL) canGoToPreviousPage;
- (IBAction) goToPreviousPage: (id) sender;

// Back and forward refer to your page "history" (think Web browsers back and forward buttons). Initially of course you 
// have no history.  But as you call other methods like -[goToDestination] and -[goToLastPage] (for example) a history 
// is recorded.  -[goBack] then works you back through that history.
- (BOOL) canGoBack;
- (IBAction) goBack: (id) sender;
- (BOOL) canGoForward;
- (IBAction) goForward: (id) sender;

// Returns the current page you are on. For two-up modes, it is the left page (if there are two). For continuous modes, 
// it finds the page crossing a horizontal line halfway betwene the views top and bottom bounds.
- (PDFPage *) currentPage;

// Scrolls to page.
- (void) goToPage: (PDFPage *) page;

// Returns a PDFDestination representing the current page and point displayed (see -[currentPage] for more comments).
- (PDFDestination *) currentDestination;

// Goes to the specified destination.
- (void) goToDestination: (PDFDestination *) destination;

// Goes to the specified selection (since selections can be large, goes to the first character of the selection).
- (void) goToSelection: (PDFSelection *) selection;

// -------- display mode

// See PDFDisplayMode constants above.  Default is kPDFDisplaySinglePageContinuous.
- (void) setDisplayMode: (PDFDisplayMode) mode;
- (PDFDisplayMode) displayMode;

// Toggle displaying or not displaying page breaks between pages.
- (void) setDisplaysPageBreaks: (BOOL) breaks;
- (BOOL) displaysPageBreaks;

// Specifies the box to display/clip to. Default is kPDFDisplayBoxCropBox.
- (void) setDisplayBox: (PDFDisplayBox) box;
- (PDFDisplayBox) displayBox;

// Specifies whether the first page is to be treated as a cover and (for two-up modes) displayed by itself.
- (void) setDisplaysAsBook: (BOOL) asBook;
- (BOOL) displaysAsBook;

// State of anti-aliasing when drawing. Default is YES.
- (void) setShouldAntiAlias: (BOOL) aliasing;
- (BOOL) shouldAntiAlias;

// Greeking threshold to apply to text displayed. Default is 3.0.
- (void) setGreekingThreshold: (float) threshold;
- (float) greekingThreshold;

// The background color is the color of the space behind the PDF pages (and betwen them if page breaks is enabled).
// Default is a 50% gray.
- (IBAction) takeBackgroundColorFrom: (id) sender;
- (void) setBackgroundColor: (NSColor *) newColor;
- (NSColor *) backgroundColor;

// -------- delgate

- (void) setDelegate: (id) anObject;
- (id) delegate;

// -------- scaling

// Methods to change the scaling on the displayed PDF document. Default is 1.0 (actual size).
- (void) setScaleFactor: (float) scale;
- (float) scaleFactor;

// Zooming changes the scaling by root-2.
- (IBAction) zoomIn: (id) sender;
- (BOOL) canZoomIn;
- (IBAction) zoomOut: (id) sender;
- (BOOL) canZoomOut;

// Toggles mode whereby the scale factor is automatically changed as the view is resized to maximize the PDF displayed.
// For continuous modes this is a "fit width" behavior, for non-continuous modes it is a "best fit" behavior.
- (void) setAutoScales: (BOOL) newAuto;
- (BOOL) autoScales;

// -------- events

// Returns type of area (see defines above) mouse is over. This method is useful for subclasses.
- (PDFAreaOfInterest) areaOfInterestForMouse: (NSEvent *) theEvent;

// Sets the appropriate cursor for a given area of interest. This method is useful for subclasses.
- (void) setCursorForAreaOfInterest: (PDFAreaOfInterest) area;

// -------- selection

// Allows access to the current selection.  View will redraw as necessary. View will not scroll.
// Call -[scrollSelectionToVisible:] to scroll to the current selection.
- (PDFSelection *) currentSelection;
- (void) setCurrentSelection: (PDFSelection *) selection;
- (void) clearSelection;
- (IBAction) selectAll: (id) sender;
- (void) scrollSelectionToVisible: (id) sender;

// -------- password

// Convenience method.  Calls -[[self document] unlockWithPassword:] with the password from sender.
- (void) takePasswordFrom: (id) sender;

// -------- rendering

// For subclasses. This method is called for each visible page requiring rendering.  By subclassing you can draw on top 
// of the PDF page or draw the page entirely yourself. Default implementation erases page to white and calls:
// [page drawInRect: pageRect withBox: [self displayBox]], then draws the selection if any.
- (void) drawPage: (PDFPage *) page;

// -------- pasteboard

// Copy the selection (if any) to the pasteboard.
- (void) copy: (id) sender;

// -------- printing

// Print the PDF document.  If autoRotate is YES, will ignore the orientation attribute in printInfo and rather choose 
// the orientation on a page by page basis that best fits the page to the paper size.
- (void) printWithInfo: (NSPrintInfo *) printInfo autoRotate: (BOOL) doRotate;

// -------- conversion

// Useful for subclasses. Given a point in view coordinates, returns the page at that point. May return NULL if no page 
// at point and nearest is NO.
- (PDFPage *) pageForPoint: (NSPoint) point nearest: (BOOL) nearest;

// Converts a point from view coordinates to page coordinates.
- (NSPoint) convertPoint: (NSPoint) point toPage: (PDFPage *) page;

// Converts a rect from view coordinates to page coordinates.
- (NSRect) convertRect: (NSRect) rect toPage: (PDFPage *) page;

// Converts a point from page coordinates to view coordinates.
- (NSPoint) convertPoint: (NSPoint) point fromPage: (PDFPage *) page;

// Converts a rect from page coordinates to view coordinates.
- (NSRect) convertRect: (NSRect) rect fromPage: (PDFPage *) page;

// -------- misc

// Returns the innermost view used by PDFView.  This is the view representing the displayed document pages.
- (id) documentView;

// Tells PDFView to calculate (layout) the inner views. Called automatically when -[setDocument] and -[setDisplayBox]
// are called. You'll need to inform the view of a change if you add or remove a page on the document, rotate a page etc.
- (void) layoutDocumentView;

// Handy for initially sizing PDFView.  Returns the size needed to display the 'row' of the view's current document  
// containing the specified page at the current scale factor and with the current display attributes.
- (NSSize) rowSizeForPage: (PDFPage *) page;

// Indicate whether dragging is allowed.  If NO (default), dragging events are not supported.  If YES, a user can drag 
// a PDF file to the view and a new document is associated with the view (the old document is released).
- (void) setAllowsDragging: (BOOL) allow;
- (BOOL) allowsDragging;

@end

@interface NSObject(PDFViewDelegate)

// Delegate method allowing a delgate to override changes to the scale factor. The default implementation pins scaling 
// between 0.1 and 10.0.
- (float) PDFViewWillChangeScaleFactor: (PDFView *) sender toScale: (float) scale;

// Delegates implementing the following method will be called to handle clicks on URL links within the PDFView.  The 
// default implementation calls [[NSWorkspace sharedWorkspace] openURL: url].
- (void) PDFViewWillClickOnLink: (PDFView *) sender withURL: (NSURL *) url;

@end
