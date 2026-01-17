/*
	NSCachedImageRep.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/NSGraphics.h>

@class NSWindow;

// this entire class is deprecated.  Please see the 10.6 AppKit release notes for more information.
NS_CLASS_DEPRECATED_MAC(10_0, 10_6)
@interface NSCachedImageRep : NSImageRep {
    /*All instance variables are private*/
    NSPoint _origin;
    NSWindow *_window;
    __strong void *_cache;
}

/* References the specified rect within the window; the window is retained */
- (id)initWithWindow:(NSWindow *)win rect:(NSRect)rect NS_DEPRECATED_MAC(10_0, 10_6);

/* Creates a location in some window. Will be freed when rep is freed */
- (id)initWithSize:(NSSize)size depth:(NSWindowDepth)depth separate:(BOOL)flag alpha:(BOOL)alpha NS_DEPRECATED_MAC(10_0, 10_6);

- (NSWindow *)window NS_DEPRECATED_MAC(10_0, 10_6);
- (NSRect)rect NS_DEPRECATED_MAC(10_0, 10_6);

@end
