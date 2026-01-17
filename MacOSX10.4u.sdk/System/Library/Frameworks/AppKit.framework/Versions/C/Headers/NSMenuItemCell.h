/*
        NSMenuItemCell.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSButtonCell.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSMenuItem.h>

@class NSMenuView;

@interface NSMenuItemCell : NSButtonCell {
    /*All instance variables are private*/
    @private
    id _extraData;
    NSSize _stateImageSize;
    NSSize _imageSize;
    NSSize _titleSize;
    NSSize _keyEquivalentSize;
    NSSize _size;
    struct __micFlags {
        unsigned int needsSizing:1;
        unsigned int highlighted:1;
        unsigned int needsDisplay:1;
        unsigned int keyEquivGlyphWidth:16;
        unsigned int RESERVED:13;
    } _micFlags;
}

- (void)setMenuItem:(NSMenuItem *)item;
- (NSMenuItem *)menuItem;
- (void)setMenuView:(NSMenuView *)menuView;
- (NSMenuView *)menuView;

- (void)setHighlighted:(BOOL)flag;
- (BOOL)isHighlighted;

- (void)setNeedsSizing:(BOOL)flag;
- (BOOL)needsSizing;
- (void)calcSize;

- (void)setNeedsDisplay:(BOOL)flag;
- (BOOL)needsDisplay;

- (float)stateImageWidth;
- (float)imageWidth;
- (float)titleWidth;
- (float)keyEquivalentWidth;

- (NSRect)stateImageRectForBounds:(NSRect)cellFrame;
- (NSRect)imageRectForBounds:(NSRect)cellFrame;
- (NSRect)titleRectForBounds:(NSRect)cellFrame;
- (NSRect)keyEquivalentRectForBounds:(NSRect)cellFrame;

- (void)drawSeparatorItemWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawStateImageWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawImageWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawTitleWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawKeyEquivalentWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawBorderAndBackgroundWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;

- (int)tag;

@end
