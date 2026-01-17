// =====================================================================================================================
//  PDFView.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFDocument.h>
#import <PDFKit/PDFPage.h>


@class PDFAction, PDFActionRemoteGoTo, PDFDestination, PDFSelection, PDFViewPrivateVars;


// Display modes.
typedef NSInteger PDFDisplayMode;
enum
{
    kPDFDisplaySinglePage = 0, 
    kPDFDisplaySinglePageContinuous = 1, 
    kPDFDisplayTwoUp = 2, 
    kPDFDisplayTwoUpContinuous = 3
};

// PDF areas of interest (bitfield, multiple bits below may be set).
typedef NSInteger PDFAreaOfInterest;
enum
{
    kPDFNoArea = 0, 
    kPDFPageArea = 1, 
    kPDFTextArea = 2, 
    kPDFAnnotationArea = 4, 
    kPDFLinkArea = 8, 
    kPDFControlArea = 16, 
    kPDFTextFieldArea = 32, 
    kPDFIconArea = 64, 
    kPDFPopupArea = 128,
    kPDFImageArea = 256
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// Interpolation quality.
typedef NSInteger PDFInterpolationQuality;
enum
{
    kPDFInterpolationQualityNone = 0, 
    kPDFInterpolationQualityLow = 1, 
    kPDFInterpolationQualityHigh = 2
};

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7


// Notifications.
extern NSString *PDFViewDocumentChangedNotification;	// Notification when a new document is associated with view.
extern NSString *PDFViewChangedHistoryNotification;		// Notification when the page history changes.
extern NSString *PDFViewPageChangedNotification;		// Notification when a new page becomes current.
extern NSString *PDFViewScaleChangedNotification;		// Notification when the scale changes.
extern NSString *PDFViewAnnotationHitNotification;		// Notification when the user clicks on an annotation.
extern NSString *PDFViewCopyPermissionNotification;		// Notification when the user is denied copy (permissions).
extern NSString *PDFViewPrintPermissionNotification;	// Notification when the user is denied print (permissions).

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

extern NSString *PDFViewAnnotationWillHitNotification;	// Notification before user clicks on an annotation.
extern NSString *PDFViewSelectionChangedNotification;	// Notification when the current selection has changed.
extern NSString *PDFViewDisplayModeChangedNotification;	// Notification when the display mode has changed.
extern NSString *PDFViewDisplayBoxChangedNotification;	// Notification when the display box has changed.

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

extern NSString *PDFViewVisiblePagesChangedNotification;  // Notification when the scroll view has scrolled into the bounds of a new page.


@interface PDFView : NSView <NSAnimationDelegate, NSMenuDelegate>
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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Goes to the specified rectangle on the specified page.  If already visible, does nothing.  This allows you to scroll 
// the PDFView to a specific PDFAnnotation or PDFSelection (since both object have bounds methods).
// Note: rect is specified in page coordinates.
- (void) goToRect: (NSRect) rect onPage: (PDFPage *) page;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

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
- (void) setGreekingThreshold: (CGFloat) threshold;
- (CGFloat) greekingThreshold;

// The background color is the color of the space behind the PDF pages (and between them if page breaks is enabled).
// Default is a 50% gray.
- (IBAction) takeBackgroundColorFrom: (id) sender;
- (void) setBackgroundColor: (NSColor *) newColor;
- (NSColor *) backgroundColor;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// Allows setting the interpolation quality for images drawn into the PDFView context. 
- (void) setInterpolationQuality: (PDFInterpolationQuality) quality;
- (PDFInterpolationQuality) interpolationQuality;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// -------- delgate

- (void) setDelegate: (id) anObject;
- (id) delegate;

// -------- scaling

// Methods to change the scaling on the displayed PDF document. Default is 1.0 (actual size).
- (void) setScaleFactor: (CGFloat) scale;
- (CGFloat) scaleFactor;

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
- (PDFAreaOfInterest) areaOfInterestForMouse: (NSEvent *) event;
- (PDFAreaOfInterest) areaOfInterestForPoint: (NSPoint) cursorLocation;

// Sets the appropriate cursor for a given area of interest. This method is useful for subclasses.
- (void) setCursorForAreaOfInterest: (PDFAreaOfInterest) area;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Performs the action specified by action.
- (void) performAction: (PDFAction *) action;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- selection

// Returns actual instance of the current PDFSelection object.  If you wish to modify this, you should make a copy of 
// the selection returned and modify that instead. Method may return nil if there is no selection.
- (PDFSelection *) currentSelection;

// Set current selection to selection.  The view will redraw as necessary. The view will not scroll.
// Call -[scrollSelectionToVisible:] to scroll to the current selection.
- (void) setCurrentSelection: (PDFSelection *) selection;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Like -[setCurrentSelection:] above but with the additional parameter that specifies whether setting the selection 
// should be animated.  The animation draws the user's attention to the new selection.  Useful when searching.
- (void) setCurrentSelection: (PDFSelection *) selection animate: (BOOL) animate;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Equivalent to -[PDFView setCurrentSelection: nil].
- (void) clearSelection;
- (IBAction) selectAll: (id) sender;

// If the selection is not visible, scrolls view so that it is.
- (void) scrollSelectionToVisible: (id) sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// The following calls allow you to associate an array of PDFSelections with a PDFView.  Unlike the user selection 
// (above), these selections do not go away when the user clicks in the PDFView, etc.  You must explicitly remove them 
// by passing nil to -[setHighlightedSelections:].  These methods allow you to highlight text perhaps to indicate 
// matches from a text search. To avoid confusion you should probably make sure the PDFSelections passed in are a 
// different color from the user's default text selection color.
- (void) setHighlightedSelections: (NSArray *) selections;
- (NSArray *) highlightedSelections;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- password

// Convenience method.  Calls -[[self document] unlockWithPassword:] with the password from sender.
- (void) takePasswordFrom: (id) sender;

// -------- rendering

// For subclasses. This method is called for each visible page requiring rendering.  By subclassing you can draw on top 
// of the PDF page or draw the page entirely yourself. Default implementation erases page to white and calls:
// [page drawWithBox: [self displayBox]], then draws the selection if any.
- (void) drawPage: (PDFPage *) page;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Also a handy method for sub-classing.  Called for post-page rendering. In this method however no scaling/rotating is 
// applied to the current context to map to page-space.  The context is in "view-space" coordinates.  The default 
// implementation of this method draws the text highlighting (if any) for page.
- (void) drawPagePost: (PDFPage *) page;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- pasteboard

// Copy the selection (if any) to the pasteboard.
- (void) copy: (id) sender;

// -------- printing

// Print the PDF document.  If autoRotate is YES, will ignore the orientation attribute in printInfo and rather choose 
// the orientation on a page by page basis that best fits the page to the paper size.
- (void) printWithInfo: (NSPrintInfo *) printInfo autoRotate: (BOOL) doRotate;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Like the above method but allows an additional parameter to describe page scaling (see PDFDocument.h for types).
// If pageScaling is equal to kPDFPrintPageScaleToFit each pages is scaled up or down in order to best fit the paper 
// size. Specifying kPDFPrintPageScaleDownToFit for pageScaling will only scale large pages down to fit the paper, 
// smaller pages will nto be scaled up.  Passing pageScaling equal to kPDFPrintPageScaleNone is the equivalent of 
// calling -[printWithInfo: autoRotate] above.
- (void) printWithInfo: (NSPrintInfo *) printInfo autoRotate: (BOOL) doRotate pageScaling: (PDFPrintScalingMode) scale;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- conversion

// Useful for subclasses. Given a point in view coordinates, returns the page at that point. May return nil if no page 
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
- (NSView *) documentView;

// Tells PDFView to calculate (layout) the inner views. Called automatically when -[setDocument] and -[setDisplayBox]
// are called. You'll need to call this if you add or remove a page on the document, rotate a page etc.
- (void) layoutDocumentView;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Tells PDFView that an annotation has changed on the specified page.  PDFView re-scans then for tooltips, popups, 
// and informs PDFThumbnailViews so the thumbnail can be redrawn. 
- (void) annotationsChangedOnPage: (PDFPage *) page;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Handy for initially sizing PDFView.  Returns the size needed to display the 'row' of the view's current document  
// containing the specified page at the current scale factor and with the current display attributes.
- (NSSize) rowSizeForPage: (PDFPage *) page;

// Indicate whether dragging is allowed.  If NO (default), dragging events are not supported.  If YES, a user can drag 
// a PDF file to the view and a new document is associated with the view (the old document is released).
- (void) setAllowsDragging: (BOOL) allow;
- (BOOL) allowsDragging;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Returns an array of PDFPage objects representing the currently visible pages. 
- (NSArray *) visiblePages;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

// Turns on or off data detection. If enabled, page text will be scanned for URL's as the page becomes visible. Where 
// URL's are found, Link annotations are created in place. These are temporary annotations and are not saved.
- (void) setEnableDataDetectors: (BOOL) enable;
- (BOOL) enableDataDetectors;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@end

@interface NSObject(PDFViewDelegate)

// Delegate method allowing a delgate to override changes to the scale factor. The default implementation pins scaling 
// between 0.1 and 10.0.
- (CGFloat) PDFViewWillChangeScaleFactor: (PDFView *) sender toScale: (CGFloat) scale;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Delegates implementing the following method will be called to handle clicks on URL links within the PDFView.  The 
// default implementation calls [[NSWorkspace sharedWorkspace] openURL: url].
- (void) PDFViewWillClickOnLink: (PDFView *) sender withURL: (NSURL *) url;

// A delegate providing this method can override the job title when PDFView is printed. The default implementation 
// uses the string, if any, associated with the "Title" key from the view's PDFDocument attribute dictionary. Failing 
// that, it uses the last path component if the PDFDocument is URL-based.
- (NSString *) PDFViewPrintJobTitle: (PDFView *) sender;

// Certain PDFAction's may request that the PDF viewer application perform a Find.  Delegates resonding to the below
// method will be called when the user clicks on an annotation with such an action.
- (void) PDFViewPerformFind: (PDFView *) sender;

// Certain PDFAction's may request that the PDF viewer application bring up a panel allowing the user to enter a 
// specific page number.  Delegates resonding to the below method will be called when the user clicks on an annotation 
// with such an action.
- (void) PDFViewPerformGoToPage: (PDFView *) sender;

// Certain PDFAction's may request that the PDF viewer application Print the current document.  Delegates resonding to 
// the below method will be called when the user clicks on an annotation with such an action.
- (void) PDFViewPerformPrint: (PDFView *) sender;

// Delegates implementing the following method will be called to handle clicks on annotations containing a 
// PDFActionRemoteGoTo action.  The action contains a URL and a page index and point.  The delegate should open the PDF 
// inidicated by the URL and go to the page and point indicated.  The easiest way to do the latter is to create a 
// PDFDestination with the page index and point once a PDFDocument from the URL is create - then you can call:
// -[PDFView goToDestination:]. The default implementation simply beeps.
- (void) PDFViewOpenPDF: (PDFView *) sender forRemoteGoToAction: (PDFActionRemoteGoTo *) action;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@end
