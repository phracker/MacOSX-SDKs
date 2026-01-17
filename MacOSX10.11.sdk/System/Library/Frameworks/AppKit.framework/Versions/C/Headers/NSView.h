/*
    NSView.h
    Application Kit
    Copyright (c) 1994-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSApplication.h>
#import <AppKit/NSResponder.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSRange.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSAnimation.h>
#import <AppKit/NSUserInterfaceItemIdentification.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSAppearance.h>

NS_ASSUME_NONNULL_BEGIN

@class NSBitmapImageRep, NSCursor, NSDraggingSession, NSGestureRecognizer, NSGraphicsContext, NSImage, NSPasteboard, NSScrollView, NSTextInputContext, NSWindow, NSAttributedString;
@class CIFilter, CALayer, NSScreen, NSShadow, NSTrackingArea;
@protocol NSDraggingSource;

// Bitset options for the autoresizingMask
typedef NS_OPTIONS(NSUInteger, NSAutoresizingMaskOptions) {
    NSViewNotSizable			=  0,
    NSViewMinXMargin			=  1,
    NSViewWidthSizable			=  2,
    NSViewMaxXMargin			=  4,
    NSViewMinYMargin			=  8,
    NSViewHeightSizable			= 16,
    NSViewMaxYMargin			= 32
};

typedef NS_ENUM(NSUInteger, NSBorderType) {
    NSNoBorder				= 0,
    NSLineBorder			= 1,
    NSBezelBorder			= 2,
    NSGrooveBorder			= 3
};

typedef NS_ENUM(NSInteger, NSViewLayerContentsRedrawPolicy) {
    // Leave the layer's contents alone. Never mark the layer as needing display, or draw the view's contents to the layer
    NSViewLayerContentsRedrawNever = 0,
    // Map view -setNeedsDisplay...: activity to the layer, and redraw affected layer parts by invoking the view's -drawRect:, but don't mark the view or layer as needing display when the view's size changes.
    NSViewLayerContentsRedrawOnSetNeedsDisplay = 1,
    // Resize the layer and redraw the view to the layer when the view's size changes. If the resize is animated, AppKit will drive the resize animation itself and will do this resize+redraw at each step of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.) 
    NSViewLayerContentsRedrawDuringViewResize = 2,
    // Resize the layer and redraw the view to the layer when the view's size changes. This will be done just once at the beginning of a resize animation, not at each frame of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.)
    NSViewLayerContentsRedrawBeforeViewResize = 3,
    // When a view is resized, the layer contents will be redrawn once and the contents will crossfade from the old value to the new value. Use this in conjunction with the layerContentsPlacement to get a nice crossfade animation for complex layer-backed views that can't correctly update on each step of the animation
    NSViewLayerContentsRedrawCrossfade NS_ENUM_AVAILABLE_MAC(10_9) = 4
} NS_ENUM_AVAILABLE_MAC(10_6);

typedef NS_ENUM(NSInteger, NSViewLayerContentsPlacement) {
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
} NS_ENUM_AVAILABLE_MAC(10_6);

typedef struct __VFlags {
#ifdef __BIG_ENDIAN__
	unsigned int rotatedFromBase:1;
	unsigned int rotatedOrScaledFromBase:1;
	unsigned int autosizing:6;
	unsigned int autoresizeSubviews:1;
	unsigned int wantsGState:1;
	unsigned int needsDisplay:1;
	unsigned int allowsVibrancy:2;
	unsigned int canDrawSubviewsIntoLayer:1;
	unsigned int frameChangeNotesSuspended:1;
	unsigned int needsFrameChangeNote:1;
	unsigned int unused2:1;
	unsigned int boundsChangeNotesSuspended:1;
	unsigned int needsBoundsChangeNote:1;
	unsigned int removingWithoutInvalidation:1;
	unsigned int isFlipped:1;
	unsigned int needsDisplayForBounds:1;
	unsigned int specialArchiving:1;
	unsigned int ignoreHitTest:1;
        unsigned int hasNotMessedWithIsFlipped:1;
	unsigned int unused3:5;
	unsigned int isOpaque:1;
	unsigned int aboutToResize:1;
#else
	unsigned int aboutToResize:1;
	unsigned int isOpaque:1;
	unsigned int unused3:5;
        unsigned int hasNotMessedWithIsFlipped:1;
	unsigned int ignoreHitTest:1;
	unsigned int specialArchiving:1;
	unsigned int needsDisplayForBounds:1;
	unsigned int isFlipped:1;
	unsigned int removingWithoutInvalidation:1;
	unsigned int needsBoundsChangeNote:1;
	unsigned int boundsChangeNotesSuspended:1;
	unsigned int unused2:1;
	unsigned int needsFrameChangeNote:1;
	unsigned int frameChangeNotesSuspended:1;
	unsigned int canDrawSubviewsIntoLayer:1;
	unsigned int allowsVibrancy:2;
	unsigned int needsDisplay:1;
	unsigned int wantsGState:1;
	unsigned int autoresizeSubviews:1;
	unsigned int autosizing:6;
	unsigned int rotatedOrScaledFromBase:1;
	unsigned int rotatedFromBase:1;
#endif
} _VFlags;

typedef NSInteger NSTrackingRectTag;
typedef NSInteger NSToolTipTag;

@class _NSViewAuxiliary;

@interface NSView : NSResponder <NSAnimatablePropertyContainer, NSUserInterfaceItemIdentification, NSDraggingDestination, NSAppearanceCustomization, NSAccessibilityElement, NSAccessibility>
{
    /* All instance variables are private */
    NSRect              _frame;
    NSRect              _bounds;
    id                  _superview;
    id                  _subviews;
    NSWindow           *_window;
    id                  _unused_was_gState;
    id                  _frameMatrix;
    CALayer             *_layer;
    id     	        _dragTypes;
    _NSViewAuxiliary    *_viewAuxiliary;
    _VFlags     	_vFlags;
    struct __VFlags2 {
        unsigned int nextKeyViewRefCount:14;
        unsigned int previousKeyViewRefCount:14;
        unsigned int isVisibleRect:1;
        unsigned int hasToolTip:1;
        unsigned int cachedIsFlipped:1;
        unsigned int menuWasSet:1;
    } _vFlags2;
}

- (instancetype)initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nullable, readonly, assign) NSWindow *window;
@property (nullable, readonly, assign) NSView *superview;
@property (copy) NSArray<__kindof NSView *> *subviews;
- (BOOL)isDescendantOf:(NSView *)aView;
- (nullable NSView *)ancestorSharedWithView:(NSView *)aView;
@property (nullable, readonly, assign) NSView *opaqueAncestor;
@property (getter=isHidden) BOOL hidden;
@property (getter=isHiddenOrHasHiddenAncestor, readonly) BOOL hiddenOrHasHiddenAncestor;

- (void)getRectsBeingDrawn:(const NSRect * __nullable * __nullable)rects count:(nullable NSInteger *)count;
- (BOOL)needsToDrawRect:(NSRect)aRect;
@property (readonly) BOOL wantsDefaultClipping;
- (void)viewDidHide NS_AVAILABLE_MAC(10_5);
- (void)viewDidUnhide NS_AVAILABLE_MAC(10_5);

- (void)addSubview:(NSView *)aView;
- (void)addSubview:(NSView *)aView positioned:(NSWindowOrderingMode)place relativeTo:(nullable NSView *)otherView;
- (void)sortSubviewsUsingFunction:(NSComparisonResult (*)(__kindof NSView *, __kindof NSView *,  void * __nullable))compare context:(nullable void *)context;

/* NOTE: In general, it is good practice to call 'super' for the viewWill* and viewDid* methods. Some AppKit subclasses, such as NSTableView, depend on this behavior, and calling super is required for things to work properly.
 */
- (void)viewWillMoveToWindow:(nullable NSWindow *)newWindow;
- (void)viewDidMoveToWindow;
- (void)viewWillMoveToSuperview:(nullable NSView *)newSuperview;
- (void)viewDidMoveToSuperview;

- (void)didAddSubview:(NSView *)subview;
- (void)willRemoveSubview:(NSView *)subview;

- (void)removeFromSuperview;
- (void)replaceSubview:(NSView *)oldView with:(NSView *)newView;
- (void)removeFromSuperviewWithoutNeedingDisplay;
- (void)viewDidChangeBackingProperties NS_AVAILABLE_MAC(10_7); // available in 10.7.4

@property BOOL postsFrameChangedNotifications;

- (void)resizeSubviewsWithOldSize:(NSSize)oldSize;
- (void)resizeWithOldSuperviewSize:(NSSize)oldSize;
@property BOOL autoresizesSubviews;
@property NSAutoresizingMaskOptions autoresizingMask;

- (void)setFrameOrigin:(NSPoint)newOrigin;
- (void)setFrameSize:(NSSize)newSize;
@property NSRect frame;
@property CGFloat frameRotation;
@property CGFloat frameCenterRotation NS_AVAILABLE_MAC(10_5);

- (void)setBoundsOrigin:(NSPoint)newOrigin;
- (void)setBoundsSize:(NSSize)newSize;
@property CGFloat boundsRotation;
- (void)translateOriginToPoint:(NSPoint)translation;
- (void)scaleUnitSquareToSize:(NSSize)newUnitSize;
- (void)rotateByAngle:(CGFloat)angle;
@property NSRect bounds;

@property (getter=isFlipped, readonly) BOOL flipped;
@property (getter=isRotatedFromBase, readonly) BOOL rotatedFromBase;
@property (getter=isRotatedOrScaledFromBase, readonly) BOOL rotatedOrScaledFromBase;

/* A hint as to whether or not this view draws its contents completely opaque or not. Opaque content drawing can allow some optimizations to happen. The default value is NO.
 */
@property (getter=isOpaque, readonly) BOOL opaque;

- (NSPoint)convertPoint:(NSPoint)aPoint fromView:(nullable NSView *)aView;
- (NSPoint)convertPoint:(NSPoint)aPoint toView:(nullable NSView *)aView;
- (NSSize)convertSize:(NSSize)aSize fromView:(nullable NSView *)aView;
- (NSSize)convertSize:(NSSize)aSize toView:(nullable NSView *)aView;
- (NSRect)convertRect:(NSRect)aRect fromView:(nullable NSView *)aView;
- (NSRect)convertRect:(NSRect)aRect toView:(nullable NSView *)aView;

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

/* Reports whether AppKit may invoke the view's -drawRect: method on a background thread, where it would otherwise be invoked on the main thread.  Defaults to NO.
*/
@property BOOL canDrawConcurrently NS_AVAILABLE_MAC(10_6);

/* Sets whether AppKit may invoke the view's -drawRect: method on a background thread, where it would otherwise be invoked on the main thread.  Defaults to NO for most kinds of views.  May be set to YES to enable threaded drawing for a particular view instance.  The view's window must also have its "allowsConcurrentViewDrawing" property set to YES (the default) for threading of view drawing to actually take place. */

@property (readonly) BOOL canDraw;
- (void)setNeedsDisplayInRect:(NSRect)invalidRect;
@property BOOL needsDisplay;
- (void)lockFocus;
- (void)unlockFocus;
- (BOOL)lockFocusIfCanDraw;
- (BOOL)lockFocusIfCanDrawInContext:(NSGraphicsContext *)context;
+ (nullable NSView *)focusView;
@property (readonly) NSRect visibleRect;

- (void)display;
- (void)displayIfNeeded;
- (void)displayIfNeededIgnoringOpacity;
- (void)displayRect:(NSRect)rect;
- (void)displayIfNeededInRect:(NSRect)rect;
- (void)displayRectIgnoringOpacity:(NSRect)rect;
- (void)displayIfNeededInRectIgnoringOpacity:(NSRect)rect;
- (void)drawRect:(NSRect)dirtyRect;
- (void)displayRectIgnoringOpacity:(NSRect)aRect inContext:(NSGraphicsContext *)context;

- (nullable NSBitmapImageRep *)bitmapImageRepForCachingDisplayInRect:(NSRect)rect;
- (void)cacheDisplayInRect:(NSRect)rect toBitmapImageRep:(NSBitmapImageRep *)bitmapImageRep;
- (void)viewWillDraw NS_AVAILABLE_MAC(10_5);

- (void)scrollPoint:(NSPoint)aPoint;
- (BOOL)scrollRectToVisible:(NSRect)aRect;
- (BOOL)autoscroll:(NSEvent *)theEvent;
- (NSRect)adjustScroll:(NSRect)newVisible;
- (void)scrollRect:(NSRect)aRect by:(NSSize)delta;
- (void)translateRectsNeedingDisplayInRect:(NSRect)clipRect by:(NSSize)delta NS_AVAILABLE_MAC(10_5);

- (nullable NSView *)hitTest:(NSPoint)aPoint;
- (BOOL)mouse:(NSPoint)aPoint inRect:(NSRect)aRect;
- (nullable __kindof NSView *)viewWithTag:(NSInteger)aTag;
@property (readonly) NSInteger tag;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (BOOL)acceptsFirstMouse:(nullable NSEvent *)theEvent;
- (BOOL)shouldDelayWindowOrderingForEvent:(NSEvent *)theEvent;
@property (readonly) BOOL needsPanelToBecomeKey;
@property (readonly) BOOL mouseDownCanMoveWindow;

/* By default, views do not accept touch events
*/
@property BOOL acceptsTouchEvents NS_AVAILABLE_MAC(10_6);

/* In some cases, the user may rest a thumb or other touch on the device. By default, these touches are not delivered and are not included in the event's set of touches. Touches may transition in and out of resting at any time. Unless the view wants restingTouches, began / ended events are simlulated as touches transition from resting to active and vice versa.
*/
@property BOOL wantsRestingTouches NS_AVAILABLE_MAC(10_6);

- (void)addCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)removeCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)discardCursorRects;
- (void)resetCursorRects;

- (NSTrackingRectTag)addTrackingRect:(NSRect)aRect owner:(id)anObject userData:(nullable void *)data assumeInside:(BOOL)flag;
- (void)removeTrackingRect:(NSTrackingRectTag)tag;

- (CALayer *)makeBackingLayer NS_AVAILABLE_MAC(10_6);

/* Get and set how the layer should redraw when resizing and redisplaying. Prior to 10.8, the default value was always set to NSViewLayerContentsRedrawDuringViewResize when an AppKit managed layer was created. In 10.8 and higher, the value is initialized to the appropriate thing for each individual AppKit view. Generally, the default value is NSViewLayerContentsRedrawOnSetNeedsDisplay if the view responds YES to -wantsUpdateLayer. Otherwise, the value is usually NSViewLayerContentsRedrawDuringViewResize, indicating that the view needs to redraw on each step of an animation via a setFrame: change. On 10.8, the value is not encoded by the view.
*/
@property NSViewLayerContentsRedrawPolicy layerContentsRedrawPolicy NS_AVAILABLE_MAC(10_6);

@property NSViewLayerContentsPlacement layerContentsPlacement NS_AVAILABLE_MAC(10_6);

/* Indicates if this view should be a "Layer Backed View". When layer backed, all subviews will subsequently also have a layer set on them (however, wantsLayer will only be YES on views that have had it explicitly set). Contents for a layer are specified in one of two ways: if -wantsUpdateLayer returns YES, then one can directly update the layer's contents (or other properties) in -updateLayer. If -wantsUpdateLayer returns NO, then the layer's contents is filled with whatever is drawn by -drawRect:
 */
@property BOOL wantsLayer NS_AVAILABLE_MAC(10_5);

/* Get and set the CALayer for this view. The layer is not encoded by the view.
 */
@property (nullable, strong) CALayer *layer NS_AVAILABLE_MAC(10_5);

/* Layer Backed Views: Return YES if this view supports directly setting the layer properties (such as the contents and backgroundColor) as opposed to filling in the contents with a drawRect: implementation. Most AppKit controls return YES if there is no subclassing involved that would alter the drawing appearance. It will return NO for views that do have subclassing that AppKit does not know about (such as, overriding drawRect:, or other drawing methods).
 */
@property (readonly) BOOL wantsUpdateLayer NS_AVAILABLE_MAC(10_8);

/* Layer Backed Views: If the view responds YES to wantsUpdateLayer, then updateLayer will be called as opposed to drawRect:. This method should be used for better performance; it is faster to directly set the layer.contents with a shared image and inform it how to stretch with the layer.contentsCenter property instead of drawing into a context with drawRect:. In general, one should also set the layerContentsRedrawPolicy to an appropriate value in the init method (frequently NSViewLayerContentsRedrawOnSetNeedsDisplay is desired). To signal a refresh of the layer contents, one will then call [view setNeedsDisplay:YES], and -updateLayer will be lazily called when the layer needs its contents. One should not alter geometry or add/remove subviews (or layers) during this method. To add subviews (or layers) use -layout. -layout will still be called even if autolayout is not enabled, and wantsUpdateLayer returns YES.
 */
- (void)updateLayer NS_AVAILABLE_MAC(10_8);

/* When canDrawSubviewsIntoLayer is set to YES, and the view is layer-backed (either explicitly with -wantsLayer=YES, or by having a parent view that is layer-backed), the layer will draw all subviews into this view's layer, and each subview will not get an individual layer (the exception to this is a subview which has wantsLayer explicitly set to YES). This is useful for layer-backing a complex set of views that can not be refactored to take advantage of proper resizing and -wantsUpdateLayer==YES. If canDrawSubviewsIntoLayer is YES, the value returned from wantsUpdateLayer will be ignored, and the layer will always have drawRect: invoked to get the layer's contents. The default value is NO. NOTE: These methods should NOT be overridden, and the setter should always be used.
 */
@property BOOL canDrawSubviewsIntoLayer NS_AVAILABLE_MAC(10_9);

@property CGFloat alphaValue NS_AVAILABLE_MAC(10_5);

/* If you have set a custom layer on your view, and it (or one of its sublayers) uses CIFilters, you should set this. You do not need to set this if you are using the backgroundFilters, compositingFilter, or contentFilters properties below. See the release notes for more information.
 */
@property BOOL layerUsesCoreImageFilters NS_AVAILABLE_MAC(10_9);

@property (copy) NSArray<__kindof CIFilter *> *backgroundFilters NS_AVAILABLE_MAC(10_5);

@property (nullable, strong) CIFilter *compositingFilter NS_AVAILABLE_MAC(10_5);

@property (copy) NSArray<__kindof CIFilter *> *contentFilters NS_AVAILABLE_MAC(10_5);

@property (nullable, copy) NSShadow *shadow NS_AVAILABLE_MAC(10_5);

/* The following methods are meant to be invoked, and probably don't need to be overridden
*/
- (void)addTrackingArea:(NSTrackingArea *)trackingArea NS_AVAILABLE_MAC(10_5);
- (void)removeTrackingArea:(NSTrackingArea *)trackingArea NS_AVAILABLE_MAC(10_5);
@property (readonly, copy) NSArray<NSTrackingArea *> *trackingAreas NS_AVAILABLE_MAC(10_5);

/* updateTrackingAreas should be overridden to remove out of date tracking areas and add recomputed tracking areas, and should call super.
*/
- (void)updateTrackingAreas NS_AVAILABLE_MAC(10_5);

@property BOOL postsBoundsChangedNotifications;

@property (nullable, readonly, strong) NSScrollView *enclosingScrollView;

- (nullable NSMenu *)menuForEvent:(NSEvent *)event;
+ (nullable NSMenu *)defaultMenu;

/*!
 * A contextual menu is being opened from the receiving view.
 * The view should update any visual state in response — such as making a selection.
 * \param menu The contextual menu that is being opened on the view
 * \param event The event that caused the menu to open.
 */
- (void)willOpenMenu:(NSMenu *)menu withEvent:(NSEvent *)event NS_AVAILABLE_MAC(10_11);

/*!
 * A contextual menu shown from the receiving view has been closed. This is only called if the menu had been opened and the view previously received \c -willOpenMenu:withEvent:.
 * The view should update any visual state in response — such as removing a temporary selection.
 * \param menu The contextual menu that was open on the view
 * \param event The event that caused the menu to close. This may be nil if there is no specific event that triggered the closing.
 */
- (void)didCloseMenu:(NSMenu *)menu withEvent:(nullable NSEvent *)event NS_AVAILABLE_MAC(10_11);

@property (nullable, copy) NSString *toolTip;
- (NSToolTipTag)addToolTipRect:(NSRect)aRect owner:(id)anObject userData:(nullable void *)data;
- (void)removeToolTip:(NSToolTipTag)tag;
- (void)removeAllToolTips;

/* Live resize support */
/* A view receives viewWillStartLiveResize before the frame is first changed for a live resize. It is important to call [super viewWillStartLiveResize] to allow AppKit to do any internal work it needs. */
- (void)viewWillStartLiveResize;

/* A view receives viewWillEndLiveResize after the frame is last changed for a live resize. It is important to call [super viewDidEndLiveResize].
 */
- (void)viewDidEndLiveResize;

/* inLiveResize can be called at any time to determine if the window is performing a live resize or not. Drawing optimizations can be done when the view is being live-resized.
 */
@property (readonly) BOOL inLiveResize;

/* A view that returns YES for -preservesContentDuringLiveResize is responsible for invalidating its own dirty rects during live resize 
 */
@property (readonly) BOOL preservesContentDuringLiveResize;

/* -rectPreservedDuringLiveResize indicates the rect the view previously occupied, in the current coordinate system of the view 
 */
@property (readonly) NSRect rectPreservedDuringLiveResize;

/* On return from -getRectsExposedDuringLiveResize, exposedRects indicates the parts of the view that are newly exposed (at most 4 rects).  *count indicates how many rects are in the exposedRects list */
- (void)getRectsExposedDuringLiveResize:(NSRect[4])exposedRects count:(NSInteger *)count;

/* Text Input */
/* Returns NSTextInputContext object for the receiver. Returns nil if the receiver doesn't conform to NSTextInputClient protocol.
 */
@property (nullable, readonly, strong) NSTextInputContext *inputContext NS_AVAILABLE_MAC(10_6);

/* Return the complete rect of the most appropriate content grouping at the specified location. For example, if your content is divided into three columns, return the entire rect of the column that contains the location. NSScrollView will attempt to magnify such that the width fits inside the scroll view while remaining within the minMagnification, maxMagnification range.
 
 If your content layout is sub-divided further than one level deep (for example, two boxes that each contain multiple text boxes), then use the visibleRect parameter to determine when to provide the rect of a sub-grouping. Always return a rect for the appropriate grouping. If there is no deeper content grouping, return the rect for the deepest grouping. NSScrollView will determine when to pan, magnify in, and magnify out.
 
 Return NSZeroRect for the default behavior.
 */
- (NSRect)rectForSmartMagnificationAtPoint:(NSPoint)location inRect:(NSRect)visibleRect NS_AVAILABLE_MAC(10_8);

/* Get and set the user interface layout direction. By default, a basic NSView may not respect the User Interface Layout Direction that is uniquely set on it, and it is up to the developer and supporting subclasses to correctly implement a Right To Left layout implementation. The default value is set to [NSApp userInterfaceLayoutDirection]. 
 */
@property NSUserInterfaceLayoutDirection userInterfaceLayoutDirection NS_AVAILABLE_MAC(10_8);

/* The View Based NSTableView allows views to be reused. Sometimes it is necessary to prepare a view with some initial state before it is to be reused. This method can be overridden to allow a view to be prepared back to the default state. Override this method to do the preparation. By default, NSView will do some setup, such as setting the view to not be hidden and have a 1.0 alpha. It is important to call super to get this work done. This method was made public in 10.9, but exists back to 10.7.
 */
- (void)prepareForReuse NS_AVAILABLE_MAC(10_7);

/* A subclass of any NSScrollView, NSClipView or the NSScrollView's documentView can override this method to verify that its customizations are compatible with 10.9's responsive scrolling behavior. By default, AppKit assumes that a ScrollView is responsive scrolling compatible if it and its clipview and document view do not override certain methods such as -scrollWheel: (See documentation for the expanded list). However, these views may still opt into responsive scrolling if they work with the new scrolling behavior by overriding and returning YES for this method. Likewise, the same set of views may return NO to explicitly opt out of responsive scrolling.
*/
+ (BOOL)isCompatibleWithResponsiveScrolling NS_AVAILABLE_MAC(10_9);

/* Called by NSView with a 'rect' for a recommended area that should be fully rendered for overdraw. Override this method and bring in additional subviews and pre-cached content for the 'rect' in order to perform responsive scrolling. Calling super may be required for some subclasses (such as NSTableView and NSOutlineView), so in general, super should always be called. To suppress overdraw for a particular view (such as NSTableView), override this method and call [super prepareContentInRect:[self visibleRect]].
 */
- (void)prepareContentInRect:(NSRect)rect NS_AVAILABLE_MAC(10_9);

/* The preparedContentRect is the area of the NSView that has full content coverage. In general, this should be called with the area that is filled in fully with views.  Set this with a value equal to the visibleRect to have overdraw start from the visibleRect and automatically grow larger on idle, as is needed for optimal system performance. The result of preparedContentRect may include the visibleRect, and may not include it if the previously prepared area has been scrolled away.
 */
@property NSRect preparedContentRect NS_AVAILABLE_MAC(10_9);

/* allowsVibrancy is queried when a vibrant appearance is used on a view hierarchy. When allowsVibrancy returns YES, the view will have an appropriate measure taken to ensure it is vibrant on top of its given material.
 
 Specific subclasses, such as NSControl, will answer this question based on the artwork they draw for a given appearance.
 */
@property (readonly) BOOL allowsVibrancy NS_AVAILABLE_MAC(10_10);

@end

@interface NSObject (NSLayerDelegateContentsScaleUpdating)

/* This method can be implemented as an optional CALayer delegate method, for handling resolution changes.  When a window changes its backing resolution, AppKit attempts to automatically update the contentsScale and contents of all CALayers in the window to match the new resolution.  View backing layers are updated automatically.  Any layer whose "contents" property is set to an NSImage will also be updated automatically.  (Basedon the NSImage's available representations, AppKit will select an appropriate bitmapped representation, or rasterize a resolution-independent representation at the appropriate scale factor.)  For all other layers, AppKit will check whether the layer has a delegate that implements this method.  If so, AppKit will send this message to the layer's delegate to ask whether it should automatically update the contentsScale for that layer to match the backingScaleFactor of the window.  If you return YES for a given layer, AppKit will set the layer's contentsScale as proposed, and you must ensure that the layer's contents and other properties are configured appropriately for that new contentsScale.  (If you expressed the layer's "contents" as a CGImage, you may need to provide a different CGImage that's appropriate for the new contentsScale.) Note this method is only invoked when a window's backingScaleFactor changes. You are responsible for setting the initial contentsScale of your layers.
*/
- (BOOL)layer:(CALayer *)layer shouldInheritContentsScale:(CGFloat)newScale fromWindow:(NSWindow *)window NS_AVAILABLE_MAC(10_7); // added in 10.7.3

@end

@interface NSObject(NSToolTipOwner)
- (NSString *)view:(NSView *)view stringForToolTip:(NSToolTipTag)tag point:(NSPoint)point userData:(nullable void *)data;
@end

@interface NSView(NSKeyboardUI)
@property (nullable, assign) NSView *nextKeyView;
@property (nullable, readonly, assign) NSView *previousKeyView;
@property (nullable, readonly, assign) NSView *nextValidKeyView;
@property (nullable, readonly, assign) NSView *previousValidKeyView;

@property (readonly) BOOL canBecomeKeyView;

- (void)setKeyboardFocusRingNeedsDisplayInRect:(NSRect)rect;

@property NSFocusRingType focusRingType;
+ (NSFocusRingType)defaultFocusRingType;

- (void)drawFocusRingMask NS_AVAILABLE_MAC(10_7);
@property (readonly) NSRect focusRingMaskBounds NS_AVAILABLE_MAC(10_7);
- (void)noteFocusRingMaskChanged NS_AVAILABLE_MAC(10_7);

@end

@interface NSView(NSPrinting)

/* EPS/PDF generation */
- (void)writeEPSInsideRect:(NSRect)rect toPasteboard:(NSPasteboard *)pasteboard;
- (NSData *)dataWithEPSInsideRect:(NSRect)rect;
- (void)writePDFInsideRect:(NSRect)rect toPasteboard:(NSPasteboard *)pasteboard;
- (NSData *)dataWithPDFInsideRect:(NSRect)rect;

/* Printing action method (Note fax: is obsolete) */
- (void)print:(nullable id)sender;

/* Pagination */
- (BOOL)knowsPageRange:(NSRangePointer)range;
@property (readonly) CGFloat heightAdjustLimit;
@property (readonly) CGFloat widthAdjustLimit;
- (void)adjustPageWidthNew:(CGFloat *)newRight left:(CGFloat)oldLeft right:(CGFloat)oldRight limit:(CGFloat)rightLimit;
- (void)adjustPageHeightNew:(CGFloat *)newBottom top:(CGFloat)oldTop bottom:(CGFloat)oldBottom limit:(CGFloat)bottomLimit;
- (NSRect)rectForPage:(NSInteger)page;
- (NSPoint)locationOfPrintRect:(NSRect)aRect;
- (void)drawPageBorderWithSize:(NSSize)borderSize;
@property (readonly, copy) NSAttributedString *pageHeader;
@property (readonly, copy) NSAttributedString *pageFooter;

/*** This method is obsolete.  It will never be invoked from within AppKit, and NSView's implementation of it does nothing. ***/
- (void)drawSheetBorderWithSize:(NSSize)borderSize;

/* Printing */
/* Returns print job title. Default implementation first tries its window's NSDocument (displayName), then window's title */
@property (readonly, copy) NSString *printJobTitle;
- (void)beginDocument;
- (void)endDocument;

- (void)beginPageInRect:(NSRect)aRect atPlacement:(NSPoint)location;
- (void)endPage;
@end


@interface NSView(NSDrag)
/* Starts a dragging session with a group of NSDraggingItems. The frame property of each NSDraggingItem must be in the view's coordinate system. The images may animate (flock) from thier initial layout into a system defined formation. Flocking or may not be done immediately. (see NSDraggingSession's flockOnBeginDrag. The visible area of the view is used as the clip rect.
*/
- (NSDraggingSession *)beginDraggingSessionWithItems:(NSArray<NSDraggingItem *> *)items event:(NSEvent *)event source:(id<NSDraggingSource>)source NS_AVAILABLE_MAC(10_7);

@property (readonly, copy) NSArray<NSString *> *registeredDraggedTypes;
- (void)registerForDraggedTypes:(NSArray<NSString *> *)newTypes;
- (void)unregisterDraggedTypes;

- (BOOL)dragFile:(NSString *)filename fromRect:(NSRect)rect slideBack:(BOOL)aFlag event:(NSEvent *)event;
- (BOOL)dragPromisedFilesOfTypes:(NSArray<NSString *> *)typeArray fromRect:(NSRect)rect source:(id)sourceObject slideBack:(BOOL)aFlag event:(NSEvent *)event;
@end

@interface NSView (NSFullScreenMode) 
- (BOOL)enterFullScreenMode:(NSScreen *)screen withOptions:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE_MAC(10_5);
- (void)exitFullScreenModeWithOptions:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE_MAC(10_5);
@property (getter=isInFullScreenMode, readonly) BOOL inFullScreenMode NS_AVAILABLE_MAC(10_5); 
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
- (void)showDefinitionForAttributedString:(nullable NSAttributedString *)attrString atPoint:(NSPoint)textBaselineOrigin NS_AVAILABLE_MAC(10_6);

/* Takes a whole attributed string with the target range (normally, this is the selected range), and shows a window displaying the definition of the specified range.  The caller can pass a zero-length range and the appropriate range will be auto-detected around the range's offset.  That's the recommended approach when there is no selection.
 
 This method also an 'options' dictionary containing options described below as key-value pairs (can be nil).
 
 Except when NSDefinitionPresentationTypeKey with NSDefinitionPresentationTypeDictionaryApplication is specified in options, the caller must supply an originProvider Block which returns the baseline origin of the first character at proposed adjustedRange in the receiver view coordinate system.
 
 If the receiver is an NSTextView, both attrString and originProvider may be nil, in which case the text view will automatically supply values suitable for displaying definitions for the specified range within its text content.  This method does not cause scrolling, so clients should perform any necessary scrolling before calling this method.
 */
- (void)showDefinitionForAttributedString:(nullable NSAttributedString *)attrString range:(NSRange)targetRange options:(nullable NSDictionary<NSString *, id> *)options baselineOriginProvider:(NSPoint (^ __nullable)(NSRange adjustedRange))originProvider NS_AVAILABLE_MAC(10_6);

@end

/* NSDefinitionPresentationTypeKey is an optional key in 'options' that specifies the presentation type of the definition display.  The possible values are NSDefinitionPresentationTypeOverlay that produces a small overlay window at the string location, or NSDefinitionPresentationTypeDictionaryApplication that invokes 'Dictionary' application to display the definition.  Without this option, the definition will be shown in either of those presentation forms depending on the 'Contextual Menu:' setting in Dictionary application preferences.
 */
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeKey NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeOverlay NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSDefinitionPresentationTypeDictionaryApplication NS_AVAILABLE_MAC(10_6);


@interface NSView(NSFindIndicator)

/* When this method returns YES, the receiver or one of its ancestors is being drawn for a find indicator, meaning the receiver should draw so its contents will be easily readable.
 */
@property (getter=isDrawingFindIndicator, readonly) BOOL drawingFindIndicator NS_AVAILABLE_MAC(10_7);

@end



@interface NSView (NSGestureRecognizer)
@property (copy) NSArray<__kindof NSGestureRecognizer *> *gestureRecognizers NS_AVAILABLE_MAC(10_10);
- (void)addGestureRecognizer:(NSGestureRecognizer *)gestureRecognizer NS_AVAILABLE_MAC(10_10);
- (void)removeGestureRecognizer:(NSGestureRecognizer *)gestureRecognizer NS_AVAILABLE_MAC(10_10);
@end

@interface NSView(NSDeprecated)

/* This drag method as been deprecated in favor of beginDraggingSessionWithItems:event:source:
 */
- (void)dragImage:(NSImage *)anImage at:(NSPoint)viewLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag NS_DEPRECATED_MAC(10_0, 10_7, "Use -beginDraggingSessionWithItems:event:source: instead");

/* These methods are deprecated on 10.7 and later. */
- (NSPoint)convertPointToBase:(NSPoint)aPoint NS_DEPRECATED_MAC(10_5, 10_7);
- (NSPoint)convertPointFromBase:(NSPoint)aPoint NS_DEPRECATED_MAC(10_5, 10_7);
- (NSSize)convertSizeToBase:(NSSize)aSize NS_DEPRECATED_MAC(10_5, 10_7);
- (NSSize)convertSizeFromBase:(NSSize)aSize NS_DEPRECATED_MAC(10_5, 10_7);
- (NSRect)convertRectToBase:(NSRect)aRect NS_DEPRECATED_MAC(10_5, 10_7);
- (NSRect)convertRectFromBase:(NSRect)aRect NS_DEPRECATED_MAC(10_5, 10_7);

/* This method is deprecated in 10.8 and higher. On MacOS it has historically not done anything.
 */
- (BOOL)performMnemonic:(NSString *)theString NS_DEPRECATED_MAC(10_0, 10_8);

/* shouldDrawColor is no longer used by AppKit.
 */
- (BOOL)shouldDrawColor NS_DEPRECATED_MAC(10_0, 10_10);

/* The gState class of methods are deprecatd and in many cases did not do anything, or not what one would expect.
 */
- (NSInteger)gState NS_DEPRECATED_MAC(10_0, 10_10);
- (void)allocateGState NS_DEPRECATED_MAC(10_0, 10_10);
- (oneway void)releaseGState NS_DEPRECATED_MAC(10_0, 10_10);
- (void)setUpGState NS_DEPRECATED_MAC(10_0, 10_10);
- (void)renewGState NS_DEPRECATED_MAC(10_0, 10_10);
                                      
@end


/* Notifications */

/* Sent when the frame changes for a view. This is only sent if postsFrameChangedNotifications is set to YES.
 */
APPKIT_EXTERN NSString *NSViewFrameDidChangeNotification;
APPKIT_EXTERN NSString *NSViewFocusDidChangeNotification;

/* This notification is sent whenever the views bounds change and the frame does not.  That is, it is sent whenever the view's bounds are translated, scaled or rotated, but NOT when the bounds change as a result of, for example, setFrameSize:.
 */
APPKIT_EXTERN NSString *NSViewBoundsDidChangeNotification;

/* This notification is sent whenever an NSView that has an attached NSSurface changes size or changes screens (thus potentially changing graphics hardware drivers.)
 */
APPKIT_EXTERN NSString *NSViewGlobalFrameDidChangeNotification;
    
/* This notification is sent whenever tracking areas should be recalculated for the view.  It is sent after the view receives -updateTrackingAreas.
 */
APPKIT_EXTERN NSString *NSViewDidUpdateTrackingAreasNotification NS_AVAILABLE_MAC(10_5);

NS_ASSUME_NONNULL_END

