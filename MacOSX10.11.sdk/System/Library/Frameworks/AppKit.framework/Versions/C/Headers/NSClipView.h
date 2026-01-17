/*
	NSClipView.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>

#ifndef NSEDGEINSETS_DEFINED
#import <AppKit/NSLayoutConstraint.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSNotification;

@interface NSClipView : NSView
{
    /*All instance variables are private*/
    NSColor             *_backgroundColor;
    NSView              *_docView;
    NSRect              _docRect;
    NSRect              _oldDocFrame;
    NSCursor            *_cursor;
    id                  _scrollAnimationHelper;
    struct __cvFlags {
	unsigned int        __unused:1;
	unsigned int        onlyUncovered:1;
	unsigned int        reflectScroll:1;
	unsigned int        usedByCell:1;
	unsigned int	    scrollClipTo:1;
	unsigned int	    noCopyOnScroll:1;
        unsigned int        drawsBackground:1;
        unsigned int        scrollInProgress:1;
        unsigned int        skipRemoveSuperviewCheck:1;
        unsigned int        animateCurrentScroll:1;
        unsigned int        canAnimateScrolls:1;
        unsigned int	    nextScrollRelativeToCurrentPosition:1;
        unsigned int        viewBoundsChangedOverridden:1;
        unsigned int        viewFrameChangedOverridden:1;
        unsigned int        documentViewAlignment:4;
        unsigned int        redrawnWhileScrolling:1;
        unsigned int        dontConstrainScroll:1;
        unsigned int        lastAtEdgesState:4;
        unsigned int        showOverlayScrollersForScrollStep:1;
        unsigned int        scrollerKnobFlashSpecifier:2;
        unsigned int        drawsContentShadow:1;
        unsigned int        dontConstrainBoundsChange:1;
        unsigned int        isScrollDueToUserAction:1;
        unsigned int        hasOverlappingViews:1;
        unsigned int        automaticallyCalculateContentSize:1;
    } _cvFlags;
}

@property (copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property (nullable, assign) id /* NSView * */ documentView;
@property (readonly) NSRect documentRect;
@property (nullable, strong) NSCursor *documentCursor;
@property (readonly) NSRect documentVisibleRect;
- (void)viewFrameChanged:(NSNotification *)notification;
- (void)viewBoundsChanged:(NSNotification *)notification;
@property BOOL copiesOnScroll;
- (BOOL)autoscroll:(NSEvent *)theEvent;
- (void)scrollToPoint:(NSPoint)newOrigin;

/* This is used to constrain the bounds of the clip view under magnification and scrolling. This also comes with the deprecation of -constrainScrollPoint:. The logic of an existing -constrainScrollPoint: can be moved to -constrainBoundsRect: by adjusting the proposedBound's origin (as opposed to 'newOrigin').
 
 To preserve compatibility, if a subclass overrides -constrainScrollPoint:, the default behavior of -constrainBoundsRect: will be to use that -constrainScrollPoint: to adjust the proposedBound's origin, and to not change the size.
 */
- (NSRect)constrainBoundsRect:(NSRect)proposedBounds NS_AVAILABLE_MAC(10_9);

/* The distance that the content view is inset from the enclosing scroll view.
   Note: animate with [self animator]
*/
@property NSEdgeInsets contentInsets NS_AVAILABLE_MAC(10_10);

/* When YES, and used as the contentView of an NSScrollView, the clip view will automatically account for other scroll view subviews such as rulers and headers. Defaults to YES.
*/
@property BOOL automaticallyAdjustsContentInsets NS_AVAILABLE_MAC(10_10);

@end

@interface NSClipView(NSDeprecated)
// -[NSClipView constrainScrollPoint:] will be formally deprecated in an upcoming release. -[NSClipView constrainBoundsRect:] should be used instead.
- (NSPoint)constrainScrollPoint:(NSPoint)newOrigin NS_DEPRECATED_MAC(10_0, 10_10, "Use -constrainBoundsRect: instead");
@end

@interface NSView(NSClipViewSuperview)
- (void)reflectScrolledClipView:(NSClipView *)aClipView;
- (void)scrollClipView:(NSClipView *)aClipView toPoint:(NSPoint)aPoint;
@end

NS_ASSUME_NONNULL_END
