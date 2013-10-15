/*
	NSView.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSRange.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSAnimation.h>
#import <AppKit/NSUserInterfaceItemIdentification.h>
#import <AppKit/NSDragging.h>

@class NSBitmapImageRep, NSCursor, NSDraggingSession, NSGraphicsContext, NSImage, NSPasteboard, NSScrollView, NSTextInputContext, NSWindow, NSAttributedString;
@class CIFilter, CALayer, NSDictionary, NSScreen, NSShadow, NSTrackingArea;
@protocol NSDraggingSource;

enum {
    NSViewNotSizable			=  0,
    NSViewMinXMargin			=  1,
    NSViewWidthSizable			=  2,
    NSViewMaxXMargin			=  4,
    NSViewMinYMargin			=  8,
    NSViewHeightSizable			= 16,
    NSViewMaxYMargin			= 32
};

enum {
    NSNoBorder				= 0,
    NSLineBorder			= 1,
    NSBezelBorder			= 2,
    NSGrooveBorder			= 3
};
typedef NSUInteger NSBorderType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
enum {
    NSViewLayerContentsRedrawNever                  = 0,
    NSViewLayerContentsRedrawOnSetNeedsDisplay      = 1,
    NSViewLayerContentsRedrawDuringViewResize       = 2,
    NSViewLayerContentsRedrawBeforeViewResize       = 3
};
#endif
typedef NSInteger NSViewLayerContentsRedrawPolicy;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
enum {
    NSViewLayerContentsPlacementScaleAxesIndependently      =  0,
    NSViewLayerContentsPlacementScaleProportionallyToFit    =  1,
    NSViewLayerContentsPlacementScaleProportionallyToFill   =  2,
    NSViewLayerContentsPlacementCenter                      =  3,
    NSViewLayerContentsPlacementTop                         =  4,
    NSViewLayerContentsPlacementTopRight                    =  5,
    NSViewLayerContentsPlacementRight                       =  6,
    NSViewLayerContentsPlacementBottomRight                 =  7,
    NSViewLayerContentsPlacementBottom                      =  8,
    NSViewLayerContentsPlacementBottomLeft                  =  9,
    NSViewLayerContentsPlacementLeft                        = 10,
    NSViewLayerContentsPlacementTopLeft                     = 11
};
#endif
typedef NSInteger NSViewLayerContentsPlacement;

typedef struct __VFlags {
#ifdef __BIG_ENDIAN__
	unsigned int        rotatedFromBase:1;
	unsigned int        rotatedOrScaledFromBase:1;
	unsigned int        autosizing:6;
	unsigned int        autoresizeSubviews:1;
	unsigned int        wantsGState:1;
	unsigned int        needsDisplay:1;
	unsigned int        validGState:1;
	unsigned int        newGState:1;
	unsigned int        noVerticalAutosizing:1;
	unsigned int        frameChangeNotesSuspended:1;
	unsigned int        needsFrameChangeNote:1;
	unsigned int        focusChangeNotesSuspended:1;
	unsigned int        boundsChangeNotesSuspended:1;
	unsigned int        needsBoundsChangeNote:1;
	unsigned int        removingWithoutInvalidation:1;
        unsigned int        interfaceStyle0:1;
	unsigned int        needsDisplayForBounds:1;
	unsigned int        specialArchiving:1;
	unsigned int        interfaceStyle1:1;
	unsigned int        retainCount:6;
	unsigned int        retainCountOverMax:1;
	unsigned int        aboutToResize:1;
#else
	unsigned int        aboutToResize:1;
	unsigned int        retainCountOverMax:1;
	unsigned int        retainCount:6;
	unsigned int        interfaceStyle1:1;
	unsigned int        specialArchiving:1;
	unsigned int        needsDisplayForBounds:1;
	unsigned int        interfaceStyle0:1;
        unsigned int        removingWithoutInvalidation:1;
	unsigned int        needsBoundsChangeNote:1;
	unsigned int        boundsChangeNotesSuspended:1;
	unsigned int        focusChangeNotesSuspended:1;
	unsigned int        needsFrameChangeNote:1;
	unsigned int        frameChangeNotesSuspended:1;
	unsigned int        noVerticalAutosizing:1;
	unsigned int        newGState:1;
	unsigned int        validGState:1;
	unsigned int        needsDisplay:1;
	unsigned int        wantsGState:1;
	unsigned int        autoresizeSubviews:1;
	unsigned int        autosizing:6;
	unsigned int        rotatedOrScaledFromBase:1;
	unsigned int        rotatedFromBase:1;
#endif
} _VFlags;

typedef NSInteger NSTrackingRectTag;
typedef NSInteger NSToolTipTag;

@class _NSViewAuxiliary;

@interface NSView : NSResponder <NSAnimatablePropertyContainer, NSUserInterfaceItemIdentification, NSDraggingDestination>
{
    /*All instance variables are private*/
    NSRect              _frame;
    NSRect              _bounds;
    id                  _superview;
    id			_subviews;
    NSWindow            *_window;
    id                  _gState;
    id                  _frameMatrix;
    id			_drawMatrix;
    id			_dragTypes;
    _NSViewAuxiliary	*_viewAuxiliary;
    _VFlags		_vFlags;
    struct __VFlags2 {
	unsigned int	nextKeyViewRefCount:14;
	unsigned int	previousKeyViewRefCount:14;
	unsigned int	isVisibleRect:1;
	unsigned int	hasToolTip:1;
	unsigned int	needsRealLockFocus:1;
	unsigned int	menuWasSet:1;
    } _vFlags2;
}


- (id)initWithFrame:(NSRect)frameRect;

- (NSWindow *)window;
- (NSView *)superview;
- (NSArray *)subviews;
- (BOOL)isDescendantOf:(NSView *)aView;
- (NSView *)ancestorSharedWithView:(NSView *)aView;
- (NSView *)opaqueAncestor;
- (void)setHidden:(BOOL)flag;
- (BOOL)isHidden;
- (BOOL)isHiddenOrHasHiddenAncestor;

- (void)getRectsBeingDrawn:(const NSRect **)rects count:(NSInteger *)count;
- (BOOL)needsToDrawRect:(NSRect)aRect;
- (BOOL)wantsDefaultClipping;
- (void)viewDidHide NS_AVAILABLE_MAC(10_5);
- (void)viewDidUnhide NS_AVAILABLE_MAC(10_5);

- (void)setSubviews:(NSArray *)newSubviews NS_AVAILABLE_MAC(10_5);
- (void)addSubview:(NSView *)aView;
- (void)addSubview:(NSView *)aView positioned:(NSWindowOrderingMode)place relativeTo:(NSView *)otherView;
- (void)sortSubviewsUsingFunction:(NSComparisonResult (*)(id, id, void *))compare context:(void *)context;
- (void)viewWillMoveToWindow:(NSWindow *)newWindow;
- (void)viewDidMoveToWindow;
- (void)viewWillMoveToSuperview:(NSView *)newSuperview;
- (void)viewDidMoveToSuperview;
- (void)didAddSubview:(NSView *)subview;
- (void)willRemoveSubview:(NSView *)subview;
- (void)removeFromSuperview;
- (void)replaceSubview:(NSView *)oldView with:(NSView *)newView;
- (void)removeFromSuperviewWithoutNeedingDisplay;

- (void)setPostsFrameChangedNotifications:(BOOL)flag;
- (BOOL)postsFrameChangedNotifications;
- (void)resizeSubviewsWithOldSize:(NSSize)oldSize;
- (void)resizeWithOldSuperviewSize:(NSSize)oldSize;
- (void)setAutoresizesSubviews:(BOOL)flag;
- (BOOL)autoresizesSubviews;
- (void)setAutoresizingMask:(NSUInteger)mask;
- (NSUInteger)autoresizingMask;

- (void)setFrameOrigin:(NSPoint)newOrigin;
- (void)setFrameSize:(NSSize)newSize;
- (void)setFrame:(NSRect)frameRect;
- (NSRect)frame;
- (void)setFrameRotation:(CGFloat)angle;
- (CGFloat)frameRotation;
- (void)setFrameCenterRotation:(CGFloat)angle NS_AVAILABLE_MAC(10_5);
- (CGFloat)frameCenterRotation NS_AVAILABLE_MAC(10_5);

- (void)setBoundsOrigin:(NSPoint)newOrigin;
- (void)setBoundsSize:(NSSize)newSize;
- (void)setBoundsRotation:(CGFloat)angle;
- (CGFloat)boundsRotation;
- (void)translateOriginToPoint:(NSPoint)translation;
- (void)scaleUnitSquareToSize:(NSSize)newUnitSize;
- (void)rotateByAngle:(CGFloat)angle;
- (void)setBounds:(NSRect)aRect;
- (NSRect)bounds;

- (BOOL)isFlipped;
- (BOOL)isRotatedFromBase;
- (BOOL)isRotatedOrScaledFromBase;
- (BOOL)isOpaque;

- (NSPoint)convertPoint:(NSPoint)aPoint fromView:(NSView *)aView;
- (NSPoint)convertPoint:(NSPoint)aPoint toView:(NSView *)aView;
- (NSSize)convertSize:(NSSize)aSize fromView:(NSView *)aView;
- (NSSize)convertSize:(NSSize)aSize toView:(NSView *)aView;
- (NSRect)convertRect:(NSRect)aRect fromView:(NSView *)aView;
- (NSRect)convertRect:(NSRect)aRect toView:(NSView *)aView;

/* Uses NSIntegralRectWithOptions() to produce a backing store pixel aligned rectangle from the given input rectangle in local view coordinates.
 */
- (NSRect)backingAlignedRect:(NSRect)aRect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);
- (NSRect)centerScanRect:(NSRect)aRect;

/* New methods for converting to and from backing store pixels */

- (NSPoint)convertPointToBacking:(NSPoint)aPoint NS_AVAILABLE_MAC(10_7);
- (NSPoint)convertPointFromBacking:(NSPoint)aPoint NS_AVAILABLE_MAC(10_7);
- (NSSize)convertSizeToBacking:(NSSize)aSize NS_AVAILABLE_MAC(10_7);
- (NSSize)convertSizeFromBacking:(NSSize)aSize NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectToBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* Use these methods to transform geometry between a view's interior (bounds) coordinate space and its layer's interior coordinate space.  The layer's space is virtual, and doesn't take into account the layer's contentsScale setting.  For conversion between view space and layer pixels, use -convert(Point/Size/Rect)(To/From)Backing: instead.
*/
- (NSPoint)convertPointToLayer:(NSPoint)aPoint NS_AVAILABLE_MAC(10_7);
- (NSPoint)convertPointFromLayer:(NSPoint)aPoint NS_AVAILABLE_MAC(10_7);
- (NSSize)convertSizeToLayer:(NSSize)aSize NS_AVAILABLE_MAC(10_7);
- (NSSize)convertSizeFromLayer:(NSSize)aSize NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectToLayer:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromLayer:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* These methods are deprecated on 10.7 and later, and are superceded by the convert*To/FromBacking methods */

- (NSPoint)convertPointToBase:(NSPoint)aPoint NS_AVAILABLE_MAC(10_5);
- (NSPoint)convertPointFromBase:(NSPoint)aPoint NS_AVAILABLE_MAC(10_5);
- (NSSize)convertSizeToBase:(NSSize)aSize NS_AVAILABLE_MAC(10_5);
- (NSSize)convertSizeFromBase:(NSSize)aSize NS_AVAILABLE_MAC(10_5);
- (NSRect)convertRectToBase:(NSRect)aRect NS_AVAILABLE_MAC(10_5);
- (NSRect)convertRectFromBase:(NSRect)aRect NS_AVAILABLE_MAC(10_5);

/* Reports whether AppKit may invoke the view's -drawRect: method on a background thread, where it would otherwise be invoked on the main thread.  Defaults to NO.
*/
- (BOOL)canDrawConcurrently NS_AVAILABLE_MAC(10_6);

/* Sets whether AppKit may invoke the view's -drawRect: method on a background thread, where it would otherwise be invoked on the main thread.  Defaults to NO for most kinds of views.  May be set to YES to enable threaded drawing for a particular view instance.  The view's window must also have its "allowsConcurrentViewDrawing" property set to YES (the default) for threading of view drawing to actually take place. */
- (void)setCanDrawConcurrently:(BOOL)flag NS_AVAILABLE_MAC(10_6);

- (BOOL)canDraw;
- (void)setNeedsDisplay:(BOOL)flag;
- (void)setNeedsDisplayInRect:(NSRect)invalidRect;
- (BOOL)needsDisplay;
- (void)lockFocus;
- (void)unlockFocus;
- (BOOL)lockFocusIfCanDraw;
- (BOOL)lockFocusIfCanDrawInContext:(NSGraphicsContext *)context;
+ (NSView *)focusView;
- (NSRect)visibleRect;

- (void)display;
- (void)displayIfNeeded;
- (void)displayIfNeededIgnoringOpacity;
- (void)displayRect:(NSRect)rect;
- (void)displayIfNeededInRect:(NSRect)rect;
- (void)displayRectIgnoringOpacity:(NSRect)rect;
- (void)displayIfNeededInRectIgnoringOpacity:(NSRect)rect;
- (void)drawRect:(NSRect)dirtyRect;
- (void)displayRectIgnoringOpacity:(NSRect)aRect inContext:(NSGraphicsContext *)context;

- (NSBitmapImageRep *)bitmapImageRepForCachingDisplayInRect:(NSRect)rect;
- (void)cacheDisplayInRect:(NSRect)rect toBitmapImageRep:(NSBitmapImageRep *)bitmapImageRep;
- (void)viewWillDraw NS_AVAILABLE_MAC(10_5);

- (NSInteger)gState;
- (void)allocateGState;
- (void)releaseGState;
- (void)setUpGState;
- (void)renewGState;

- (void)scrollPoint:(NSPoint)aPoint;
- (BOOL)scrollRectToVisible:(NSRect)aRect;
- (BOOL)autoscroll:(NSEvent *)theEvent;
- (NSRect)adjustScroll:(NSRect)newVisible;
- (void)scrollRect:(NSRect)aRect by:(NSSize)delta;
- (void)translateRectsNeedingDisplayInRect:(NSRect)clipRect by:(NSSize)delta NS_AVAILABLE_MAC(10_5);

- (NSView *)hitTest:(NSPoint)aPoint;
- (BOOL)mouse:(NSPoint)aPoint inRect:(NSRect)aRect;
- (id)viewWithTag:(NSInteger)aTag;
- (NSInteger)tag;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;
- (BOOL)shouldDelayWindowOrderingForEvent:(NSEvent *)theEvent;
- (BOOL)needsPanelToBecomeKey;
- (BOOL)mouseDownCanMoveWindow;

/* By default, views do not accept touch events
*/
- (void)setAcceptsTouchEvents:(BOOL)flag NS_AVAILABLE_MAC(10_6);
- (BOOL)acceptsTouchEvents NS_AVAILABLE_MAC(10_6);

/* In some cases, the user may rest a thumb or other touch on the device. By default, these touches are not delivered and are not included in the event's set of touches. Touches may transition in and out of resting at any time. Unless the view wants restingTouches, began / ended events are simlulated as touches transition from resting to active and vice versa.
*/
- (void)setWantsRestingTouches:(BOOL)flag NS_AVAILABLE_MAC(10_6);
- (BOOL)wantsRestingTouches NS_AVAILABLE_MAC(10_6);

- (void)addCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)removeCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)discardCursorRects;
- (void)resetCursorRects;

- (NSTrackingRectTag)addTrackingRect:(NSRect)aRect owner:(id)anObject userData:(void *)data assumeInside:(BOOL)flag;
- (void)removeTrackingRect:(NSTrackingRectTag)tag;

- (CALayer *)makeBackingLayer NS_AVAILABLE_MAC(10_6);

- (NSViewLayerContentsRedrawPolicy)layerContentsRedrawPolicy NS_AVAILABLE_MAC(10_6);
- (void)setLayerContentsRedrawPolicy:(NSViewLayerContentsRedrawPolicy)newPolicy NS_AVAILABLE_MAC(10_6);

- (NSViewLayerContentsPlacement)layerContentsPlacement NS_AVAILABLE_MAC(10_6);
- (void)setLayerContentsPlacement:(NSViewLayerContentsPlacement)newPlacement NS_AVAILABLE_MAC(10_6);

- (void)setWantsLayer:(BOOL)flag NS_AVAILABLE_MAC(10_5);
- (BOOL)wantsLayer NS_AVAILABLE_MAC(10_5);

- (void)setLayer:(CALayer *)newLayer NS_AVAILABLE_MAC(10_5);
- (CALayer *)layer NS_AVAILABLE_MAC(10_5);

- (void)setAlphaValue:(CGFloat)viewAlpha NS_AVAILABLE_MAC(10_5);
- (CGFloat)alphaValue NS_AVAILABLE_MAC(10_5);

- (void)setBackgroundFilters:(NSArray *)filters NS_AVAILABLE_MAC(10_5);
- (NSArray *)backgroundFilters NS_AVAILABLE_MAC(10_5);

- (void)setCompositingFilter:(CIFilter *)filter NS_AVAILABLE_MAC(10_5);
- (CIFilter *)compositingFilter NS_AVAILABLE_MAC(10_5);

- (void)setContentFilters:(NSArray *)filters NS_AVAILABLE_MAC(10_5);
- (NSArray *)contentFilters NS_AVAILABLE_MAC(10_5);

- (void)setShadow:(NSShadow *)shadow NS_AVAILABLE_MAC(10_5);
- (NSShadow *)shadow NS_AVAILABLE_MAC(10_5);

/* The following methods are meant to be invoked, and probably don't need to be overridden
*/
- (void)addTrackingArea:(NSTrackingArea *)trackingArea NS_AVAILABLE_MAC(10_5);
- (void)removeTrackingArea:(NSTrackingArea *)trackingArea NS_AVAILABLE_MAC(10_5);
- (NSArray *)trackingAreas NS_AVAILABLE_MAC(10_5);

/* updateTrackingAreas should be overridden to remove out of date tracking areas and add recomputed tracking areas, and should call super.
*/
- (void)updateTrackingAreas NS_AVAILABLE_MAC(10_5);


- (BOOL)shouldDrawColor;

- (void)setPostsBoundsChangedNotifications:(BOOL)flag;
- (BOOL)postsBoundsChangedNotifications;

- (NSScrollView *)enclosingScrollView;

- (NSMenu *)menuForEvent:(NSEvent *)event;
+ (NSMenu *)defaultMenu;

- (void)setToolTip:(NSString *)string;
- (NSString *)toolTip;
- (NSToolTipTag)addToolTipRect:(NSRect)aRect owner:(id)anObject userData:(void *)data;
- (void)removeToolTip:(NSToolTipTag)tag;
- (void)removeAllToolTips;

/* Live resize support */
// a view receives viewWillStartLiveResize before the frame is first changed for a live resize
- (void)viewWillStartLiveResize;
// a view receives viewWillEndLiveResize after the frame is last changed for a live resize
- (void)viewDidEndLiveResize;
// inLiveResize can be called from drawRect: to decide between cheap and full drawing
- (BOOL)inLiveResize;
/* A view that returns YES for -preservesContentDuringLiveResize is responsible for invalidating its own dirty rects during live resize */
- (BOOL)preservesContentDuringLiveResize;
/* -rectPreservedDuringLiveResize indicates the rect the view previously occupied, in the current coordinate system of the view */
- (NSRect)rectPreservedDuringLiveResize;
/* On return from -getRectsExposedDuringLiveResize, exposedRects indicates the parts of the view that are newly exposed (at most 4 rects).  *count indicates how many rects are in the exposedRects list */
- (void)getRectsExposedDuringLiveResize:(NSRect[4])exposedRects count:(NSInteger *)count;

/* Text Input */
/* Returns NSTextInputContext object for the receiver. Returns nil if the receiver doesn't conform to NSTextInputClient protocol.
 */
- (NSTextInputContext *)inputContext NS_AVAILABLE_MAC(10_6);
@end

@interface NSObject(NSToolTipOwner)
- (NSString *)view:(NSView *)view stringForToolTip:(NSToolTipTag)tag point:(NSPoint)point userData:(void *)data;
@end

@interface NSView(NSKeyboardUI)
- (BOOL)performMnemonic:(NSString *)theString;
- (void)setNextKeyView:(NSView *)next;
- (NSView *)nextKeyView;
- (NSView *)previousKeyView;
- (NSView *)nextValidKeyView;
- (NSView *)previousValidKeyView;

- (BOOL)canBecomeKeyView;

- (void)setKeyboardFocusRingNeedsDisplayInRect:(NSRect)rect;

- (void)setFocusRingType:(NSFocusRingType)focusRingType;
- (NSFocusRingType)focusRingType;
+ (NSFocusRingType)defaultFocusRingType;

- (void)drawFocusRingMask NS_AVAILABLE_MAC(10_7);
- (NSRect)focusRingMaskBounds NS_AVAILABLE_MAC(10_7);
- (void)noteFocusRingMaskChanged NS_AVAILABLE_MAC(10_7);

@end

@interface NSView(NSPrinting)

/* EPS/PDF generation */
- (void)writeEPSInsideRect:(NSRect)rect toPasteboard:(NSPasteboard *)pasteboard;
- (NSData *)dataWithEPSInsideRect:(NSRect)rect;
- (void)writePDFInsideRect:(NSRect)rect toPasteboard:(NSPasteboard *)pasteboard;
- (NSData *)dataWithPDFInsideRect:(NSRect)rect;

/* Printing action method (Note fax: is obsolete) */
- (void)print:(id)sender;

/* Pagination */
- (BOOL)knowsPageRange:(NSRangePointer)range;
- (CGFloat)heightAdjustLimit;
- (CGFloat)widthAdjustLimit;
- (void)adjustPageWidthNew:(CGFloat *)newRight left:(CGFloat)oldLeft right:(CGFloat)oldRight limit:(CGFloat)rightLimit;
- (void)adjustPageHeightNew:(CGFloat *)newBottom top:(CGFloat)oldTop bottom:(CGFloat)oldBottom limit:(CGFloat)bottomLimit;
- (NSRect)rectForPage:(NSInteger)page;
- (NSPoint)locationOfPrintRect:(NSRect)aRect;
- (void)drawPageBorderWithSize:(NSSize)borderSize;
- (NSAttributedString *)pageHeader;
- (NSAttributedString *)pageFooter;

/*** This method is obsolete.  It will never be invoked from within AppKit, and NSView's implementation of it does nothing. ***/
- (void)drawSheetBorderWithSize:(NSSize)borderSize;

/* Printing */
/* Returns print job title. Default implementation first tries its window's NSDocument (displayName), then window's title */
- (NSString *)printJobTitle;
- (void)beginDocument;
- (void)endDocument;

- (void)beginPageInRect:(NSRect)aRect atPlacement:(NSPoint)location;
- (void)endPage;
@end


@interface NSView(NSDrag)
/* Starts a dragging session with a group of NSDraggingItems. The frame property of each NSDraggingItem must be in the view's coordinate system. The images may animate (flock) from thier initial layout into a system defined formation. Flocking or may not be done immediately. (see NSDraggingSession's flockOnBeginDrag. The visible area of the view is used as the clip rect.
*/
- (NSDraggingSession *)beginDraggingSessionWithItems:(NSArray *)items event:(NSEvent *)event source:(id<NSDraggingSource>)source NS_AVAILABLE_MAC(10_7);

/* This drag method as been deprecated in favor of beginDraggingSessionWithItems:event:source:
*/ 
- (void)dragImage:(NSImage *)anImage at:(NSPoint)viewLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag;

- (NSArray *)registeredDraggedTypes;
- (void)registerForDraggedTypes:(NSArray *)newTypes;
- (void)unregisterDraggedTypes;

- (BOOL)dragFile:(NSString *)filename fromRect:(NSRect)rect slideBack:(BOOL)aFlag event:(NSEvent *)event;
- (BOOL)dragPromisedFilesOfTypes:(NSArray *)typeArray fromRect:(NSRect)rect source:(id)sourceObject slideBack:(BOOL)aFlag event:(NSEvent *)event;
@end

@interface NSView (NSFullScreenMode) 
- (BOOL)enterFullScreenMode:(NSScreen *)screen withOptions:(NSDictionary *)options NS_AVAILABLE_MAC(10_5);
- (void)exitFullScreenModeWithOptions:(NSDictionary *)options NS_AVAILABLE_MAC(10_5);
- (BOOL)isInFullScreenMode NS_AVAILABLE_MAC(10_5); 
@end

/* Constants for options when entering and exiting full screen mode */
APPKIT_EXTERN NSString * const NSFullScreenModeAllScreens NS_AVAILABLE_MAC(10_5);                      // NSNumber numberWithBool:YES/NO
APPKIT_EXTERN NSString * const NSFullScreenModeSetting NS_AVAILABLE_MAC(10_5);                         // NSDictionary (obtained from CGSDisplay based functions)
APPKIT_EXTERN NSString * const NSFullScreenModeWindowLevel NS_AVAILABLE_MAC(10_5);                     // NSNumber numberWithInt:windowLevel
APPKIT_EXTERN NSString * const NSFullScreenModeApplicationPresentationOptions NS_AVAILABLE_MAC(10_5);  // NSNumber numberWithUnsignedInteger:(NSApplicationPresentationOptions flags)

@interface NSView(NSDefinition)
/* Shows a window that displays the definition (or other subject depending on available dictionaries) of the specified attributed string.  This method can be used for implementing the same functionality as NSTextView's 'Look Up in Dictionary' contextual menu on a custom view.
 
 textBaselineOrigin specifies the baseline origin of attrString in the receiver view coordinate system.  If a small overlay window is selected as default presentation (see NSDefinitionPresentationTypeKey option for details), the overlay text would be rendered starting from the location.  Otherwise, 'Dictionary' application will be invoked to show the definition of the specified string.
 
 This method is equivalent to using showDefinitionForAttributedString:range:options:baselineOriginProvider: and passing attrString with the whole range, nil options, and an originProvider which returns textBaselineOrigin.
 */
- (void)showDefinitionForAttributedString:(NSAttributedString *)attrString atPoint:(NSPoint)textBaselineOrigin NS_AVAILABLE_MAC(10_6);

#if NS_BLOCKS_AVAILABLE
/* Takes a whole attributed string with the target range (normally, this is the selected range), and shows a window displaying the definition of the specified range.  The caller can pass a zero-length range and the appropriate range will be auto-detected around the range's offset.  That's the recommended approach when there is no selection.
 
 This method also an 'options' dictionary containing options described below as key-value pairs (can be nil).
 
 Except when NSDefinitionPresentationTypeKey with NSDefinitionPresentationTypeDictionaryApplication is specified in options, the caller must supply an originProvider Block which returns the baseline origin of the first character at proposed adjustedRange in the receiver view coordinate system.
 
 If the receiver is an NSTextView, both attrString and originProvider may be nil, in which case the text view will automatically supply values suitable for displaying definitions for the specified range within its text content.  This method does not cause scrolling, so clients should perform any necessary scrolling before calling this method.
 */
- (void)showDefinitionForAttributedString:(NSAttributedString *)attrString range:(NSRange)targetRange options:(NSDictionary *)options baselineOriginProvider:(NSPoint (^)(NSRange adjustedRange))originProvider NS_AVAILABLE_MAC(10_6);
#endif

@end

/* NSDefinitionPresentationTypeKey is an optional key in 'options' that specifies the presentation type of the definition display.  The possible values are NSDefinitionPresentationTypeOverlay that produces a small overlay window at the string location, or NSDefinitionPresentationTypeDictionaryApplication that invokes 'Dictionary' application to display the definition.  Without this option, the definition will be shown in either of those presentation forms depending on the 'Contextual Menu:' setting in Dictionary application preferences.
 */
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeKey NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeOverlay NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeDictionaryApplication NS_AVAILABLE_MAC(10_6);


@interface NSView(NSFindIndicator)

/* When this method returns YES, the receiver or one of its ancestors is being drawn for a find indicator, meaning the receiver should draw so its contents will be easily readable.
 */
- (BOOL)isDrawingFindIndicator NS_AVAILABLE_MAC(10_7);

@end

/* Notifications */

APPKIT_EXTERN NSString *NSViewFrameDidChangeNotification;
APPKIT_EXTERN NSString *NSViewFocusDidChangeNotification;
APPKIT_EXTERN NSString *NSViewBoundsDidChangeNotification;
    // This notification is sent whenever the views bounds change and the frame does not.  That is, it is sent whenever the view's bounds are translated, scaled or rotated, but NOT when the bounds change as a result of, for example, setFrameSize:.
APPKIT_EXTERN NSString *NSViewGlobalFrameDidChangeNotification;
    // This notification is sent whenever an NSView that has an attached NSSurface changes size or changes screens (thus potentially changing graphics hardware drivers.)
    
APPKIT_EXTERN NSString *NSViewDidUpdateTrackingAreasNotification NS_AVAILABLE_MAC(10_5);
    // This notification is sent whenever tracking areas should be recalculated for the view.  It is sent after the view receives -updateTrackingAreas.
