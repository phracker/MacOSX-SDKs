/*
	NSScrollView.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/
#import <Foundation/NSDate.h>
#import <AppKit/NSView.h>
#import <AppKit/NSScroller.h>
#import <AppKit/NSTextFinder.h>

#ifndef NSEDGEINSETS_DEFINED
#import <AppKit/NSLayoutConstraint.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSClipView, NSRulerView, NSScroller;

typedef NS_ENUM(NSInteger, NSScrollElasticity) {
    NSScrollElasticityAutomatic = 0, // automatically determine whether to allow elasticity on this axis
    NSScrollElasticityNone      = 1, // disallow scrolling beyond document bounds on this axis
    NSScrollElasticityAllowed   = 2, // allow content to be scrolled past its bounds on this axis in an elastic fashion
} NS_ENUM_AVAILABLE_MAC(10_7);

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
    unsigned int registeredForWindowWillClose:1;
    unsigned int unarchiving:1;
    unsigned int RESERVED:3;
#else
    unsigned int RESERVED:3;
    unsigned int unarchiving:1;
    unsigned int registeredForWindowWillClose:1;
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

- (instancetype)initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* Returns the NSScrollView frame size that yields the specified contentView frame size.  This method should be used in preference to the deprecated +frameSizeForContentSize:hasHorizontalScroller:hasVerticalScroller:borderType:, which makes assumptions about the scrollers' classes, control size, and style.  The "horizontalScrollerClass" parameter should specify the class of horizontal scroller to use if the NSScrollView will have a horizontal scroller, or Nil if it will not.  Likewise for the "verticalScrollerClass" parameter.
*/
+ (NSSize)frameSizeForContentSize:(NSSize)cSize horizontalScrollerClass:(nullable Class)horizontalScrollerClass verticalScrollerClass:(nullable Class)verticalScrollerClass borderType:(NSBorderType)aType controlSize:(NSControlSize)controlSize scrollerStyle:(NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Returns the contentView frame size that yields the specified NSScrollView frame size.  This method should be used in preference to the deprecated +contentSizeForFrameSize:hasHorizontalScroller:hasVerticalScroller:borderType: method, which makes assumptions about the scrollers' classes, control size, and style.  The "horizontalScrollerClass" parameter should specify the class of horizontal scroller to use if the NSScrollView will have a horizontal scroller, or Nil if it will not.  Likewise for the "verticalScrollerClass" parameter.
*/
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize horizontalScrollerClass:(nullable Class)horizontalScrollerClass verticalScrollerClass:(nullable Class)verticalScrollerClass borderType:(NSBorderType)aType controlSize:(NSControlSize)controlSize scrollerStyle:(NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Returns the NSScrollView frame size that yields the specified contentView frame size.  This method assumes scrollers of NSRegularControlSize, that are not subclassed in a way that affects their metrics (scrollerWidth), and also assumes that scrollers of the current [NSScroller preferredScrollerStyle] will be used, which may not be the case if conditions such as legacy scroller subclassing or presence of accessory views force fallback to NSScrollerStyleLegacy for a particular NSScrollView instance.  Since those assumptions will produce incorrect results for some cases, this method should be considered deprecated; use +frameSizeForContentSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle:, which provides for full specification of the relevant parameters, instead.
*/
+ (NSSize)frameSizeForContentSize:(NSSize)cSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType NS_DEPRECATED_MAC(10_0, 10_7, "Use +frameSizeForContentSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle: instead");

/*Returns the contentView frame size that yields the specified NSScrollView frame size.  This method assumes scrollers of NSRegularControlSize, that are not subclassed in a way that affects their metrics (scrollerWidth), and also assumes that scrollers of the current [NSScroller preferredScrollerStyle] will be used, which may not be the case if conditions such as legacy scroller subclassing or presence of accessory views force fallback to NSScrollerStyleLegacy for a particular NSScrollView instance.  Since those assumptions will produce incorrect results for some cases, this method should be considered deprecated; use +contentSizeForFrameSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle:, which provides for full specification of the relevant parameters, instead.
*/
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType NS_DEPRECATED_MAC(10_0, 10_7, "+contentSizeForFrameSize:horizontalScrollerClass:verticalScrollerClass:borderType:controlSize:scrollerStyle: instead");

@property (readonly) NSRect documentVisibleRect;
@property (readonly) NSSize contentSize;
@property (nullable, assign) id /* NSView * */ documentView;
@property (strong) NSClipView *contentView;
@property (nullable, strong) NSCursor *documentCursor;
@property NSBorderType borderType;
@property (copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property BOOL hasVerticalScroller;
@property BOOL hasHorizontalScroller;
@property (nullable, strong) NSScroller *verticalScroller;
@property (nullable, strong) NSScroller *horizontalScroller;
@property BOOL autohidesScrollers;
@property CGFloat horizontalLineScroll;
@property CGFloat verticalLineScroll;
@property CGFloat lineScroll;
@property CGFloat horizontalPageScroll;
@property CGFloat verticalPageScroll;
@property CGFloat pageScroll;
@property BOOL scrollsDynamically;
- (void)tile;
- (void)reflectScrolledClipView:(NSClipView *)cView;
- (void)scrollWheel:(NSEvent *)theEvent;

/* An NSScrollView's scrollerStyle determines the style of scrollers that it will use.  AppKit sets this property automatically at runtime, based on the user's "Show scroll bars" setting and (if relevant) the set of connected pointing devices and their configured scroll capabilities, as determined by [NSScroller preferredScrollerStyle].  Setting an NSScrollView's scrollerStyle sets the scrollerStyle of its horizontalScroller and verticalScroller to match the new value.  If the NSScrollView subsequently creates or is assigned a new horizontalScroller or verticalScroller, they will at that time be assigned the same scrollerStyle that was given to the NSScrollView.
*/
@property NSScrollerStyle scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Applicable only to ScrolViews that use Overlay scrollers.  Setting an NSScrollView's scrollerKnobStyle sets the knobStyle of its horizontalScroller and verticalScroller to match the new value.  If the NSScrollView subsequently creates or is assigned a new horizontalScroller or verticalScroller, they will at that time be assigned the same knobStyle that was given to the NSScrollView.
*/
@property NSScrollerKnobStyle scrollerKnobStyle NS_AVAILABLE_MAC(10_7);

/* Applicable only to NSScrollViews that use Overlay scrollers.  This method can be invoked to cause the Overlay scroller knobs to be momentarily shown.
*/
- (void)flashScrollers NS_AVAILABLE_MAC(10_7);

/* NSScrollView can scroll its contents past its bounds to achieve an elastic effect. When set to NSScrollElasticityAutomatic, scrolling the horizontal axis beyond its document bounds only occurs if the document width is greater than the view width or, the vertical scroller is hidden and the horizontal scroller is visible. The default value is NSScrollElasticityAutomatic.
*/
@property NSScrollElasticity horizontalScrollElasticity NS_AVAILABLE_MAC(10_7);

/* NSScrollView can scroll its contents past its bounds to achieve an elastic effect. When set to NSScrollElasticityAuto, scrolling the vertical axis beyond its docment bounds occurs if any of the following are true: visible vertical scroller, content height greater than view height, horizontal scroller hidden
*/
@property NSScrollElasticity verticalScrollElasticity NS_AVAILABLE_MAC(10_7);

/* Some content is scrollable in both the horizontal and vertical axes, but is predominantly scrolled one axis at a time. Other content (such as a drawing canvas) should scroll freely in both axes. Traditionally this is not an issue with scroll wheels since they can only scroll in one direction at a time. With scroll balls and touch surfaces, it becomes more difficult to determine the user's intention. This property helps NSScrollView determine the user's intention by specifying the type of scrolling content. When set to YES, NSScrollView will only scroll in the predominate direction the user is scrolling. The default value is YES for apps build on 10.7; NO otherwise.
*/
@property BOOL usesPredominantAxisScrolling NS_AVAILABLE_MAC(10_7);

/* Allow the user to magnify the scrollview. Note: this does not prevent the developer from manually adjusting the magnification value. If magnification exceeds either the maximum or minimum limits for magnification, and allowsMagnification is YES, the scroll view temporarily animates the content magnification just past those limits before returning to them. The default value is NO.
*/
@property BOOL allowsMagnification NS_AVAILABLE_MAC(10_8);

/* This value determines how much the content is currently scaled. To animate the magnification, use the object's animator. The default value is 1.0 */
@property CGFloat magnification NS_AVAILABLE_MAC(10_8);

/* This value determines how large the content can be magnified. It must be greater than or equal to the minimum magnification. The default value is 4.0.
*/
@property CGFloat maxMagnification NS_AVAILABLE_MAC(10_8);

/* This value determines how small the content can be magnified. The default value is 0.25.
*/
@property CGFloat minMagnification NS_AVAILABLE_MAC(10_8);

/* Magnify content view proportionally such that the entire rect (in content view space) fits centered in the scroll view. The resulting magnification value is clipped to the minMagnification and maxMagnification values. To animate the magnification, use the object's animator.
*/
- (void)magnifyToFitRect:(NSRect)rect NS_AVAILABLE_MAC(10_8);

/* Scale the content view such that the passed in point (in content view space) remains at the same screen location once the scaling is completed. The resulting magnification value is clipped to the minMagnification and maxMagnification values. To animate the magnification, use the object's animator.
*/
- (void)setMagnification:(CGFloat)magnification centeredAtPoint:(NSPoint)point NS_AVAILABLE_MAC(10_8);

/* Some subviews of the document view do not scroll like the rest of the document. Instead these views appear to float over the document (see NSTableView floating group rows). The following API makes it easier to work with these types of floating views. Note: You are responsible for keeping track of the floating views and removing them via -removeFromSuperview when they should no longer float. A view may only float on one axis at a time.
*/
- (void)addFloatingSubview:(NSView *)view forAxis:(NSEventGestureAxis)axis NS_AVAILABLE_MAC(10_9);


/*  Automatically sets the scroll view's contentInsets property to account for any overlapping title bar. Defaults to YES.
*/
@property BOOL automaticallyAdjustsContentInsets NS_AVAILABLE_MAC(10_10);

/* The distance that the sub views are inset from the enclosing scroll view during tiling. When contentInset equal to NSEdgeInsetsZero, traditional tiling is performed. That is, the rulers, headers, etc... are tiled with the contentView frame filling the remaining space. When contentInset is not equal to NSEdgeInsetsZero, the rulers, header, etc... are inset as specified. The contentView is is placed underneath these sibling views and is only inset by scroll view border and non-overlay scrollers.
*/
@property NSEdgeInsets contentInsets NS_AVAILABLE_MAC(10_10);

/* The distance the scrollers are inset from the edge of the scroll view. */
@property NSEdgeInsets scrollerInsets NS_AVAILABLE_MAC(10_10);


@end

/* This notification is sent at the beginning of a magnify gesture. The notification object is the scroll view performing the magnification.
*/
APPKIT_EXTERN NSString * const NSScrollViewWillStartLiveMagnifyNotification NS_AVAILABLE_MAC(10_8);

/* This notification is sent at the end of magnify gesture. The notification object is the scroll view view performing the magnification.
*/
APPKIT_EXTERN NSString * const NSScrollViewDidEndLiveMagnifyNotification NS_AVAILABLE_MAC(10_8);

/* This notification is sent on the main thread at the beginning of user initiated live scroll tracking (gesture scroll or scroller tracking, e.g. thumb dragging).
 The notification object is the scroll view performing the scroll.
*/
APPKIT_EXTERN NSString * const NSScrollViewWillStartLiveScrollNotification NS_AVAILABLE_MAC(10_9);

/* This notification is sent on the main thread after changing the clipview bounds origin due to a user initiated event.
 Not all user initiated scrolls are bracketed by a willStart/didEnd notification pair (legacy mice).
 The notification object is the scroll view performing the scroll.
*/
APPKIT_EXTERN NSString * const NSScrollViewDidLiveScrollNotification NS_AVAILABLE_MAC(10_9);

/* This notification is sent on the main thread at the end of live scroll tracking.
 The notification object is the scroll view performing the scroll.
*/
APPKIT_EXTERN NSString * const NSScrollViewDidEndLiveScrollNotification NS_AVAILABLE_MAC(10_9);


@interface NSScrollView(NSRulerSupport)

+ (void)setRulerViewClass:(nullable Class)rulerViewClass;
+ (Class)rulerViewClass;

@property BOOL rulersVisible;

@property BOOL hasHorizontalRuler;
@property BOOL hasVerticalRuler;

@property (nullable, strong) NSRulerView *horizontalRulerView;
@property (nullable, strong) NSRulerView *verticalRulerView;

@end

typedef NS_ENUM(NSInteger, NSScrollViewFindBarPosition) {
    NSScrollViewFindBarPositionAboveHorizontalRuler = 0,
    NSScrollViewFindBarPositionAboveContent = 1,
    NSScrollViewFindBarPositionBelowContent = 2
} NS_ENUM_AVAILABLE_MAC(10_7);

@interface NSScrollView(NSFindBarSupport)

@property NSScrollViewFindBarPosition findBarPosition NS_AVAILABLE_MAC(10_7);

@end

NS_ASSUME_NONNULL_END
