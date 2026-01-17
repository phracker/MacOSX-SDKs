/*
    NSBox.h
    Application Kit
    Copyright (c) 1994-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFont;

typedef NS_ENUM(NSUInteger, NSTitlePosition) {
    NSNoTitle     = 0,
    NSAboveTop    = 1,
    NSAtTop       = 2,
    NSBelowTop    = 3,
    NSAboveBottom = 4,
    NSAtBottom    = 5,
    NSBelowBottom = 6,
};

typedef NS_ENUM(NSUInteger, NSBoxType) {
    /* Group subviews with a standard look. This is the default style. */
    NSBoxPrimary = 0,

    /* Vertical or horizontal separtor line.  Not used with subviews. */
    NSBoxSeparator = 2,

    /* Custom boxes draw based entirely on user parameters; see the fillColor, borderColor, borderWidth, and cornerRadius properties for more information. */
    NSBoxCustom NS_ENUM_AVAILABLE_MAC(10_5) = 4,
};

@interface NSBox : NSView {
    /* All instance variables are private */
    id                  _titleCell APPKIT_IVAR;
    id                  _contentView APPKIT_IVAR;
    NSSize              _offsets APPKIT_IVAR;
    NSRect              _borderRect APPKIT_IVAR;
    NSRect              _titleRect APPKIT_IVAR;
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
    } _bFlags APPKIT_IVAR;
    id _unused APPKIT_IVAR;
}

@property NSBoxType boxType;
@property NSTitlePosition titlePosition;
@property (copy) NSString *title;
@property (strong) NSFont *titleFont;
@property (readonly) NSRect borderRect;
@property (readonly) NSRect titleRect;
@property (readonly, strong) id titleCell;
@property NSSize contentViewMargins;
- (void)sizeToFit;
- (void)setFrameFromContentFrame:(NSRect)contentFrame;

/* Get and set the content view for the box. Note that subviews added to the NSBox will be really added as subviews of the contentView. */
@property (nullable, strong) __kindof NSView *contentView;

/* Transparent boxes do not draw anything.  Subview drawing is unaffected.  The 'transparent' property corresponds to the binding 'NSTransparentBinding'. */
@property (getter=isTransparent) BOOL transparent NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the border width of the box. The default value is 1.0. */
@property CGFloat borderWidth NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the corner radius of the box. The default value is 0.0 (no corner radius). */
@property CGFloat cornerRadius NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the border color the box. The default value is black with some alpha, and may vary release-to-release. */
@property (copy) NSColor *borderColor NS_AVAILABLE_MAC(10_5);

/* For boxType == NSBoxCustom: Get and set the fill (background) color the box. The default value is NSColor.clearColor. */
@property (copy) NSColor *fillColor NS_AVAILABLE_MAC(10_5);

@end

/* Deprecated Interfaces */

@interface NSBox (NSDeprecated)

@property NSBorderType borderType NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "borderType is only applicable to NSBoxOldStyle, which is deprecated. To replace a borderType of NSNoBorder, use the `transparent` property.");

/* Mnemonics are deprecated in 10.8. Historically they have not done anything. For compatability, this method still calls setTitle: with the ampersand stripped from it. */
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);
@end

/* The Secondary box type has been identical to Primary since Mac OS X 10.3. Use NSBoxPrimary instead. */
static const NSBoxType NSBoxSecondary NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBoxPrimary", 10_0, API_TO_BE_DEPRECATED) = (NSBoxType)1;

/* Draws a border in the style of Mac OS X 10.2 and earlier. This style is not recommended. */
static const NSBoxType NSBoxOldStyle NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "NSBoxOldStyle is discouraged in modern application design. It should be replaced with either NSBoxPrimary or NSBoxCustom.") = (NSBoxType)3;

NS_ASSUME_NONNULL_END
