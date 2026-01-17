/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-2017, Apple Inc.
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
    unsigned int        imageHugsTitle:1;
    unsigned int        shouldNotHighlightOnPerformClick:1;
    unsigned int        leadingOrTrailing:1;
    unsigned int        alwaysRadioExclusive:1;
    unsigned int        hasOverlayView:1;
    unsigned int        __reserved:1;
#else
    unsigned int        __reserved:1;
    unsigned int        hasOverlayView:1;
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

@interface NSButtonCell : NSActionCell {
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

// The following NSButtonType constants will be deprecated in a future release. Please migrate to the modern equivalents.
static const NSButtonType NSMomentaryLightButton = NSButtonTypeMomentaryLight;
static const NSButtonType NSPushOnPushOffButton = NSButtonTypePushOnPushOff;
static const NSButtonType NSToggleButton = NSButtonTypeToggle;
static const NSButtonType NSSwitchButton = NSButtonTypeSwitch;
static const NSButtonType NSRadioButton = NSButtonTypeRadio;
static const NSButtonType NSMomentaryChangeButton = NSButtonTypeMomentaryChange;
static const NSButtonType NSOnOffButton = NSButtonTypeOnOff;
static const NSButtonType NSMomentaryPushInButton = NSButtonTypeMomentaryPushIn;
static const NSButtonType NSAcceleratorButton = NSButtonTypeAccelerator;
static const NSButtonType NSMultiLevelAcceleratorButton = NSButtonTypeMultiLevelAccelerator;

/* These constants were accidentally reversed so that NSMomentaryPushButton lit and NSMomentaryLight pushed. These names are now deprecated */
static const NSButtonType NSMomentaryPushButton NS_ENUM_DEPRECATED_MAC(10_0, 10_9, "This constant is misnamed and has the same effect as NSButtonTypeMomentaryLight. Use that name instead, or switch to NSButtonTypeMomentaryPushIn.") = NSButtonTypeMomentaryLight;
static const NSButtonType NSMomentaryLight NS_ENUM_DEPRECATED_MAC(10_0, 10_9, "This constant is misnamed and has the same effect as NSButtonTypeMomentaryPushIn. Use that name instead, or switch to NSButtonTypeMomentaryLight.") = NSButtonTypeMomentaryPushIn;

// The following NSBezelStyle constants will be deprecated in a future release. Please migrate to the modern equivalents.
static const NSBezelStyle NSRoundedBezelStyle = NSBezelStyleRounded;
static const NSBezelStyle NSRegularSquareBezelStyle = NSBezelStyleRegularSquare;
static const NSBezelStyle NSDisclosureBezelStyle = NSBezelStyleDisclosure;
static const NSBezelStyle NSShadowlessSquareBezelStyle = NSBezelStyleShadowlessSquare;
static const NSBezelStyle NSCircularBezelStyle = NSBezelStyleCircular;
static const NSBezelStyle NSTexturedSquareBezelStyle = NSBezelStyleTexturedSquare;
static const NSBezelStyle NSHelpButtonBezelStyle = NSBezelStyleHelpButton;
static const NSBezelStyle NSSmallSquareBezelStyle = NSBezelStyleSmallSquare;
static const NSBezelStyle NSTexturedRoundedBezelStyle = NSBezelStyleTexturedRounded;
static const NSBezelStyle NSRoundRectBezelStyle = NSBezelStyleRoundRect;
static const NSBezelStyle NSRecessedBezelStyle = NSBezelStyleRecessed;
static const NSBezelStyle NSRoundedDisclosureBezelStyle = NSBezelStyleRoundedDisclosure;
static const NSBezelStyle NSInlineBezelStyle = NSBezelStyleInline;

static const NSBezelStyle NSSmallIconButtonBezelStyle NS_ENUM_DEPRECATED_MAC(10_0, 10_0, "This bezel style is obsolete and should not be used.") = (NSBezelStyle)2;
static const NSBezelStyle NSThickSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRegularSquare", 10.0, 10.12) = (NSBezelStyle)3;
static const NSBezelStyle NSThickerSquareBezelStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBezelStyleRegularSquare", 10.0, 10.12) = (NSBezelStyle)4;

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

