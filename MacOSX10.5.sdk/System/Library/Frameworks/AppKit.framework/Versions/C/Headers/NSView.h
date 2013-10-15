/*
	NSView.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSRange.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSAnimation.h>

@class NSBitmapImageRep, NSCursor, NSGraphicsContext, NSImage, NSPasteboard, NSScrollView, NSWindow, NSAttributedString;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@class CIFilter, CALayer, NSDictionary, NSScreen, NSShadow, NSTrackingArea;
#endif

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

@interface NSView : NSResponder
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
<NSAnimatablePropertyContainer>
#endif
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setHidden:(BOOL)flag;
- (BOOL)isHidden;
- (BOOL)isHiddenOrHasHiddenAncestor;

- (void)getRectsBeingDrawn:(const NSRect **)rects count:(NSInteger *)count;
- (BOOL)needsToDrawRect:(NSRect)aRect;
- (BOOL)wantsDefaultClipping;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)viewDidHide;
- (void)viewDidUnhide;

- (void)setSubviews:(NSArray *)newSubviews;
#endif
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setFrameCenterRotation:(CGFloat)angle;
- (CGFloat)frameCenterRotation;
#endif

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
- (NSRect)centerScanRect:(NSRect)aRect;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSPoint)convertPointToBase:(NSPoint)aPoint;
- (NSPoint)convertPointFromBase:(NSPoint)aPoint;
- (NSSize)convertSizeToBase:(NSSize)aSize;
- (NSSize)convertSizeFromBase:(NSSize)aSize;
- (NSRect)convertRectToBase:(NSRect)aRect;
- (NSRect)convertRectFromBase:(NSRect)aRect;
#endif

- (BOOL)canDraw;
- (void)setNeedsDisplay:(BOOL)flag;
- (void)setNeedsDisplayInRect:(NSRect)invalidRect;
- (BOOL)needsDisplay;
- (void)lockFocus;
- (void)unlockFocus;
- (BOOL)lockFocusIfCanDraw;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)lockFocusIfCanDrawInContext:(NSGraphicsContext *)context;
#endif
+ (NSView *)focusView;
- (NSRect)visibleRect;

- (void)display;
- (void)displayIfNeeded;
- (void)displayIfNeededIgnoringOpacity;
- (void)displayRect:(NSRect)rect;
- (void)displayIfNeededInRect:(NSRect)rect;
- (void)displayRectIgnoringOpacity:(NSRect)rect;
- (void)displayIfNeededInRectIgnoringOpacity:(NSRect)rect;
- (void)drawRect:(NSRect)rect;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)displayRectIgnoringOpacity:(NSRect)aRect inContext:(NSGraphicsContext *)context;

- (NSBitmapImageRep *)bitmapImageRepForCachingDisplayInRect:(NSRect)rect;
- (void)cacheDisplayInRect:(NSRect)rect toBitmapImageRep:(NSBitmapImageRep *)bitmapImageRep;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)viewWillDraw;
#endif

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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)translateRectsNeedingDisplayInRect:(NSRect)clipRect by:(NSSize)delta;
#endif

- (NSView *)hitTest:(NSPoint)aPoint;
- (BOOL)mouse:(NSPoint)aPoint inRect:(NSRect)aRect;
- (id)viewWithTag:(NSInteger)aTag;
- (NSInteger)tag;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;
- (BOOL)shouldDelayWindowOrderingForEvent:(NSEvent *)theEvent;
- (BOOL)needsPanelToBecomeKey;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (BOOL)mouseDownCanMoveWindow;
#endif

- (void)addCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)removeCursorRect:(NSRect)aRect cursor:(NSCursor *)anObj;
- (void)discardCursorRects;
- (void)resetCursorRects;

- (NSTrackingRectTag)addTrackingRect:(NSRect)aRect owner:(id)anObject userData:(void *)data assumeInside:(BOOL)flag;
- (void)removeTrackingRect:(NSTrackingRectTag)tag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setWantsLayer:(BOOL)flag;
- (BOOL)wantsLayer;

- (void)setLayer:(CALayer *)newLayer;
- (CALayer *)layer;

- (void)setAlphaValue:(CGFloat)viewAlpha;
- (CGFloat)alphaValue;

- (void)setBackgroundFilters:(NSArray *)filters;
- (NSArray *)backgroundFilters;

- (void)setCompositingFilter:(CIFilter *)filter;
- (CIFilter *)compositingFilter;

- (void)setContentFilters:(NSArray *)filters;
- (NSArray *)contentFilters;

- (void)setShadow:(NSShadow *)shadow;
- (NSShadow *)shadow;

/* The following methods are meant to be invoked, and probably don't need to be overridden
*/
- (void)addTrackingArea:(NSTrackingArea *)trackingArea;
- (void)removeTrackingArea:(NSTrackingArea *)trackingArea;
- (NSArray *)trackingAreas;

/* updateTrackingAreas should be overridden to remove out of date tracking areas and add recomputed tracking areas, and should call super.
*/
- (void)updateTrackingAreas;
#endif


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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* A view that returns YES for -preservesContentDuringLiveResize is responsible for invalidating its own dirty rects during live resize */
- (BOOL)preservesContentDuringLiveResize;
/* -rectPreservedDuringLiveResize indicates the rect the view previously occupied, in the current coordinate system of the view */
- (NSRect)rectPreservedDuringLiveResize;
/* On return from -getRectsExposedDuringLiveResize, exposedRects indicates the parts of the view that are newly exposed (at most 4 rects).  *count indicates how many rects are in the exposedRects list */
- (void)getRectsExposedDuringLiveResize:(NSRect[4])exposedRects count:(NSInteger *)count;
#endif
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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (BOOL)canBecomeKeyView;
#endif

- (void)setKeyboardFocusRingNeedsDisplayInRect:(NSRect)rect;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setFocusRingType:(NSFocusRingType)focusRingType;
- (NSFocusRingType)focusRingType;
+ (NSFocusRingType)defaultFocusRingType;
#endif
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSAttributedString *)pageHeader;
- (NSAttributedString *)pageFooter;
#endif

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
- (void)dragImage:(NSImage *)anImage at:(NSPoint)viewLocation offset:(NSSize)initialOffset event:(NSEvent *)event pasteboard:(NSPasteboard *)pboard source:(id)sourceObj slideBack:(BOOL)slideFlag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSArray *)registeredDraggedTypes;
#endif
- (void)registerForDraggedTypes:(NSArray *)newTypes;
- (void)unregisterDraggedTypes;

- (BOOL)dragFile:(NSString *)filename fromRect:(NSRect)rect slideBack:(BOOL)aFlag event:(NSEvent *)event;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (BOOL)dragPromisedFilesOfTypes:(NSArray *)typeArray fromRect:(NSRect)rect source:(id)sourceObject slideBack:(BOOL)aFlag event:(NSEvent *)event;
#endif
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@interface NSView (NSFullScreenMode) 
- (BOOL)enterFullScreenMode:(NSScreen *)screen withOptions:(NSDictionary *)options;
- (void)exitFullScreenModeWithOptions:(NSDictionary *)options;
- (BOOL)isInFullScreenMode; 
@end

/* Constants for options when entering and exiting full screen mode */
APPKIT_EXTERN NSString * const NSFullScreenModeAllScreens;     // NSNumber numberWithBool:YES/NO
APPKIT_EXTERN NSString * const NSFullScreenModeSetting;        // NSDictionary (obtained from CGSDisplay based functions)
APPKIT_EXTERN NSString * const NSFullScreenModeWindowLevel;	   // NSNumber numberWithInt:windowLevel
#endif

/* Notifications */

APPKIT_EXTERN NSString *NSViewFrameDidChangeNotification;
APPKIT_EXTERN NSString *NSViewFocusDidChangeNotification;
APPKIT_EXTERN NSString *NSViewBoundsDidChangeNotification;
    // This notification is sent whenever the views bounds change and the frame does not.  That is, it is sent whenever the view's bounds are translated, scaled or rotated, but NOT when the bounds change as a result of, for example, setFrameSize:.
APPKIT_EXTERN NSString *NSViewGlobalFrameDidChangeNotification;
    // This notification is sent whenever an NSView that has an attached NSSurface changes size or changes screens (thus potentially changing graphics hardware drivers.)
    
APPKIT_EXTERN NSString *NSViewDidUpdateTrackingAreasNotification AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
    // This notification is sent whenever tracking areas should be recalculated for the view.  It is sent after the view receives -updateTrackingAreas.
