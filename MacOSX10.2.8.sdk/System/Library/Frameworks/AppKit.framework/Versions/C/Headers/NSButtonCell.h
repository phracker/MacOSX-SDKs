/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@class NSAttributedString, NSFont, NSImage, NSSound;

typedef enum _NSButtonType {
    NSMomentaryLightButton		= 0,	// was NSMomentaryPushButton
    NSPushOnPushOffButton		= 1,
    NSToggleButton			= 2,
    NSSwitchButton			= 3,
    NSRadioButton			= 4,
    NSMomentaryChangeButton		= 5,
    NSOnOffButton			= 6,
    NSMomentaryPushInButton		= 7,	// was NSMomentaryLight

    /* These constants were accidentaly reversed so that NSMomentaryPushButton lit and
       NSMomentaryLight pushed. These names are now deprecated */
    
    NSMomentaryPushButton		= 0,
    NSMomentaryLight			= 7
    
} NSButtonType;

typedef enum _NSBezelStyle {

    NSRoundedBezelStyle          = 1,
    NSRegularSquareBezelStyle    = 2,
    NSThickSquareBezelStyle      = 3,
    NSThickerSquareBezelStyle    = 4,
    NSShadowlessSquareBezelStyle = 6,
    NSCircularBezelStyle         = 7,
    
    // this will be obsolete before GM

    NSSmallIconButtonBezelStyle  = 2
    
} NSBezelStyle;

typedef struct __BCFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        pushIn:1;
    unsigned int        changeContents:1;
    unsigned int        changeBackground:1;
    unsigned int        changeGray:1;
    unsigned int        lightByContents:1;
    unsigned int        lightByBackground:1;
    unsigned int        lightByGray:1;
    unsigned int        reserved:1;
    unsigned int        bordered:1;
    unsigned int        imageOverlaps:1;
    unsigned int        horizontal:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        imageAndText:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        lastState:1;
    unsigned int        transparent:1;
    unsigned int        inset:2;
    unsigned int        doesNotDimImage:1;
    unsigned int        gradientType:3;
    unsigned int        useButtonImageSource:1;
    unsigned int        alternateMnemonicLocation:8;
#else
    unsigned int        alternateMnemonicLocation:8;
    unsigned int        useButtonImageSource:1;
    unsigned int        gradientType:3;
    unsigned int        doesNotDimImage:1;
    unsigned int        inset:2;
    unsigned int        transparent:1;
    unsigned int        lastState:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        imageAndText:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        horizontal:1;
    unsigned int        imageOverlaps:1;
    unsigned int        bordered:1;
    unsigned int        hasAlpha:1;
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
    unsigned int	reserved:3;
    unsigned int	mouseInside:1;
    unsigned int	showsBorderOnlyWhileMouseInside:1;
    unsigned int	bezelStyle:3;
#else
    unsigned int	bezelStyle:3;
    unsigned int	showsBorderOnlyWhileMouseInside:1;
    unsigned int	mouseInside:1;
    unsigned int	reserved:3;
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
- (int)highlightsBy;
- (void)setHighlightsBy:(int)aType;
- (int)showsStateBy;
- (void)setShowsStateBy:(int)aType;
- (void)setButtonType:(NSButtonType)aType;
- (BOOL)isOpaque;
- (void)setFont:(NSFont *)fontObj;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (NSFont *)keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSFont *)fontObj;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(float)fontSize;
- (void)performClick:(id)sender; // Significant NSCell override, actually clicks itself.
@end

@interface NSButtonCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateMnemonicLocation:(unsigned)location;
- (unsigned)alternateMnemonicLocation;
- (NSString *)alternateMnemonic;
@end

// NSGradientType :
//
// A concave gradient is darkest in the top left corner, 
// a convex gradient is darkest in the bottom right corner.
//
// Weak versus strong is how much contrast exists between
// the colors used in opposite corners
typedef enum _NSGradientType {
    NSGradientNone          = 0,
    NSGradientConcaveWeak   = 1,
    NSGradientConcaveStrong = 2,
    NSGradientConvexWeak    = 3,
    NSGradientConvexStrong  = 4
} NSGradientType;

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

