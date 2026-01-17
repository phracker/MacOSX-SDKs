/*
    NSBox.h
    Application Kit
    Copyright (c) 1994-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFont;

typedef NS_ENUM(NSUInteger, NSTitlePosition) {
    NSNoTitle				= 0,
    NSAboveTop				= 1,
    NSAtTop				= 2,
    NSBelowTop				= 3,
    NSAboveBottom			= 4,
    NSAtBottom				= 5,
    NSBelowBottom			= 6
};

typedef NS_ENUM(NSUInteger, NSBoxType) {
    NSBoxPrimary	= 0,	// group subviews with a standard look. default
    NSBoxSecondary	= 1,    // same as primary since 10.3
    NSBoxSeparator	= 2,    // vertical or horizontal separtor line.  Not used with subviews.
    NSBoxOldStyle	= 3,    // 10.2 and earlier style boxes
    NSBoxCustom	NS_ENUM_AVAILABLE_MAC(10_5)	= 4     // draw based entirely on user parameters, not human interface guidelines
};

@interface NSBox : NSView
{
    /* All instance variables are private */
    id                  _titleCell;
    id                  _contentView;
    NSSize              _offsets;
    NSRect              _borderRect;
    NSRect              _titleRect;
    struct __bFlags {
        NSBorderType borderType:2;
        NSTitlePosition titlePosition:3;
        unsigned int backgroundTransparent:1;
        unsigned int orientation:2;
        unsigned int needsTile:1;
        unsigned int transparent:1;
        unsigned int colorAltInterpretation:1;
        unsigned int boxType:3;
        unsigned int useSuperAddSubview:1;
        unsigned int _RESERVED:17;
    } _bFlags;
    id _unused;
}

@property NSBorderType borderType;
@property NSTitlePosition titlePosition;
@property NSBoxType boxType;
@property (copy) NSString *title;
@property (strong) NSFont *titleFont;
@property (readonly) NSRect borderRect;
@property (readonly) NSRect titleRect;
@property (readonly, strong) id titleCell;
- (void)sizeToFit;
@property NSSize contentViewMargins;
- (void)setFrameFromContentFrame:(NSRect)contentFrame;

/* Get and set the content view for the box. Note that subviews added to the NSBox will be really added as subviews of the contentView.
 */
@property (nullable, assign) __kindof NSView *contentView;

/* Transparent boxes do not draw anything.  Subview drawing is unaffected.  The 'transparent' property corresponds to the binding 'NSTransparentBinding'.
 */
@property (getter=isTransparent) BOOL transparent NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the border width of the box. The default value is 1.0.
 */
@property CGFloat borderWidth NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the corner radius of the box. The default value is 0.0 (no corner radius).
 */
@property CGFloat cornerRadius NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the border color the box. The default value is black with some alpha, and may vary release-to-release.
 */
@property (copy) NSColor *borderColor NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the fill (background) color the box. The default value is NSColor.clearColor.
 */
@property (copy) NSColor *fillColor NS_AVAILABLE_MAC(10_5);

@end

@interface NSBox(NSDeprecated)

/* Mnemonics are deprecated in 10.8. Historically they have not done anything. For compatability, this method still calls setTitle: with the ampersand stripped from it.
 */
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end

NS_ASSUME_NONNULL_END

