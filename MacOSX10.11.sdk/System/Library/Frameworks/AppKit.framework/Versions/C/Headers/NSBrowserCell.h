/*
	NSBrowserCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSImage;

@interface NSBrowserCell : NSCell

+ (nullable NSImage *)branchImage;
+ (nullable NSImage *)highlightedBranchImage;

- (nullable NSColor *)highlightColorInView:(NSView *)controlView;

@property (getter=isLeaf) BOOL leaf;
@property (getter=isLoaded) BOOL loaded;
- (void)reset;
- (void)set;
@property (nullable, strong) NSImage *image;
@property (nullable, strong) NSImage *alternateImage;

@end

NS_ASSUME_NONNULL_END
