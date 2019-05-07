/*
        NSMenuItemCell.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSButtonCell.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSMenuItem.h>

#if ! __LP64__
@class NSMenuView;
#endif

NS_ASSUME_NONNULL_BEGIN

@interface NSMenuItemCell : NSButtonCell {
    /*All instance variables are private*/
    @private
    id _extraData APPKIT_IVAR;
    NSSize _stateImageSize APPKIT_IVAR;
    NSSize _imageSize APPKIT_IVAR;
    NSSize _titleSize APPKIT_IVAR;
#if ! __LP64__
    NSSize _keyEquivalentSize APPKIT_IVAR;
#endif
    NSSize _size APPKIT_IVAR;
    struct __micFlags {
        unsigned int needsSizing:1;
        unsigned int reserved:1;
        unsigned int needsDisplay:1;
        unsigned int keyEquivGlyphWidth:16;
	unsigned int uniqueAgainstMain:1;
        unsigned int RESERVED:12;
    } _micFlags APPKIT_IVAR;
}

- (instancetype)initTextCell:(NSString *)string NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nullable, strong) NSMenuItem *menuItem;

#if ! __LP64__
- (void)setMenuView:(nullable NSMenuView *)menuView;
- (nullable NSMenuView *)menuView;
#endif

@property BOOL needsSizing;
- (void)calcSize;

@property BOOL needsDisplay;

@property (readonly) CGFloat stateImageWidth;
@property (readonly) CGFloat imageWidth;
@property (readonly) CGFloat titleWidth;
@property (readonly) CGFloat keyEquivalentWidth;

- (NSRect)stateImageRectForBounds:(NSRect)cellFrame;
- (NSRect)titleRectForBounds:(NSRect)cellFrame;
- (NSRect)keyEquivalentRectForBounds:(NSRect)cellFrame;

- (void)drawSeparatorItemWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawStateImageWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawImageWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawTitleWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawKeyEquivalentWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawBorderAndBackgroundWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;

@property NSInteger tag;

@end

NS_ASSUME_NONNULL_END
