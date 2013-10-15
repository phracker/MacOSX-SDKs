/*
	NSScreen.h
	Application Kit
	Copyright (c) 1994-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSGraphics.h>

@class NSArray, NSColorSpace;

typedef struct NSScreenAuxiliary NSScreenAuxiliaryOpaque;

@interface NSScreen : NSObject {
/*All instance variables are private*/
@private
    NSRect _frame;          // cached value, possibly stale
    NSWindowDepth _depth;   // unused
    int _screenNumber;
    id _auxiliaryStorage;
}

+ (NSArray *)screens;		/* All screens; first one is "zero" screen */
+ (NSScreen *)mainScreen;	/* Screen with key window */
+ (NSScreen *)deepestScreen;

- (NSWindowDepth)depth;
- (NSRect)frame;
- (NSRect)visibleFrame;
- (NSDictionary *)deviceDescription;
- (NSColorSpace *)colorSpace AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (const NSWindowDepth *)supportedWindowDepths; /* 0 terminated */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Returns scale factor applied by default to windows created on this screen
*/
- (CGFloat)userSpaceScaleFactor;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

@end

/* Notifications */
APPKIT_EXTERN NSString * const NSScreenColorSpaceDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // the notification object is the screen whose profile has changed

