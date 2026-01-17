/*
	NSColorPanel.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/NSApplication.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColorList, NSMutableArray;

typedef NS_ENUM(NSInteger, NSColorPanelMode) {
    /* If the color panel is not displaying a mode, the NSColorPanelModeNone will be returned */
    NSColorPanelModeNone NS_ENUM_AVAILABLE_MAC(10_5) = -1,
    NSColorPanelModeGray            = 0,
    NSColorPanelModeRGB             = 1,
    NSColorPanelModeCMYK            = 2,
    NSColorPanelModeHSB             = 3,
    NSColorPanelModeCustomPalette   = 4,
    NSColorPanelModeColorList       = 5,
    NSColorPanelModeWheel           = 6,
    NSColorPanelModeCrayon          = 7
};

typedef NS_OPTIONS(NSUInteger, NSColorPanelOptions) {
    NSColorPanelGrayModeMask		= 0x00000001,
    NSColorPanelRGBModeMask		= 0x00000002,
    NSColorPanelCMYKModeMask		= 0x00000004,
    NSColorPanelHSBModeMask		= 0x00000008,
    NSColorPanelCustomPaletteModeMask	= 0x00000010,
    NSColorPanelColorListModeMask	= 0x00000020,
    NSColorPanelWheelModeMask		= 0x00000040,
    NSColorPanelCrayonModeMask		= 0x00000080,
    NSColorPanelAllModesMask		= 0x0000ffff
};
    
    

@interface NSColorPanel : NSPanel
{
    /*All instance variables are private*/
    id			_colorSwatch APPKIT_IVAR;
    id                  _accessoryContainerView APPKIT_IVAR;
    id			_colorWell APPKIT_IVAR;
    NSMutableArray     *_pickersWithLoadedViews APPKIT_IVAR;
    id			_magnifyButton APPKIT_IVAR;
    id			_middleView APPKIT_IVAR;
    id			_opacitySlider APPKIT_IVAR;
    id			_opacityText APPKIT_IVAR;
    id			_opacityView APPKIT_IVAR;
    id                  _modalButtons APPKIT_IVAR;
    id			_pickerView APPKIT_IVAR;
    id			_customViewsList APPKIT_IVAR;
    id			_customPickerList APPKIT_IVAR;
    id			_currViewObject APPKIT_IVAR;
    id			_bottomConstraint APPKIT_IVAR;
    id			_target APPKIT_IVAR;
    id			_accessoryView APPKIT_IVAR;
    SEL			_action APPKIT_IVAR;
    NSSize		_minColorPanelSize APPKIT_IVAR;
    NSSize		_maxColorPanelSize APPKIT_IVAR;
    id                  _accessoryContainerViewHeight APPKIT_IVAR;
    id                  _opacityViewHeight APPKIT_IVAR;
    id                  _reserved1 APPKIT_IVAR;
    NSUInteger          _colorSettingSuppressionCount APPKIT_IVAR;
    id			_resizeDimple APPKIT_IVAR;
    BOOL                _reserved3 APPKIT_IVAR;
    BOOL		_reserved4 APPKIT_IVAR;
    BOOL		_handlingOpacityMoveAction APPKIT_IVAR;
    BOOL		_ignoreConstraints APPKIT_IVAR;
    BOOL		_continuous APPKIT_IVAR;
    BOOL	        _reserved5 APPKIT_IVAR;
    BOOL		_stillInitializing APPKIT_IVAR;
    BOOL                _hasModalAppearance APPKIT_IVAR;
    id			_opacityTextController APPKIT_IVAR;
}

@property (class, readonly, strong) NSColorPanel *sharedColorPanel;
@property (class, readonly) BOOL sharedColorPanelExists;
+ (BOOL)dragColor:(NSColor *)color withEvent:(NSEvent *)event fromView:(NSView *)sourceView;
+ (void)setPickerMask:(NSColorPanelOptions)mask;
+ (void)setPickerMode:(NSColorPanelMode)mode;

@property (nullable, strong) NSView *accessoryView;
@property (getter=isContinuous) BOOL continuous;
@property BOOL showsAlpha;
@property NSColorPanelMode mode;
@property (copy) NSColor *color;
@property (readonly) CGFloat alpha;
- (void)setAction:(nullable SEL)selector;
- (void)setTarget:(nullable id)target;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
@end

@interface NSApplication(NSColorPanel)
- (void)orderFrontColorPanel:(nullable id)sender;
@end

@protocol NSColorChanging <NSObject>
- (void)changeColor:(nullable NSColorPanel *)sender;
@end

#if __swift__ < 40200
@interface NSObject(NSColorPanelResponderMethod)
- (void)changeColor:(nullable id)sender NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "This is now a method of the NSColorChanging protocol.");
@end
#endif

/* Notifications */
APPKIT_EXTERN NSNotificationName NSColorPanelColorDidChangeNotification;


static const NSColorPanelMode NSNoModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeNone", 10_5, 10_14) = NSColorPanelModeNone;
static const NSColorPanelMode NSGrayModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeGray", 10_0, 10_14) = NSColorPanelModeGray;
static const NSColorPanelMode NSRGBModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeRGB", 10_0, 10_14) = NSColorPanelModeRGB;
static const NSColorPanelMode NSCMYKModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeCMYK", 10_0, 10_14) = NSColorPanelModeCMYK;
static const NSColorPanelMode NSHSBModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeHSB", 10_0, 10_14) = NSColorPanelModeHSB;
static const NSColorPanelMode NSCustomPaletteModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeCustomPalette", 10_0, 10_14) = NSColorPanelModeCustomPalette;
static const NSColorPanelMode NSColorListModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeColorList", 10_0, 10_14) = NSColorPanelModeColorList;
static const NSColorPanelMode NSWheelModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeWheel", 10_0, 10_14) = NSColorPanelModeWheel;
static const NSColorPanelMode NSCrayonModeColorPanel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorPanelModeCrayon", 10_0, 10_14) = NSColorPanelModeCrayon;

NS_ASSUME_NONNULL_END

