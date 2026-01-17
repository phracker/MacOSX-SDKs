/*
	NSBox.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>

@class NSFont;

enum {
    NSNoTitle				= 0,
    NSAboveTop				= 1,
    NSAtTop				= 2,
    NSBelowTop				= 3,
    NSAboveBottom			= 4,
    NSAtBottom				= 5,
    NSBelowBottom			= 6
};
typedef NSUInteger NSTitlePosition;

enum {
    NSBoxPrimary	= 0,	// group subviews with a standard look. default
    NSBoxSecondary	= 1,    // same as primary since 10.3
    NSBoxSeparator	= 2,    // vertical or horizontal separtor line.  Not used with subviews.
    NSBoxOldStyle	= 3,    // 10.2 and earlier style boxes
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
    NSBoxCustom		= 4     // draw based entirely on user parameters, not human interface guidelines
#endif
};
typedef NSUInteger NSBoxType;

@interface NSBox : NSView
{
    /*All instance variables are private*/
    id                  _titleCell;
    id                  _contentView;
    NSSize              _offsets;
    NSRect              _borderRect;
    NSRect              _titleRect;
    struct __bFlags {
	NSBorderType	borderType:2;
	NSTitlePosition	titlePosition:3;
	unsigned int	backgroundTransparent:1;
        unsigned int	reserved:2;
        unsigned int	needsTile:1;
        unsigned int	transparent:1;
        unsigned int	colorAltInterpretation:1;
        unsigned int	boxType:3;
        unsigned int	_RESERVED:18;
    } _bFlags;
    id			_unused;
}

- (NSBorderType)borderType;
- (NSTitlePosition)titlePosition;
- (void)setBorderType:(NSBorderType)aType;
- (void)setBoxType:(NSBoxType)boxType;
- (NSBoxType)boxType;
- (void)setTitlePosition:(NSTitlePosition)aPosition;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSRect)borderRect;
- (NSRect)titleRect;
- (id)titleCell;
- (void)sizeToFit;
- (NSSize)contentViewMargins;
- (void)setContentViewMargins:(NSSize)offsetSize;
- (void)setFrameFromContentFrame:(NSRect)contentFrame;
- (id)contentView;
- (void)setContentView:(NSView *)aView;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// Transparent boxes do not draw anything.  Subview drawing is unaffected.  The 'transparent' property corresponds to the binding 'NSTransparentBinding'.
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
#endif

@end

@interface NSBox(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@interface NSBox (NSCustomBoxTypeProperties)
/* These properties only apply to boxes with boxType NSBoxCustom.
 */

- (CGFloat)borderWidth;
- (void)setBorderWidth:(CGFloat)borderWidth;	// Only meaningful for boxes configured with NSBoxCustom

- (CGFloat)cornerRadius;
- (void)setCornerRadius:(CGFloat)cornerRadius;	// Only meaningful for boxes configured with NSBoxCustom

- (NSColor *)borderColor;
- (void)setBorderColor:(NSColor *)borderColor;	// Only meaningful for boxes configured with NSBoxCustom

- (NSColor *)fillColor;
- (void)setFillColor:(NSColor *)fillColor;	// Only meaningful for boxes configured with NSBoxCustom

@end
#endif