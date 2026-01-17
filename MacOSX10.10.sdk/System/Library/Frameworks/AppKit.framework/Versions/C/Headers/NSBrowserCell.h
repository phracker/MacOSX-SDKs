/*
	NSBrowserCell.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSCell.h>

@class NSImage;

@interface NSBrowserCell : NSCell

+ (NSImage *)branchImage;
+ (NSImage *)highlightedBranchImage;

- (NSColor *)highlightColorInView:(NSView *)controlView;

@property (getter=isLeaf) BOOL leaf;
@property (getter=isLoaded) BOOL loaded;
- (void)reset;
- (void)set;
@property (strong) NSImage *image;
@property (strong) NSImage *alternateImage;

@end
