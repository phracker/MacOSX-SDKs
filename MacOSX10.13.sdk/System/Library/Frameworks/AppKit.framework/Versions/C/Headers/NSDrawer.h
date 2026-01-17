/*
    NSDrawer.h
    Application Kit
    Copyright (c) 1999-2017, Apple Inc.
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
    NSDrawerClosedState NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController") = 0,
    NSDrawerOpeningState NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController") = 1,
    NSDrawerOpenState NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController") = 2,
    NSDrawerClosingState NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController") = 3
};

NS_CLASS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController")
@interface NSDrawer : NSResponder <NSAccessibilityElement, NSAccessibility>
{
    /* All instance variables are private */
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
    CFRunLoopTimerRef 	_drawerTimer;
    id 			_drawerDelegate;
    unsigned int	_drawerFlags;
    CFRunLoopObserverRef _drawerObserver;
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

@interface NSWindow(NSDrawers)

@property (nullable, readonly, copy) NSArray<NSDrawer *> *drawers NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");

@end

@protocol NSDrawerDelegate <NSObject>
@optional
- (BOOL)drawerShouldOpen:(NSDrawer *)sender NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
- (BOOL)drawerShouldClose:(NSDrawer *)sender NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
- (NSSize)drawerWillResizeContents:(NSDrawer *)sender toSize:(NSSize)contentSize NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");

- (void)drawerWillOpen:(NSNotification *)notification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
- (void)drawerDidOpen:(NSNotification *)notification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
- (void)drawerWillClose:(NSNotification *)notification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
- (void)drawerDidClose:(NSNotification *)notification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");

@end

APPKIT_EXTERN NSNotificationName NSDrawerWillOpenNotification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
APPKIT_EXTERN NSNotificationName NSDrawerDidOpenNotification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
APPKIT_EXTERN NSNotificationName NSDrawerWillCloseNotification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");
APPKIT_EXTERN NSNotificationName NSDrawerDidCloseNotification NS_DEPRECATED_MAC(10_0, 10_13, "Drawers are deprecated; consider using NSSplitViewController");

NS_ASSUME_NONNULL_END

