//
//  PDFView.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  This class is the main view of PDFKit: you can instantiate a PDFView or create one
//  in Interface Builder that will host the contents of a PDFDocument. Note that you can
//  layout the pages of a PDFDocument in a few different ways, mostly as a function of
//  PDFDisplayMode, combined with a few options like "displayDirection" and "displaysRTL".
//  Note the delegate PDFViewDelegate and associated notifications, both of which can be
//  used as a way to listen for search, print, and user-interaction events.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFDocument.h>
#import <PDFKit/PDFPage.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFAction, PDFActionRemoteGoTo, PDFDestination, PDFSelection, PDFViewPrivate;
@protocol PDFViewDelegate;

// Display modes.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayMode)
{
    kPDFDisplaySinglePage = 0, 
    kPDFDisplaySinglePageContinuous = 1, 
    kPDFDisplayTwoUp = 2, 
    kPDFDisplayTwoUpContinuous = 3
};

// Display direction.
PDFKIT_ENUM_AVAILABLE(10_13, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayDirection)
{
    kPDFDisplayDirectionVertical = 0,
    kPDFDisplayDirectionHorizontal = 1,
};

// PDF areas of interest (bitfield, multiple bits below may be set).
PDFKIT_AVAILABLE(10_4, 11_0)
typedef NS_OPTIONS(NSInteger, PDFAreaOfInterest)
{
    kPDFNoArea =            0,
    kPDFPageArea =          (1UL << 0),
    kPDFTextArea =          (1UL << 1),
    kPDFAnnotationArea =    (1UL << 2),
    kPDFLinkArea =          (1UL << 3),
    kPDFControlArea =       (1UL << 4),
    kPDFTextFieldArea =     (1UL << 5),
    kPDFIconArea =          (1UL << 6),
    kPDFPopupArea =         (1UL << 7),
    kPDFImageArea =         (1UL << 8),
    
    kPDFAnyArea =           NSIntegerMax
};

// Interpolation quality.
PDFKIT_ENUM_AVAILABLE(10_7, 11_0)
typedef NS_ENUM(NSInteger, PDFInterpolationQuality)
{
    kPDFInterpolationQualityNone = 0, 
    kPDFInterpolationQualityLow = 1, 
    kPDFInterpolationQualityHigh = 2
};

// Notifications.
PDFKIT_EXTERN NSNotificationName const PDFViewDocumentChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);       // Notification when a new document is associated with view.
PDFKIT_EXTERN NSNotificationName const PDFViewChangedHistoryNotification PDFKIT_AVAILABLE(10_4, 11_0);        // Notification when the page history changes.
PDFKIT_EXTERN NSNotificationName const PDFViewPageChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);           // Notification when a new page becomes current.
PDFKIT_EXTERN NSNotificationName const PDFViewScaleChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);          // Notification when the scale changes.
PDFKIT_EXTERN NSNotificationName const PDFViewAnnotationHitNotification PDFKIT_AVAILABLE(10_4, 11_0);         // Notification when the user clicks on an annotation.
PDFKIT_EXTERN NSNotificationName const PDFViewCopyPermissionNotification PDFKIT_AVAILABLE(10_4, 11_0);        // Notification when the user is denied copy (permissions).
PDFKIT_EXTERN NSNotificationName const PDFViewPrintPermissionNotification PDFKIT_AVAILABLE(10_4, 11_0);       // Notification when the user is denied print (permissions).
PDFKIT_EXTERN NSNotificationName const PDFViewAnnotationWillHitNotification PDFKIT_AVAILABLE(10_4, 11_0);     // Notification before user clicks on an annotation.
PDFKIT_EXTERN NSNotificationName const PDFViewSelectionChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);      // Notification when the current selection has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewDisplayModeChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);    // Notification when the display mode has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewDisplayBoxChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);     // Notification when the display box has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewVisiblePagesChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);   // Notification when the scroll view has scrolled into the bounds of a new page.

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFView : PDFKitPlatformView
#if defined(PDFKIT_PLATFORM_OSX)
    < NSAnimationDelegate, NSMenuDelegate >
#elif defined(PDFKIT_PLATFORM_IOS)
    < UIGestureRecognizerDelegate >
#endif
{
@private
    PDFViewPrivate *_private;
}

// -------- document

// Methods for associating a PDFDocument with a PDFView.
@property (nonatomic, retain, nullable) PDFDocument *document;

// -------- page navigation

// Simple page navigation methods.
@property (nonatomic, readonly) BOOL canGoToFirstPage;
- (IBAction)goToFirstPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToLastPage;
- (IBAction)goToLastPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToNextPage;
- (IBAction)goToNextPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToPreviousPage;
- (IBAction)goToPreviousPage:(nullable id)sender;

// Page visitations done via goToFirstPage:, goToLastPage:, goToPage:, etc. methods are recorded with visitation history
// and can be revisited by executing goBack: or goForward:, much like a web browser. Note that visitiation history
// also includes all rect, destination, and selection goTo*: methods.
@property (nonatomic, readonly) BOOL canGoBack;
- (IBAction)goBack:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoForward;
- (IBAction)goForward:(nullable id)sender;

// Returns the current page you are on. For two-up modes, it is the left page (if there are two). For continuous modes, 
// it finds the page crossing a horizontal line halfway between the views top and bottom bounds.
@property (nonatomic, readonly, nullable) PDFPage *currentPage;

// Scrolls to page.
- (void)goToPage:(PDFPage *)page;

// Returns a PDFDestination representing the current page and point displayed (see -[currentPage] for more comments).
@property (nonatomic, readonly, nullable) PDFDestination *currentDestination;

// Goes to the specified destination.
- (void)goToDestination:(PDFDestination *)destination;

// Goes to the specified selection (since selections can be large, goes to the first character of the selection).
- (void)goToSelection:(PDFSelection *)selection;

// Goes to the specified rectangle on the specified page. If already visible, does nothing. This allows you to scroll 
// the PDFView to a specific PDFAnnotation or PDFSelection (since both object have bounds methods).
// Note: rect is specified in page coordinates. Example: You might use this function when tabbing through a form to keep
// focus on the active element.
- (void)goToRect:(PDFRect)rect onPage:(PDFPage *)page;

// -------- display mode

// See PDFDisplayMode constants above. Default is kPDFDisplaySinglePageContinuous.
@property (nonatomic) PDFDisplayMode displayMode;

// Set the layout direction, either vertical or horizontal, for the given display mode
// Defaults to vertical layout (kPDFDisplayDirectionVertical).
@property (nonatomic) PDFDisplayDirection displayDirection PDFKIT_AVAILABLE(10_13, 11_0);

// Toggle displaying or not displaying page breaks (spacing) between pages. This spacing value
// is defined by the pageBreakMargins property. If displaysPageBreaks is NO, then pageBreakMargins
// will always return { 0.0, 0.0, 0.0, 0.0 }. Default is YES.
@property (nonatomic) BOOL displaysPageBreaks;

// If displaysPageBreaks is enabled, you may customize the spacing between pages by defining margins for
// the top, bottom, left, and right of each page. Note that pageBreakMargins only allows positive values
// and will clamp any negative value to 0.0. By default, if displaysPageBreaks is enabled, pageBreakMargins
// is { 4.75, 4.0, 4.75, 4.0 } (with respect to top, left, bottom, right), otherwise it is { 0.0, 0.0, 0.0, 0.0 }
@property (nonatomic) PDFEdgeInsets pageBreakMargins PDFKIT_AVAILABLE(10_13, 11_0);

// Specifies the box to display/clip to. Default is kPDFDisplayBoxCropBox.
@property (nonatomic) PDFDisplayBox displayBox;

// Specifies whether the first page is to be treated as a cover and (for two-up modes) displayed by itself.
@property (nonatomic) BOOL displaysAsBook;

// Specifies presentation of pages from right-to-left. Defaults to NO.
@property (nonatomic) BOOL displaysRTL PDFKIT_AVAILABLE(10_13, 11_0);

// Default is a 50% gray.
@property (nonatomic, strong) PDFKitPlatformColor *backgroundColor;

// Allows setting the interpolation quality for images drawn into the PDFView context. 
@property (nonatomic) PDFInterpolationQuality interpolationQuality PDFKIT_AVAILABLE(10_7, 11_0);

// Specifies if shadows should be drawn around page borders in a PDFView. Defaults to YES.
@property (nonatomic, setter=enablePageShadows:) BOOL pageShadowsEnabled PDFKIT_AVAILABLE(10_14, 12_0);

#if defined(PDFKIT_PLATFORM_IOS)

// Changes the underlying scroll view to use a UIPageViewController as a way to layout and navigate
// pages. Note that you can change the orientation via -[PDFView setDisplayDirection:], and that
// the property -[PDFView displayMode] is ignored: layout is always assumed single page continuous.
// The viewOptions argument is given to the UIPageViewController initializer, as a way to pass in page spacing, etc.
- (void)usePageViewController:(BOOL)enable withViewOptions:(nullable NSDictionary*)viewOptions PDFKIT_AVAILABLE(NA, 11_0);
@property (nonatomic, readonly) BOOL isUsingPageViewController PDFKIT_AVAILABLE(NA, 11_0);

#endif

// -------- delegate

@property (nonatomic, weak, nullable) id< PDFViewDelegate > delegate;

// -------- scaling

// Method to get / set the current scaling on the displayed PDF document. Default is 1.0 (actual size).
// Note that the given scaleFactor is clamped by the current min / max scale factors.
// When using a page view controller layout on iOS, this only affects the currently visible page and
// is ignored for any future loaded pages. You can observe the PDFViewPageChangedNotification notification
// to see when new pages are visible to apply new scale factors to them.
@property (nonatomic) CGFloat scaleFactor;

// Set the minimum and maximum scaling factors for the PDF document. Assigning these values will implicitly turn
// off autoScales, and allows scaleFactor to vary between these min / max scale factors
@property (nonatomic) CGFloat minScaleFactor PDFKIT_AVAILABLE(10_13, 11_0);
@property (nonatomic) CGFloat maxScaleFactor PDFKIT_AVAILABLE(10_13, 11_0);

// Toggles mode whereby the scale factor is automatically changed as the view is resized, or rotated, to maximize the
// PDF displayed. For continuous modes this is a "fit width" behavior, for non-continuous modes it is a "best fit" behavior.
@property (nonatomic) BOOL autoScales;

// Regardless of current autoScales mode, this returns the "size to fit" scale factor that autoScales would use
// for scaling the current document and layout. For continuous modes this is a "fit width" scale, for
// non-continuous modes it is a "best fit" scale.
@property (nonatomic, readonly) CGFloat scaleFactorForSizeToFit PDFKIT_AVAILABLE(10_13, 11_0);

// Zooming changes the scaling by root-2.
- (IBAction)zoomIn:(nullable id)sender;
@property (nonatomic, readonly) BOOL canZoomIn;

- (IBAction)zoomOut:(nullable id)sender;
@property (nonatomic, readonly) BOOL canZoomOut;

// -------- events

// Returns type of area (see defines above) mouse is over. This method is useful for subclasses.
- (PDFAreaOfInterest)areaOfInterestForMouse:(PDFKitPlatformEvent *)event;
- (PDFAreaOfInterest)areaOfInterestForPoint:(PDFPoint)cursorLocation;

#if defined(PDFKIT_PLATFORM_OSX)

// Sets the appropriate cursor for a given area of interest. This method is useful for subclasses.
- (void)setCursorForAreaOfInterest:(PDFAreaOfInterest)area;

#endif

// Performs the action specified by action.
- (void)performAction:(PDFAction *)action PDFKIT_AVAILABLE(10_5, 11_0);

// -------- selection

// Getter: Returns actual instance of the current PDFSelection object. If you wish to modify this, you should make a copy of
// the selection returned and modify that instead. Method may return nil if there is no selection.
// Setter: Set current selection to selection. The view will redraw as necessary. The view will not scroll.
// Call -[scrollSelectionToVisible:] to scroll to the current selection.
@property (nonatomic, strong, nullable) PDFSelection *currentSelection;

// Like -[setCurrentSelection:] above but with the additional parameter that specifies whether setting the selection
// should be animated. The animation draws the user's attention to the new selection. Useful when searching.
- (void)setCurrentSelection:(nullable PDFSelection *)selection animate:(BOOL)animate PDFKIT_AVAILABLE(10_5, 11_0);

// Equivalent to -[PDFView setCurrentSelection: nil].
- (void)clearSelection;

// Select all text for the entire document, unless in in page view controller mode for iOS,
// where only the current page is selected.
- (IBAction)selectAll:(nullable id)sender;

// If the selection is not visible, scrolls view so that it is.
- (IBAction)scrollSelectionToVisible:(nullable id)sender;

// The following calls allow you to associate an array of PDFSelections with a PDFView. Unlike the user selection 
// (above), these selections do not go away when the user clicks in the PDFView, etc. You must explicitly remove them 
// by passing nil to -[setHighlightedSelections:]. These methods allow you to highlight text perhaps to indicate 
// matches from a text search. To avoid confusion you should probably make sure the PDFSelections passed in are a 
// different color from the user's default text selection color. Commonly used for highlighting search results.
@property (nonatomic, copy, nullable) NSArray<PDFSelection*> *highlightedSelections PDFKIT_AVAILABLE(10_5, 11_0);

// -------- rendering

// Context-aware subclassing functions

// For subclasses. This method is called for each visible page requiring rendering. By subclassing you can draw on top
// of the PDF page or draw the page entirely yourself. Default implementation erases page to white and calls:
// [page drawWithBox: [self displayBox] toContext: context]. Note that this may be called multiple times for
// the same page due to tiling of renderable content.
- (void)drawPage:(PDFPage *)page toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// Also a handy method for sub-classing. Called for post-page rendering. In this method however no scaling/rotating is
// applied to the current context to map to page-space. The context is in "view-space" coordinates.
- (void)drawPagePost:(PDFPage *)page toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);


// -------- pasteboard

// Copy the selection (if any) to the pasteboard.
- (IBAction)copy:(nullable id)sender;

#if defined(PDFKIT_PLATFORM_OSX)

// -------- printing

// Print the PDF document. If autoRotate is YES, will ignore the orientation attribute in printInfo and rather choose 
// the orientation on a page by page basis that best fits the page to the paper size.
- (void)printWithInfo:(NSPrintInfo *)printInfo autoRotate:(BOOL)doRotate;

// Like the above method but allows an additional parameter to describe page scaling (see PDFDocument.h for types).
// If pageScaling is equal to kPDFPrintPageScaleToFit each page is scaled up or down in order to best fit the paper
// size. Specifying kPDFPrintPageScaleDownToFit for pageScaling will only scale large pages down to fit the paper, 
// smaller pages will not be scaled up. Passing pageScaling equal to kPDFPrintPageScaleNone is the equivalent of
// calling -[printWithInfo: autoRotate] above.
- (void)printWithInfo:(NSPrintInfo *)printInfo autoRotate:(BOOL)doRotate pageScaling:(PDFPrintScalingMode)scale PDFKIT_AVAILABLE(10_5, 11_0);

#endif

// -------- conversion

// Given a point in view coordinates, returns the page at that point. May return nil if no page at point and nearest is NO.
- (nullable PDFPage *)pageForPoint:(PDFPoint)point nearest:(BOOL)nearest;

// Converts a point from view coordinates to page coordinates.
- (PDFPoint)convertPoint:(PDFPoint)point toPage:(PDFPage *)page;

// Converts a rect from view coordinates to page coordinates.
- (PDFRect)convertRect:(PDFRect)rect toPage:(PDFPage *)page;

// Converts a point from page coordinates to view coordinates.
- (PDFPoint)convertPoint:(PDFPoint)point fromPage:(PDFPage *)page;

// Converts a rect from page coordinates to view coordinates.
- (PDFRect)convertRect:(PDFRect)rect fromPage:(PDFPage *)page;

// -------- misc

// Returns the innermost view used by PDFView. This is the view representing the displayed document pages.
@property (nonatomic, readonly, nullable) PDFKitPlatformView *documentView;

// Tells PDFView to calculate (layout) the inner views. Called automatically when -[setDocument] and -[setDisplayBox]
// are called. You'll need to call this if you add or remove a page on the document, rotate a page etc.
- (void)layoutDocumentView;

// Tells PDFView that an annotation has changed on the specified page. PDFView re-scans then for tooltips, popups, 
// and informs PDFThumbnailViews so the thumbnail can be redrawn. 
- (void)annotationsChangedOnPage:(PDFPage *)page PDFKIT_AVAILABLE(10_5, 11_0);

// Handy for initially sizing PDFView. Returns the size needed to display the 'row' of the view's current document
// containing the specified page at the current scale factor and with the current display attributes.
- (PDFSize)rowSizeForPage:(PDFPage *)page;

#if defined(PDFKIT_PLATFORM_OSX)

// Indicate whether dragging a file into PDFView is allowed. If NO (default), dragging events are not supported.
// If YES, a user can drag and drop a PDF file into the view and have it loaded & set as the visible document (the old document is released).
@property (nonatomic) BOOL acceptsDraggedFiles PDFKIT_AVAILABLE(10_13, NA);

#endif

// Returns an array of PDFPage objects representing the currently visible pages. May return empty array if no document is assigned.
@property (nonatomic, readonly) NSArray<PDFPage *> *visiblePages PDFKIT_AVAILABLE(10_5, 11_0);

// Turns on or off data detection. If enabled, page text will be scanned for results such as URL's, addresses, phone numbers,
// times/dates, etc., as the page becomes visible. Where URL's are found, Link annotations are created in place. These are
// temporary annotations and are not saved.
@property (nonatomic) BOOL enableDataDetectors PDFKIT_AVAILABLE(10_6, 11_0);

@end

@protocol PDFViewDelegate< NSObject >
@optional

// Delegates implementing the following method will be called to handle clicks on URL links within the PDFView. The
// default implementation calls [[NSWorkspace sharedWorkspace] openURL: url].
- (void)PDFViewWillClickOnLink:(PDFView *)sender withURL:(NSURL *)url PDFKIT_AVAILABLE(10_5, 11_0);

#if defined( PDFKIT_PLATFORM_OSX )

// Delegate method allowing a delegate to override changes to the scale factor. The default implementation pins scaling
// between 0.1 and 10.0.
- (CGFloat)PDFViewWillChangeScaleFactor:(PDFView *)sender toScale:(CGFloat)scaler PDFKIT_AVAILABLE(10_5, NA);

// A delegate providing this method can override the job title when PDFView is printed. The default implementation 
// uses the string, if any, associated with the "Title" key from the view's PDFDocument attribute dictionary. Failing 
// that, it uses the last path component if the PDFDocument is URL-based.
- (NSString *)PDFViewPrintJobTitle:(PDFView *)sender PDFKIT_AVAILABLE(10_5, NA);

// Certain PDFAction's may request that the PDF viewer application Print the current document. Delegates responding to
// the below method will be called when the user clicks on an annotation with such an action.
- (void)PDFViewPerformPrint:(PDFView *)sender PDFKIT_AVAILABLE(10_5, NA);

#elif defined( PDFKIT_PLATFORM_IOS )

// A delegate that should return the main view controller the PDFView resides in. This is to add additional
// support to one's view such as 'Lookup' from the text selection menu, along with support of entering text for notes.
- (PDFKitPlatformViewController*) PDFViewParentViewController PDFKIT_AVAILABLE(10_15, 13_0);

#endif

// Certain PDFAction's may request that the PDF viewer application perform a Find. Delegates responding to the below
// method will be called when the user clicks on an annotation with such an action.
- (void)PDFViewPerformFind:(PDFView *)sender PDFKIT_AVAILABLE(10_5, 11_0);

// Certain PDFAction's may request that the PDF viewer application bring up a panel allowing the user to enter a 
// specific page number. Delegates responding to the below method will be called when the user clicks on an annotation
// with such an action.
- (void)PDFViewPerformGoToPage:(PDFView *)sender PDFKIT_AVAILABLE(10_5, 11_0);

// Delegates implementing the following method will be called to handle clicks on annotations containing a 
// PDFActionRemoteGoTo action. The action contains a URL and a page index and point. The delegate should open the PDF 
// indicated by the URL and go to the page and point indicated. The easiest way to do the latter is to create a 
// PDFDestination with the page index and point once a PDFDocument from the URL is created - then you can call:
// -[PDFView goToDestination:]. The default implementation simply beeps.
- (void)PDFViewOpenPDF:(PDFView *)sender forRemoteGoToAction:(PDFActionRemoteGoTo *)action PDFKIT_AVAILABLE(10_5, 11_0);

@end

#if defined( PDFKIT_PLATFORM_OSX )

// Deprecated macOS PDFView methods
@interface PDFView (PDFViewDeprecated)

// -------- password

// Convenience method. Calls -[[self document] unlockWithPassword:] with the password from sender.
- (IBAction)takePasswordFrom:(id)sender PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// -------- rendering

// This method is deprecated in favor of the of the context aware -[PDFView drawPage:toContext:]. If you subclass
// PDFView, rendering code will first call -[PDFView drawPage:toContext:]. If your subclass does not override the
// context-aware function, this original -[PDFView drawPage:] method will be called.
// For subclasses. This method is called for each visible page requiring rendering.  By subclassing you can draw on top
// of the PDF page or draw the page entirely yourself. Default implementation erases page to white and calls:
// [page drawWithBox: [self displayBox]], then draws the selection if any.
- (void)drawPage:(PDFPage *)page PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// This method is deprecated in favor of the of the context aware -[PDFView drawPagePost:toContext:]. If you subclass
// PDFView, rendering code will first call -[PDFView drawPagePost:toContext:]. If your subclass does not override the
// context-aware function, this original -[PDFView drawPagePost:] method will be called.
// Also a handy method for sub-classing.  Called for post-page rendering. In this method however no scaling/rotating is
// applied to the current context to map to page-space.  The context is in "view-space" coordinates.  The default
// implementation of this method draws the text highlighting (if any) for page.
- (void)drawPagePost:(PDFPage *)page PDFKIT_DEPRECATED(10_5, 10_12, NA, NA);

// State of anti-aliasing when drawing. Default is YES.
@property (nonatomic) BOOL shouldAntiAlias PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// Greeking threshold to apply to text displayed. Default is 0.0.
@property (nonatomic) CGFloat greekingThreshold PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// The background color is the color of the space behind the PDF pages (and between them if page breaks is enabled).
// Default is a 50% gray.
- (IBAction)takeBackgroundColorFrom:(id)sender PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// -------- misc

// Indicate whether dragging is allowed. If NO (default), dragging events are not supported. If YES, a user can drag
// a PDF file to the view and a new document is associated with the view (the old document is released).
// Method renamed to "acceptsDraggedFiles", has same behavior.
@property (nonatomic) BOOL allowsDragging PDFKIT_DEPRECATED(10_4, 10_13, NA, NA);

@end

#endif

NS_ASSUME_NONNULL_END
