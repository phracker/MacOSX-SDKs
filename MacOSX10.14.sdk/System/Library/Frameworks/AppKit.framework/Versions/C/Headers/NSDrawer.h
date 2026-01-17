/*
    NSDrawer.h
    Application Kit
    Copyright (c) 1999-2018, Apple Inc.
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
    NSDrawerState 	_drawerState APPKIT_IVAR;
    NSDrawerState	_drawerNextState APPKIT_IVAR;
    NSRectEdge 		_drawerEdge APPKIT_IVAR;
    NSRectEdge 		_drawerNextEdge APPKIT_IVAR;
    NSRectEdge 		_drawerPreferredEdge APPKIT_IVAR;
    float 		_drawerPercent APPKIT_IVAR;
    float 		_drawerPercentSaved APPKIT_IVAR;
    CGFloat		_drawerLeadingOffset APPKIT_IVAR;
    CGFloat		_drawerTrailingOffset APPKIT_IVAR;
    NSLock 		*_drawerLock APPKIT_IVAR;
    NSWindow		*_drawerWindow APPKIT_IVAR;
    NSWindow 		*_drawerParentWindow APPKIT_IVAR;
    NSWindow		*_drawerNextParentWindow APPKIT_IVAR;
    NSString		*_drawerSaveName APPKIT_IVAR;
    CFAbsoluteTime 	_drawerStartTime APPKIT_IVAR;
    CFTimeInterval 	_drawerTotalTime APPKIT_IVAR;
    CFRunLoopRef 	_drawerLoop APPKIT_IVAR;
    CFRunLoopTimerRef 	_drawerTimer APPKIT_IVAR;
    id 			_drawerDelegate APPKIT_IVAR;
    unsigned int	_drawerFlags APPKIT_IVAR;
    CFRunLoopObserverRef _drawerObserver APPKIT_IVAR;
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

