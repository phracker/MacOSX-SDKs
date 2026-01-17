/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@class NSAttributedString, NSFont, NSImage, NSSound;

enum {
    NSMomentaryLightButton		= 0,	// was NSMomentaryPushButton
    NSPushOnPushOffButton		= 1,
    NSToggleButton			= 2,
    NSSwitchButton			= 3,
    NSRadioButton			= 4,
    NSMomentaryChangeButton		= 5,
    NSOnOffButton			= 6,
    NSMomentaryPushInButton		= 7,	// was NSMomentaryLight

    /* These constants were accidentally reversed so that NSMomentaryPushButton lit and
       NSMomentaryLight pushed. These names are now deprecated */
    
    NSMomentaryPushButton		= 0,
    NSMomentaryLight			= 7
    
};
typedef NSUInteger NSButtonType;

enum {

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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
    // The inline bezel style contains a solid round-rect border background. It can be used to create an "unread" indicator in an outline view, or another inline button in a tableview, such as a stop progress button in a download panel. Use text for an unread indicator, and a template image for other buttons.
    NSInlineBezelStyle = 15,
#endif
    
    // This bezel style is obsolete and should not be used.
    NSSmallIconButtonBezelStyle  = 2
    
};
typedef NSUInteger NSBezelStyle;

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
    unsigned int        reserved:1;
    unsigned int        useButtonImageSource:1;
    unsigned int        alternateMnemonicLocation:8;
#else
    unsigned int        alternateMnemonicLocation:8;
    unsigned int        useButtonImageSource:1;
    unsigned int        reserved:1;
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
    _BCFlags2		_bcFlags2; // was _keyEquivalentModifierMask
    unsigned short	_periodicDelay;
    unsigned short	_periodicInterval;
    _BCFlags            _bcFlags;
    NSImage            *_normalImage;
    id                  _alternateImageOrKeyEquivalentFont;
}


- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSString *)alternateTitle;
- (void)setAlternateTitle:(NSString *)aString;

- (NSImage *)alternateImage;
- (void)setAlternateImage:(NSImage *)image;
- (NSCellImagePosition)imagePosition;
- (void)setImagePosition:(NSCellImagePosition)aPosition;
- (NSImageScaling)imageScaling NS_AVAILABLE_MAC(10_5);
- (void)setImageScaling:(NSImageScaling)scaling NS_AVAILABLE_MAC(10_5);

- (NSInteger)highlightsBy;
- (void)setHighlightsBy:(NSInteger)aType;
- (NSInteger)showsStateBy;
- (void)setShowsStateBy:(NSInteger)aType;
- (void)setButtonType:(NSButtonType)aType;
- (BOOL)isOpaque;
- (void)setFont:(NSFont *)fontObj;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (NSUInteger)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(NSUInteger)mask;
- (NSFont *)keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSFont *)fontObj;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(CGFloat)fontSize;
- (void)performClick:(id)sender; // Significant NSCell override, actually clicks itself.

- (void)drawImage:(NSImage*)image withFrame:(NSRect)frame inView:(NSView*)controlView;
- (NSRect)drawTitle:(NSAttributedString*)title withFrame:(NSRect)frame inView:(NSView*)controlView;
- (void)drawBezelWithFrame:(NSRect)frame inView:(NSView*)controlView;
@end

@interface NSButtonCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateMnemonicLocation:(NSUInteger)location;
- (NSUInteger)alternateMnemonicLocation;
- (NSString *)alternateMnemonic;
@end

// NSGradientType :
//
// A concave gradient is darkest in the top left corner, 
// a convex gradient is darkest in the bottom right corner.
//
// Weak versus strong is how much contrast exists between
// the colors used in opposite corners
enum {
    NSGradientNone          = 0,
    NSGradientConcaveWeak   = 1,
    NSGradientConcaveStrong = 2,
    NSGradientConvexWeak    = 3,
    NSGradientConvexStrong  = 4
};
typedef NSUInteger NSGradientType;

@interface NSButtonCell(NSButtonCellExtensions)
- (NSGradientType)gradientType;
- (void)setGradientType:(NSGradientType)type;

// When disabled, the image and text of an NSButtonCell are normally dimmed with gray.
// Radio buttons and switches use (imageDimsWhenDisabled == NO) so only their text is dimmed.
- (void)setImageDimsWhenDisabled:(BOOL)flag;
- (BOOL)imageDimsWhenDisabled;

- (void) setShowsBorderOnlyWhileMouseInside:(BOOL)show;
- (BOOL) showsBorderOnlyWhileMouseInside;

- (void) mouseEntered:(NSEvent*)event;
- (void) mouseExited:(NSEvent*)event;

- (NSColor*)backgroundColor;
- (void)setBackgroundColor:(NSColor*)color;

@end

@interface NSButtonCell(NSButtonCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
- (NSAttributedString *)attributedAlternateTitle;
- (void)setAttributedAlternateTitle:(NSAttributedString *)obj;
@end

@interface NSButtonCell(NSButtonCellBezelStyles)

- (void) setBezelStyle:(NSBezelStyle)bezelStyle;
- (NSBezelStyle)bezelStyle;

@end

@interface NSButtonCell (NSButtonCellSoundExtensions)
- (void)setSound:(NSSound *)aSound;
- (NSSound *)sound;
@end

