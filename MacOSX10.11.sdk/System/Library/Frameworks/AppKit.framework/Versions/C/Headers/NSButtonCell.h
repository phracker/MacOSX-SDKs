/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAttributedString, NSFont, NSImage, NSSound;

typedef NS_ENUM(NSUInteger, NSButtonType) {
    NSMomentaryLightButton		= 0,	// was NSMomentaryPushButton
    NSPushOnPushOffButton		= 1,
    NSToggleButton			= 2,
    NSSwitchButton			= 3,
    NSRadioButton			= 4,
    NSMomentaryChangeButton		= 5,
    NSOnOffButton			= 6,
    NSMomentaryPushInButton		= 7,	// was NSMomentaryLight
    NSAcceleratorButton NS_ENUM_AVAILABLE_MAC(10_10_3)			= 8,
    NSMultiLevelAcceleratorButton NS_ENUM_AVAILABLE_MAC(10_10_3)	= 9,
    
    /* These constants were accidentally reversed so that NSMomentaryPushButton lit and
       NSMomentaryLight pushed. These names are now deprecated */
    NSMomentaryPushButton NS_ENUM_DEPRECATED_MAC(10_0, 10_9)    = 0, // NSMomentaryLightButton should be used instead
    NSMomentaryLight NS_ENUM_DEPRECATED_MAC(10_0, 10_9)         = 7 // NSMomentaryPushInButton should be used instead
};

typedef NS_ENUM(NSUInteger, NSBezelStyle) {
    NSRoundedBezelStyle          = 1,
    NSRegularSquareBezelStyle    = 2,
    NSThickSquareBezelStyle      = 3,
    NSThickerSquareBezelStyle    = 4,
    NSDisclosureBezelStyle       = 5,
    NSShadowlessSquareBezelStyle = 6,
    NSCircularBezelStyle         = 7,
    NSTexturedSquareBezelStyle   = 8,
    NSHelpButtonBezelStyle       = 9,
    NSSmallSquareBezelStyle       = 10,
    NSTexturedRoundedBezelStyle   = 11,
    NSRoundRectBezelStyle         = 12,
    NSRecessedBezelStyle          = 13,
    NSRoundedDisclosureBezelStyle = 14,
    // The inline bezel style contains a solid round-rect border background. It can be used to create an "unread" indicator in an outline view, or another inline button in a tableview, such as a stop progress button in a download panel. Use text for an unread indicator, and a template image for other buttons.
    NSInlineBezelStyle NS_ENUM_AVAILABLE_MAC(10_7) = 15,
    
    NSSmallIconButtonBezelStyle NS_ENUM_DEPRECATED_MAC(10_0, 10_0) = 2 // This bezel style is obsolete and should not be used.
};

typedef struct __BCFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        pushIn:1;
    unsigned int        changeContents:1;
    unsigned int        changeBackground:1;
    unsigned int        changeGray:1;
    unsigned int        lightByContents:1;
    unsigned int        lightByBackground:1;
    unsigned int        lightByGray:1;
    unsigned int        drawing:1;
    unsigned int        bordered:1;
    unsigned int        imageOverlaps:1;
    unsigned int        horizontal:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        imageAndText:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        inIntermediateDisclosure:1;
    unsigned int        transparent:1;
    unsigned int        inset:2;
    unsigned int        doesNotDimImage:1;
    unsigned int        suppressAXValueChangeNote:1;
    unsigned int        isDrawingDisclosure:1;
    unsigned int        hasTitleTextField:1;
    unsigned int        useButtonImageSource:1;
    unsigned int        isDrawingFocus:1;
    unsigned int        allowTitleTightening:1;
    unsigned int        __reserved:6;
#else
    unsigned int        __reserved:6;
    unsigned int        allowTitleTightening:1;
    unsigned int        isDrawingFocus:1;
    unsigned int        useButtonImageSource:1;
    unsigned int        hasTitleTextField:1;
    unsigned int        isDrawingDisclosure:1;
    unsigned int        suppressAXValueChangeNote:1;
    unsigned int        doesNotDimImage:1;
    unsigned int        inset:2;
    unsigned int        transparent:1;
    unsigned int        inIntermediateDisclosure:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        imageAndText:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        horizontal:1;
    unsigned int        imageOverlaps:1;
    unsigned int        bordered:1;
    unsigned int        drawing:1;
    unsigned int        lightByGray:1;
    unsigned int        lightByBackground:1;
    unsigned int        lightByContents:1;
    unsigned int        changeGray:1;
    unsigned int        changeBackground:1;
    unsigned int        changeContents:1;
    unsigned int        pushIn:1;
#endif
} _BCFlags;

typedef struct __BCFlags2 {
#ifdef __BIG_ENDIAN__
    unsigned int	keyEquivalentModifierMask:24;
    unsigned int	imageScaling:2;
    unsigned int	bezelStyle2:1;
    unsigned int	mouseInside:1;
    unsigned int	showsBorderOnlyWhileMouseInside:1;
    unsigned int	bezelStyle:3;
#else
    unsigned int	bezelStyle:3;
    unsigned int	showsBorderOnlyWhileMouseInside:1;
    unsigned int	mouseInside:1;
    unsigned int	bezelStyle2:1;
    unsigned int	imageScaling:2;
    unsigned int	keyEquivalentModifierMask:24;
#endif
} _BCFlags2;

@interface NSButtonCell : NSActionCell
{
    /*All instance variables are private*/
    NSString	       *_altContents;
    id			_sound;
    NSString	       *_keyEquivalent;
    _BCFlags2		_bcFlags2;
    unsigned short	_periodicDelay;
    unsigned short	_periodicInterval;
    _BCFlags            _bcFlags;
    NSImage            *_normalImage;
    id                  _alternateImageOrKeyEquivalentFont;
}


@property (null_resettable, copy) NSString *title;
@property (copy) NSString *alternateTitle;

@property (nullable, strong) NSImage *alternateImage;
@property NSCellImagePosition imagePosition;
@property NSImageScaling imageScaling NS_AVAILABLE_MAC(10_5);

@property NSCellStyleMask highlightsBy;
@property NSCellStyleMask showsStateBy;
- (void)setButtonType:(NSButtonType)aType;
@property (getter=isOpaque, readonly) BOOL opaque;
@property (getter=isTransparent) BOOL transparent;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
@property (copy) NSString *keyEquivalent;
@property NSUInteger keyEquivalentModifierMask;
@property (nullable, strong) NSFont *keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(CGFloat)fontSize;
- (void)performClick:(nullable id)sender; // Significant NSCell override, actually clicks itself.

- (void)drawImage:(NSImage*)image withFrame:(NSRect)frame inView:(NSView*)controlView;
- (NSRect)drawTitle:(NSAttributedString*)title withFrame:(NSRect)frame inView:(NSView*)controlView;
- (void)drawBezelWithFrame:(NSRect)frame inView:(NSView*)controlView;

@end

// NSGradientType :
//
// A concave gradient is darkest in the top left corner, 
// a convex gradient is darkest in the bottom right corner.
//
// Weak versus strong is how much contrast exists between
// the colors used in opposite corners
typedef NS_ENUM(NSUInteger, NSGradientType) {
    NSGradientNone          = 0,
    NSGradientConcaveWeak   = 1,
    NSGradientConcaveStrong = 2,
    NSGradientConvexWeak    = 3,
    NSGradientConvexStrong  = 4
};

@interface NSButtonCell(NSButtonCellExtensions)

// NOTE: gradientType is not used
@property NSGradientType gradientType;

// When disabled, the image and text of an NSButtonCell are normally dimmed with gray.
// Radio buttons and switches use (imageDimsWhenDisabled == NO) so only their text is dimmed.
@property BOOL imageDimsWhenDisabled;

@property BOOL showsBorderOnlyWhileMouseInside;

- (void)mouseEntered:(NSEvent*)event;
- (void)mouseExited:(NSEvent*)event;

@property (nullable, copy) NSColor *backgroundColor;

@end

@interface NSButtonCell(NSButtonCellAttributedStringMethods)
@property (copy) NSAttributedString *attributedTitle;
@property (copy) NSAttributedString *attributedAlternateTitle;
@end

@interface NSButtonCell(NSButtonCellBezelStyles)

@property NSBezelStyle bezelStyle;

@end

@interface NSButtonCell (NSButtonCellSoundExtensions)
@property (nullable, strong) NSSound *sound;
@end

/* In 10.8 and higher, all the *Mnemonic* methods are deprecated. On MacOS they have typically not been used.
 */
@interface NSButtonCell(NSKeyboardUI)

/* On 10.8, these two methods still will call setTitle: (or setAlternateTitle:) with the ampersand stripped from stringWithAmpersand, but does nothing else. Use setTitle directly.
 */
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);
- (void)setAlternateTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

/* This method no longer does anything and should not be called.
 */
- (void)setAlternateMnemonicLocation:(NSUInteger)location NS_DEPRECATED_MAC(10_0, 10_8);

/* On 10.8, alternateMnemonicLocation now always returns NSNotFound.
 */
- (NSUInteger)alternateMnemonicLocation NS_DEPRECATED_MAC(10_0, 10_8);

- (null_unspecified NSString *)alternateMnemonic NS_DEPRECATED_MAC(10_0, 10_8);
@end

NS_ASSUME_NONNULL_END

