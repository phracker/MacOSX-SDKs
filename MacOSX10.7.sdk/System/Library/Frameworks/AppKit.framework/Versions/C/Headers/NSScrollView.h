/*
	NSScrollView.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/
#import <Foundation/NSDate.h>
#import <AppKit/NSView.h>
#import <AppKit/NSScroller.h>
#import <AppKit/NSTextFinder.h>

@class NSColor, NSClipView, NSRulerView, NSScroller;

#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSScrollElasticityAutomatic = 0, // automatically determine whether to allow elasticity on this axis
    NSScrollElasticityNone      = 1, // disallow scrolling beyond document bounds on this axis
    NSScrollElasticityAllowed   = 2, // allow content to be scrolled past its bounds on this axis in an elastic fashion
};
#endif
typedef NSInteger NSScrollElasticity; 

typedef struct __SFlags {
#ifdef __BIG_ENDIAN__
    unsigned int vScrollerRequired:1;
    unsigned int hScrollerRequired:1;
    unsigned int vScrollerStatus:1;
    unsigned int hScrollerStatus:1;
    unsigned int noDynamicScrolling:1;
    NSBorderType borderType:2;
    unsigned int oldRulerInstalled:1;
    unsigned int showRulers:1;
    unsigned int hasHorizontalRuler:1;
    unsigned int hasVerticalRuler:1;
    unsigned int needsTile:1;
    unsigned int doesNotDrawBackground:1;
    unsigned int skipRemoveSuperviewCheck:1;
    unsigned int focusRingNeedsRedisplay:1;
    unsigned int hasCustomLineBorderColor:1;
    unsigned int autohidesScrollers:1;
    unsigned int autoforwardsScrollWheelEvents:1;
    unsigned int findBarVisible:1;
    unsigned int unused:1;
    unsigned int vContentElasticity:2;
    unsigned int hContentElasticity:2;
    unsigned int predominantAxisScrolling:1;
    unsigned int findBarPosition:2;
    unsigned int RESERVED:5;
#else
    unsigned int RESERVED:5;
    unsigned int findBarPosition:2;
    unsigned int predominantAxisScrolling:1;
    unsigned int hContentElasticity:2;
    unsigned int vContentElasticity:2;
    unsigned int unused:1;
    unsigned int findBarVisible:1;
    unsigned int autoforwardsScrollWheelEvents:1;
    unsigned int autohidesScrollers:1;
    unsigned int hasCustomLineBorderColor:1;
    unsigned int focusRingNeedsRedisplay:1;
    unsigned int skipRemoveSuperviewCheck:1;
    unsigned int doesNotDrawBackground:1;
    unsigned int needsTile:1;
    unsigned int hasVerticalRuler:1;
    unsigned int hasHorizontalRuler:1;
    unsigned int showRulers:1;
    unsigned int oldRulerInstalled:1;
    NSBorderType borderType:2;
    unsigned int noDynamicScrolling:1;
    unsigned int hScrollerStatus:1;
    unsigned int vScrollerStatus:1;
    unsigned int hScrollerRequired:1;
    unsigned int vScrollerRequired:1;
#endif
} _SFlags;

@interface NSScrollView : NSView <NSTextFinderBarContainer>
{
    /*All instance variables are private*/
    NSScroller *_vScroller;
    NSScroller *_hScroller;
    NSClipView *_contentView;
    NSClipView *_headerClipView;
    NSView *    _cornerView;
    id          _ruler;
    _SFlags     _sFlags;
    __strong void *_extraIvars;
    
    // new rulers
    NSRulerView *_horizontalRuler;
    NSRulerView *_verticalRuler;
}

/* Returns the NSScrollView frame size that yields the specified contentView frame size.  This method should be used in preference to the deprecated +frameSizeForContentSize:hasHorizontalScroller:hasVerticalScroller:borderType:, which makes assumptions about the scrollers' classes, control size, and style.  The "horizontalScrollerClass" parameter should specify the class of horizontal scroller to use if the NSScrollView will have a horizontal scroller, or Nil if it will not.  Likewise for the "verticalScrollerClass" parameter.
*/
+ (NSSize)frameSizeForContentSize:(NSSize)cSize horizontalScrollerClass:(Class)horizontalScrollerClass verticalScrollerClass:(Class)verticalScrollerClass borderType:(NSBorderType)aType controlSize:(NSControlSize)controlSize scrollerStyle:(NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Returns the contentView frame size that yields the specified NSScrollView frame size.  This method should be used in preference to the deprecated +contentSizeForFrameSize:hasHorizontalScroller:hasVerticalScroller:borderType: method, which makes assumptions about the scrollers' classes, control size, and style.  The "horizontalScrollerClass" parameter should specify the class of horizontal scroller to use if the NSScrollView will have a horizontal scroller, or Nil if it will not.  Likewise for the "verticalScrollerClass" parameter.
*/
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize horizontalScrollerClass:(Class)horizontalScrollerClass verticalScrollerClass:(Class)verticalScrollerClass borderType:(NSBorderType)aType controlSize:(NSControlSize)controlSize scrollerStyle:(NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Returns the NSScrollView frame size that yields the specified contentView frame size.  This method assumes scrollers of NSRegularControlSize, that are not subclassed in a way that affects their metrics (scrollerWidth), and also assumes that scrollers of the current [NSScroller preferredScrollerStyle] will be used, which may not be the case if conditions such as legacy scroller subclassing or presence of accessory views force fallback to NSScrollerStyleLegacy for a particular NSScrollView instance.  Since those assumptions will produce incorrect results for some cases, this method should be considered deprecated; use +frameSizeForContentSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle:, which provides for full specification of the relevant parameters, instead.
*/
+ (NSSize)frameSizeForContentSize:(NSSize)cSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType; /* deprecated in 10.7 */

/*Returns the contentView frame size that yields the specified NSScrollView frame size.  This method assumes scrollers of NSRegularControlSize, that are not subclassed in a way that affects their metrics (scrollerWidth), and also assumes that scrollers of the current [NSScroller preferredScrollerStyle] will be used, which may not be the case if conditions such as legacy scroller subclassing or presence of accessory views force fallback to NSScrollerStyleLegacy for a particular NSScrollView instance.  Since those assumptions will produce incorrect results for some cases, this method should be considered deprecated; use +contentSizeForFrameSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle:, which provides for full specification of the relevant parameters, instead.
*/
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType; /* deprecated in 10.7 */

- (NSRect)documentVisibleRect;
- (NSSize)contentSize;

- (void)setDocumentView:(NSView *)aView;
- (id)documentView;
- (void)setContentView:(NSClipView *)contentView;
- (NSClipView *)contentView;
- (void)setDocumentCursor:(NSCursor *)anObj;
- (NSCursor *)documentCursor;
- (void)setBorderType:(NSBorderType)aType;
- (NSBorderType)borderType;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setHasVerticalScroller:(BOOL)flag;
- (BOOL)hasVerticalScroller;
- (void)setHasHorizontalScroller:(BOOL)flag;
- (BOOL)hasHorizontalScroller;
- (void)setVerticalScroller:(NSScroller *)anObject;
- (NSScroller *)verticalScroller;
- (void)setHorizontalScroller:(NSScroller *)anObject;
- (NSScroller *)horizontalScroller;
- (BOOL)autohidesScrollers;
- (void)setAutohidesScrollers:(BOOL)flag;
- (void)setHorizontalLineScroll:(CGFloat)value;
- (void)setVerticalLineScroll:(CGFloat)value;
- (void)setLineScroll:(CGFloat)value;
- (CGFloat)horizontalLineScroll;
- (CGFloat)verticalLineScroll;
- (CGFloat)lineScroll;
- (void)setHorizontalPageScroll:(CGFloat)value;
- (void)setVerticalPageScroll:(CGFloat)value;
- (void)setPageScroll:(CGFloat)value;
- (CGFloat)horizontalPageScroll;
- (CGFloat)verticalPageScroll;
- (CGFloat)pageScroll;
- (void)setScrollsDynamically:(BOOL)flag;
- (BOOL)scrollsDynamically;
- (void)tile;
- (void)reflectScrolledClipView:(NSClipView *)cView;
- (void)scrollWheel:(NSEvent *)theEvent;

/* An NSScrollView's scrollerStyle determines the style of scrollers that it will use.  AppKit sets this property automatically at runtime, based on the user's "Show scroll bars" setting and (if relevant) the set of connected pointing devices and their configured scroll capabilities, as determined by [NSScroller preferredScrollerStyle].  Setting an NSScrollView's scrollerStyle sets the scrollerStyle of its horizontalScroller and verticalScroller to match the new value.  If the NSScrollView subsequently creates or is assigned a new horizontalScroller or verticalScroller, they will at that time be assigned the same scrollerStyle that was given to the NSScrollView.
*/
- (NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);
- (void)setScrollerStyle:(NSScrollerStyle)newScrollerStyle NS_AVAILABLE_MAC(10_7);

/* Applicable only to ScrolViews that use Overlay scrollers.  Setting an NSScrollView's scrollerKnobStyle sets the knobStyle of its horizontalScroller and verticalScroller to match the new value.  If the NSScrollView subsequently creates or is assigned a new horizontalScroller or verticalScroller, they will at that time be assigned the same knobStyle that was given to the NSScrollView.
*/
- (NSScrollerKnobStyle)scrollerKnobStyle NS_AVAILABLE_MAC(10_7);
- (void)setScrollerKnobStyle:(NSScrollerKnobStyle)newScrollerKnobStyle NS_AVAILABLE_MAC(10_7);

/* Applicable only to NSScrollViews that use Overlay scrollers.  This method can be invoked to cause the Overlay scroller knobs to be momentarily shown.
*/
- (void)flashScrollers NS_AVAILABLE_MAC(10_7);

/* NSScrollView can scroll its contents past its bounds to achieve an elastic effect. When set to NSScrollElasticityAutomatic, scrolling the horizontal axis beyond its document bounds only occurs if the document width is greater than the view width or, the vertical scroller is hidden and the horizontal scroller is visible. The default value is NSScrollElasticityAutomatic.
*/
- (NSScrollElasticity)horizontalScrollElasticity NS_AVAILABLE_MAC(10_7);
- (void)setHorizontalScrollElasticity:(NSScrollElasticity)elasticity NS_AVAILABLE_MAC(10_7);

/* NSScrollView can scroll its contents past its bounds to achieve an elastic effect. When set to NSScrollElasticityAuto, scrolling the vertical axis beyond its docment bounds occurs if any of the following are true: visible vertical scroller, content height greater than view height, horizontal scroller hidden
*/
- (NSScrollElasticity)verticalScrollElasticity NS_AVAILABLE_MAC(10_7);
- (void)setVerticalScrollElasticity:(NSScrollElasticity)elasticity NS_AVAILABLE_MAC(10_7);

/* Some content is scrollable in both the horizontal and vertical axes, but is predominantly scrolled one axis at a time. Other content (such as a drawing canvas) should scroll freely in both axes. Traditionally this is not an issue with scroll wheels since they can only scroll in one direction at a time. With scroll balls and touch surfaces, it becomes more difficult to determine the user's intention. This property helps NSScrollView determine the user's intention by specifying the type of scrolling content. When set to YES, NSScrollView will only scroll in the predominate direction the user is scrolling. The default value is YES for apps build on 10.7; NO otherwise.
*/
- (BOOL)usesPredominantAxisScrolling NS_AVAILABLE_MAC(10_7);
- (void)setUsesPredominantAxisScrolling:(BOOL)predominantAxisScrolling NS_AVAILABLE_MAC(10_7);

@end

@interface NSScrollView(NSRulerSupport)

+ (void)setRulerViewClass:(Class)rulerViewClass;
+ (Class)rulerViewClass;

- (void)setRulersVisible:(BOOL)flag;
- (BOOL)rulersVisible;

- (void)setHasHorizontalRuler:(BOOL)flag;
- (BOOL)hasHorizontalRuler;
- (void)setHasVerticalRuler:(BOOL)flag;
- (BOOL)hasVerticalRuler;

- (void)setHorizontalRulerView:(NSRulerView *)ruler;
- (NSRulerView *)horizontalRulerView;
- (void)setVerticalRulerView:(NSRulerView *)ruler;
- (NSRulerView *)verticalRulerView;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSScrollViewFindBarPositionAboveHorizontalRuler = 0,
    NSScrollViewFindBarPositionAboveContent = 1,
    NSScrollViewFindBarPositionBelowContent = 2
};
#endif
typedef NSInteger NSScrollViewFindBarPosition;

@interface NSScrollView(NSFindBarSupport)

- (void)setFindBarPosition:(NSScrollViewFindBarPosition)position NS_AVAILABLE_MAC(10_7);
- (NSScrollViewFindBarPosition)findBarPosition NS_AVAILABLE_MAC(10_7);

@end
