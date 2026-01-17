/*
	NSCachedImageRep.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/NSGraphics.h>

@class NSWindow;

@interface NSCachedImageRep : NSImageRep {
    /*All instance variables are private*/
    NSPoint _origin;
    NSWindow *_window;
    void *_cache;
}

/* References the specified rect within the window; the window is retained */
- (id)initWithWindow:(NSWindow *)win rect:(NSRect)rect;

/* Creates a location in some window. Will be freed when rep is freed */
- (id)initWithSize:(NSSize)size depth:(NSWindowDepth)depth separate:(BOOL)flag alpha:(BOOL)alpha;

- (NSWindow *)window;
- (NSRect)rect;

@end
