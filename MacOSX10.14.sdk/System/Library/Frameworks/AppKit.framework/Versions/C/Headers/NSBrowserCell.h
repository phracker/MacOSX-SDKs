/*
	NSBrowserCell.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSImage;

@interface NSBrowserCell : NSCell

- (instancetype)initTextCell:(NSString *)string NS_DESIGNATED_INITIALIZER;
- (instancetype)initImageCell:(nullable NSImage *)image NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (class, readonly, nullable, strong) NSImage *branchImage;
@property (class, readonly, nullable, strong) NSImage *highlightedBranchImage;

- (nullable NSColor *)highlightColorInView:(NSView *)controlView;

@property (getter=isLeaf) BOOL leaf;
@property (getter=isLoaded) BOOL loaded;
- (void)reset;
- (void)set;
@property (nullable, strong) NSImage *image;
@property (nullable, strong) NSImage *alternateImage;

@end

NS_ASSUME_NONNULL_END
