/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAttributedString, NSFont, NSImage, NSSound;

typedef NS_ENUM(NSUInteger, NSButtonType) {
    NSButtonTypeMomentaryLight    = 0,
    NSButtonTypePushOnPushOff     = 1,
    NSButtonTypeToggle            = 2,
    NSButtonTypeSwitch            = 3,
    NSButtonTypeRadio             = 4,
    NSButtonTypeMomentaryChange   = 5,
    NSButtonTypeOnOff             = 6,
    NSButtonTypeMomentaryPushIn   = 7,
    NSButtonTypeAccelerator NS_ENUM_AVAILABLE_MAC(10_10_3) = 8,
    NSButtonTypeMultiLevelAccelerator NS_ENUM_AVAILABLE_MAC(10_10_3) = 9,
};

typedef NS_ENUM(NSUInteger, NSBezelStyle) {
    NSBezelStyleRounded           = 1,
    NSBezelStyleRegularSquare     = 2,
    NSBezelStyleDisclosure        = 5,
    NSBezelStyleShadowlessSquare  = 6,
    NSBezelStyleCircular          = 7,
    NSBezelStyleTexturedSquare    = 8,
    NSBezelStyleHelpButton        = 9,
    NSBezelStyleSmallSquare       = 10,
    NSBezelStyleTexturedRounded   = 11,
    NSBezelStyleRoundRect         = 12,
    NSBezelStyleRecessed          = 13,
    NSBezelStyleRoundedDisclosure = 14,
    NSBezelStyleInline NS_ENUM_AVAILABLE_MAC(10_7) = 15,
};

typedef struct __BCFlags {
    unsigned int        __reserved:1;
    unsigned int        calculatingPreferredAppearance:1;
    unsigned int        alwaysRadioExclusive:1;
    unsigned int        leadingOrTrailing:1;
    unsigned int        shouldNotHighlightOnPerformClick:1;
    unsigned int        imageHugsTitle:1;
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
} _BCFlags;

typedef struct __BCFlags2 {
    unsigned int	bezelStyle:3;
    unsigned int	showsBorderOnlyWhileMouseInside:1;
    unsigned int	mouseInside:1;
    unsigned int	bezelStyle2:1;
    unsigned int	imageScaling:2;
    unsigned int	keyEquivalentModifierMask:24;
} _BCFlags2;

@interface NSButtonCell : NSActionCell {
    /*All instance variables are private*/
    NSString	       *_altContents APPKIT_IVAR;
    id			_sound APPKIT_IVAR;
    NSString	       *_keyEquivalent APPKIT_IVAR;
    _BCFlags2		_bcFlags2 APPKIT_IVAR;
    unsigned short	_periodicDelay APPKIT_IVAR;
    unsigned short	_periodicInterval APPKIT_IVAR;
    _BCFlags            _bcFlags APPKIT_IVAR;
    NSImage            *_normalImage APPKIT_IVAR;
    id                  _alternateImageOrKeyEquivalentFont APPKIT_IVAR;
}

- (instancetype)initTextCell:(NSString *)string NS_DESIGNATED_INITIALIZER;
- (instancetype)initImageCell:(nullable NSImage *)image NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (null_resettable, copy) NSString *title;
@property (copy) NSString *alternateTitle;

@property (nullable, strong) NSImage *alternateImage;
@property NSCellImagePosition imagePosition;
@property NSImageScaling imageScaling NS_AVAILABLE_MAC(10_5);

@property NSCellStyleMask highlightsBy;
@property NSCellStyleMask showsStateBy;
- (void)setButtonType:(NSButtonType)type;
@property (getter=isOpaque, readonly) BOOL opaque;
@property (getter=isTransparent) BOOL transparent;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
@property (copy) NSString *keyEquivalent;
@property NSEventModifierFlags keyEquivalentModifierMask;
@property (nullable, strong) NSFont *keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(CGFloat)fontSize;
- (void)performClick:(nullable id)sender; // Significant NSCell override, actually clicks itself.

- (void)drawImage:(NSImage*)image withFrame:(NSRect)frame inView:(NSView*)controlView;
- (NSRect)drawTitle:(NSAttributedString*)title withFrame:(NSRect)frame inView:(NSView*)controlView;
- (void)drawBezelWithFrame:(NSRect)frame inView:(NSView*)controlView;

@end

@interface NSButtonCell(NSButtonCellExtensions)

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

// Deprecations

typedef NS_ENUM(NSUInteger, NSGradientType) {
    NSGradientNone          = 0,
    NSGradientConcaveWeak   = 1,
    NSGradientConcaveStrong = 2,
    NSGradientConvexWeak    = 3,
    NSGradientConvexStrong  = 4
} NS_DEPRECATED_MAC(10_0, 10_12);

static const NSButtonType NSMomentaryLightButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeMomentaryLight", 10_0, 10_14) = NSButtonTypeMomentaryLight;
static const NSButtonType NSPushOnPushOffButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypePushOnPushOff", 10_0, 10_14) = NSButtonTypePushOnPushOff;
static const NSButtonType NSToggleButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeToggle", 10_0, 10_14) = NSButtonTypeToggle;
static const NSButtonType NSSwitchButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeSwitch", 10_0, 10_14) = NSButtonTypeSwitch;
static const NSButtonType NSRadioButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeRadio", 10_0, 10_14) = NSButtonTypeRadio;
static const NSButtonType NSMomentaryChangeButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeMomentaryChange", 10_0, 10_14) = NSButtonTypeMomentaryChange;
static const NSButtonType NSOnOffButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeOnOff", 10_0, 10_14) = NSButtonTypeOnOff;
static const NSButtonType NSMomentaryPushInButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeMomentaryPushIn", 10_0, 10_14) = NSButtonTypeMomentaryPushIn;
static const NSButtonType NSAcceleratorButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeAccelerator", 10_10_3, 10_14) = NSButtonTypeAccelerator;
static const NSButtonType NSMultiLevelAcceleratorButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSButtonTypeMultiLevelAccelerator", 10_10_3, 10_14) = NSButtonTypeMultiLevelAccelerator;

/* These constants were accidentally reversed so that NSMomentaryPushButton lit and NSMomentaryLight pushed. These names are now deprecated */
static const NSButtonType NSMomentaryPushButton NS_ENUM_DEPRECATED_MAC(10_0, 10_9, "This constant is misnamed and has the same effect as NSButtonTypeMomentaryLight. Use that name instead, or switch to NSButtonTypeMomentaryPushIn.") = NSButtonTypeMomentaryLight;
static const NSButtonType NSMomentaryLight NS_ENUM_DEPRECATED_MAC(10_0, 10_9, "This constant is misnamed and has the same effect as NSButtonTypeMomentaryPushIn. Use that name instead, or switch to NSButtonTypeMomentaryLight.") = NSButtonTypeMomentaryPushIn;

static const NSBezelStyle NSRoundedBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRounded", 10_0, 10_14) = NSBezelStyleRounded;
static const NSBezelStyle NSRegularSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRegularSquare", 10_0, 10_14) = NSBezelStyleRegularSquare;
static const NSBezelStyle NSDisclosureBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleDisclosure", 10_0, 10_14) = NSBezelStyleDisclosure;
static const NSBezelStyle NSShadowlessSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleShadowlessSquare", 10_0, 10_14) = NSBezelStyleShadowlessSquare;
static const NSBezelStyle NSCircularBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleCircular", 10_0, 10_14) = NSBezelStyleCircular;
static const NSBezelStyle NSTexturedSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleTexturedSquare", 10_0, 10_14) = NSBezelStyleTexturedSquare;
static const NSBezelStyle NSHelpButtonBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleHelpButton", 10_0, 10_14) = NSBezelStyleHelpButton;
static const NSBezelStyle NSSmallSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleSmallSquare", 10_0, 10_14) = NSBezelStyleSmallSquare;
static const NSBezelStyle NSTexturedRoundedBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleTexturedRounded", 10_0, 10_14) = NSBezelStyleTexturedRounded;
static const NSBezelStyle NSRoundRectBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRoundRect", 10_0, 10_14) = NSBezelStyleRoundRect;
static const NSBezelStyle NSRecessedBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRecessed", 10_0, 10_14) = NSBezelStyleRecessed;
static const NSBezelStyle NSRoundedDisclosureBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRoundedDisclosure", 10_0, 10_14) = NSBezelStyleRoundedDisclosure;
static const NSBezelStyle NSInlineBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleInline", 10_0, 10_14) = NSBezelStyleInline;

static const NSBezelStyle NSSmallIconButtonBezelStyle NS_ENUM_DEPRECATED_MAC(10_0, 10_0, "This bezel style is obsolete and should not be used.") = (NSBezelStyle)2;
static const NSBezelStyle NSThickSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRegularSquare", 10_0, 10_12) = (NSBezelStyle)3;
static const NSBezelStyle NSThickerSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRegularSquare", 10_0, 10_12) = (NSBezelStyle)4;

@interface NSButtonCell(NSDeprecated)

@property NSGradientType gradientType NS_DEPRECATED_MAC(10_0, 10_12, "The gradientType property is unused, and setting it has no effect.");

// On 10.8, these two methods still will call setTitle: (or setAlternateTitle:) with the ampersand stripped from stringWithAmpersand, but does nothing else. Use setTitle directly.
- (void)setTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);
- (void)setAlternateTitleWithMnemonic:(null_unspecified NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

// This method no longer does anything and should not be called.
- (void)setAlternateMnemonicLocation:(NSUInteger)location NS_DEPRECATED_MAC(10_0, 10_8, "This method is obsolete. Calling it has no effect.");

// On 10.8, alternateMnemonicLocation now always returns NSNotFound.
- (NSUInteger)alternateMnemonicLocation NS_DEPRECATED_MAC(10_0, 10_8);

- (null_unspecified NSString *)alternateMnemonic NS_DEPRECATED_MAC(10_0, 10_8);
@end

NS_ASSUME_NONNULL_END

