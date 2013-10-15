/*
	NSScrollView.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/
#import <Foundation/NSDate.h>
#import <AppKit/NSView.h>

@class NSColor, NSClipView, NSRulerView, NSScroller;

typedef struct __SFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        vScrollerRequired:1;
    unsigned int        hScrollerRequired:1;
    unsigned int        vScrollerStatus:1;
    unsigned int        hScrollerStatus:1;
    unsigned int        noDynamicScrolling:1;
    NSBorderType        borderType:2;
    unsigned int        oldRulerInstalled:1;
    unsigned int        showRulers:1;
    unsigned int        hasHorizontalRuler:1;
    unsigned int        hasVerticalRuler:1;
    unsigned int        needsTile:1;
    unsigned int	doesNotDrawBackground:1;
    unsigned int	skipRemoveSuperviewCheck:1;
    unsigned int	focusRingNeedsRedisplay:1;
    unsigned int	hasCustomLineBorderColor:1;
    unsigned int	autohidesScrollers:1;
    unsigned int	autoforwardsScrollWheelEvents:1;
    unsigned int        RESERVED:14;
#else
    unsigned int        RESERVED:14;
    unsigned int	autoforwardsScrollWheelEvents:1;
    unsigned int	autohidesScrollers:1;
    unsigned int	hasCustomLineBorderColor:1;
    unsigned int	focusRingNeedsRedisplay:1;
    unsigned int	skipRemoveSuperviewCheck:1;
    unsigned int	doesNotDrawBackground:1;
    unsigned int        needsTile:1;
    unsigned int        hasVerticalRuler:1;
    unsigned int        hasHorizontalRuler:1;
    unsigned int        showRulers:1;
    unsigned int        oldRulerInstalled:1;
    NSBorderType        borderType:2;
    unsigned int        noDynamicScrolling:1;
    unsigned int        hScrollerStatus:1;
    unsigned int        vScrollerStatus:1;
    unsigned int        hScrollerRequired:1;
    unsigned int        vScrollerRequired:1;
#endif
} _SFlags;

@interface NSScrollView : NSView
{
    /*All instance variables are private*/
    NSScroller *_vScroller;
    NSScroller *_hScroller;
    NSClipView *_contentView;
    NSClipView *_headerClipView;
    NSView *    _cornerView;
    id		_ruler;
    _SFlags     _sFlags;
    void *      _extraIvars;
    
    // new rulers
    NSRulerView *_horizontalRuler;
    NSRulerView *_verticalRuler;
}

+ (NSSize)frameSizeForContentSize:(NSSize)cSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;

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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (BOOL)autohidesScrollers;
- (void)setAutohidesScrollers:(BOOL)flag;
#endif
- (void)setHorizontalLineScroll:(float)value;
- (void)setVerticalLineScroll:(float)value;
- (void)setLineScroll:(float)value;
- (float)horizontalLineScroll;
- (float)verticalLineScroll;
- (float)lineScroll;
- (void)setHorizontalPageScroll:(float)value;
- (void)setVerticalPageScroll:(float)value;
- (void)setPageScroll:(float)value;
- (float)horizontalPageScroll;
- (float)verticalPageScroll;
- (float)pageScroll;
- (void)setScrollsDynamically:(BOOL)flag;
- (BOOL)scrollsDynamically;
- (void)tile;
- (void)reflectScrolledClipView:(NSClipView *)cView;
- (void)scrollWheel:(NSEvent *)theEvent;
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
