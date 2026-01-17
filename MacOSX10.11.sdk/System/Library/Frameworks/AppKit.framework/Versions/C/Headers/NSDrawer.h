/*
        NSDrawer.h
        Application Kit
        Copyright (c) 1999-2015, Apple Inc.
        All rights reserved.
*/

#import <CoreFoundation/CFDate.h>
#import <CoreFoundation/CFRunLoop.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSResponder.h>
#import <AppKit/NSWindow.h>

NS_ASSUME_NONNULL_BEGIN

@class NSLock;
@class NSView;
@class NSWindow;
@class NSNotification;
@protocol NSDrawerDelegate;

typedef NS_ENUM(NSUInteger, NSDrawerState) {
    NSDrawerClosedState			= 0,
    NSDrawerOpeningState 		= 1,
    NSDrawerOpenState 			= 2,
    NSDrawerClosingState 		= 3
};

@interface NSDrawer : NSResponder <NSAccessibilityElement, NSAccessibility>
{
    /*All instance variables are private*/
    NSDrawerState 	_drawerState;
    NSDrawerState	_drawerNextState;
    NSRectEdge 		_drawerEdge;
    NSRectEdge 		_drawerNextEdge;
    NSRectEdge 		_drawerPreferredEdge;
    float 		_drawerPercent;
    float 		_drawerPercentSaved;
    CGFloat		_drawerLeadingOffset;
    CGFloat		_drawerTrailingOffset;
    NSLock 		*_drawerLock;
    NSWindow		*_drawerWindow;
    NSWindow 		*_drawerParentWindow;
    NSWindow		*_drawerNextParentWindow;
    NSString		*_drawerSaveName;
    CFAbsoluteTime 	_drawerStartTime;
    CFTimeInterval 	_drawerTotalTime;
    CFRunLoopRef 	_drawerLoop;
    __strong CFRunLoopTimerRef 	_drawerTimer;
    id 			_drawerDelegate;
    unsigned int	_drawerFlags;
    __strong CFRunLoopObserverRef _drawerObserver;
}

- (instancetype)initWithContentSize:(NSSize)contentSize preferredEdge:(NSRectEdge)edge;

@property (nullable, assign) NSWindow *parentWindow;
@property (nullable, strong) NSView *contentView;
@property NSRectEdge preferredEdge;
@property (nullable, assign) id<NSDrawerDelegate> delegate;

- (void)open;
- (void)openOnEdge:(NSRectEdge)edge;
- (void)close;

- (void)open:(nullable id)sender;
- (void)close:(nullable id)sender;
- (void)toggle:(nullable id)sender;

@property (readonly) NSInteger state;
@property (readonly) NSRectEdge edge;

@property NSSize contentSize;
@property NSSize minContentSize;
@property NSSize maxContentSize;

@property CGFloat leadingOffset;
@property CGFloat trailingOffset;

@end

@interface NSWindow(Drawers)

@property (nullable, readonly, copy) NSArray<NSDrawer *> *drawers;

@end

@protocol NSDrawerDelegate <NSObject>
@optional
- (BOOL)drawerShouldOpen:(NSDrawer *)sender;
- (BOOL)drawerShouldClose:(NSDrawer *)sender;
- (NSSize)drawerWillResizeContents:(NSDrawer *)sender toSize:(NSSize)contentSize;

/* Notifications */
- (void)drawerWillOpen:(NSNotification *)notification;
- (void)drawerDidOpen:(NSNotification *)notification;
- (void)drawerWillClose:(NSNotification *)notification;
- (void)drawerDidClose:(NSNotification *)notification;

@end

/* Notifications */
APPKIT_EXTERN NSString * NSDrawerWillOpenNotification;
APPKIT_EXTERN NSString * NSDrawerDidOpenNotification;
APPKIT_EXTERN NSString * NSDrawerWillCloseNotification;
APPKIT_EXTERN NSString * NSDrawerDidCloseNotification;

NS_ASSUME_NONNULL_END

/* Note that the size of a drawer is determined partly by its content, partly by
the size of its parent window.  The size in the direction of the drawer's motion
is determined by the drawer's content size, and may be manually changed by the
user within the limits determined by the min and max content sizes (programmatic
changes are not so limited.)  The size in the transverse direction is determined
by the size of the parent window, combined with the drawer's leading and trailing
offsets.  For finer control over the size of the drawer in the transverse direction,
listen for the parent window's NSWindowDidResizeNotification and then reset the
leading and/or trailing offsets accordingly.  The one overriding restriction is
that a drawer can never be larger than its parent, and the sizes of both drawer
and parent are constrained by this. */
