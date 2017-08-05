/*
	NSColorPanel.h
	Application Kit
	Copyright (c) 1994-2016, Apple Inc.
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
    id			_colorSwatch;
    id                  _accessoryContainerView;
    id			_colorWell;
    NSMutableArray     *_pickersWithLoadedViews;
    id			_magnifyButton;
    id			_middleView;
    id			_opacitySlider;
    id			_opacityText;
    id			_opacityView;
    id			_modalButtons;
    id			_pickerView;
    id			_customViewsList;
    id			_customPickerList;
    id			_currViewObject;
    id			_bottomConstraint;
    id			_target;
    id			_accessoryView;
    SEL			_action;
    NSSize		_minColorPanelSize;
    NSSize		_maxColorPanelSize;
    id                  _accessoryContainerViewHeight;
    id                  _opacityViewHeight;
    id                  _reserved1;
    id                  _reserved2;
    id			_resizeDimple;
    BOOL                _reserved3;
    BOOL		_reserved4;
    BOOL		_handlingOpacityMoveAction;
    BOOL		_ignoreConstraints;
    BOOL		_continuous;
    BOOL		_allowColorSetting;
    BOOL		_stillInitializing;
    BOOL                _reserved5;
    id			_opacityTextController;
}

+ (NSColorPanel *)sharedColorPanel;
+ (BOOL)sharedColorPanelExists;
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

@interface NSObject(NSColorPanelResponderMethod)
- (void)changeColor:(nullable id)sender;
@end

/* Notifications */
APPKIT_EXTERN NSNotificationName NSColorPanelColorDidChangeNotification;


static const NSColorPanelMode NSNoModeColorPanel NS_AVAILABLE_MAC(10_5) /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeNone", macosx(10.5, 10.12))*/ = NSColorPanelModeNone;
static const NSColorPanelMode NSGrayModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeGray", macosx(10.0, 10.12))*/ = NSColorPanelModeGray;
static const NSColorPanelMode NSRGBModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeRGB", macosx(10.0, 10.12))*/ = NSColorPanelModeRGB;
static const NSColorPanelMode NSCMYKModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeCMYK", macosx(10.0, 10.12))*/ = NSColorPanelModeCMYK;
static const NSColorPanelMode NSHSBModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeHSB", macosx(10.0, 10.12))*/ = NSColorPanelModeHSB;
static const NSColorPanelMode NSCustomPaletteModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeCustomPalette", macosx(10.0, 10.12))*/ = NSColorPanelModeCustomPalette;
static const NSColorPanelMode NSColorListModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeColorList", macosx(10.0, 10.12))*/ = NSColorPanelModeColorList;
static const NSColorPanelMode NSWheelModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeWheel", macosx(10.0, 10.12))*/ = NSColorPanelModeWheel;
static const NSColorPanelMode NSCrayonModeColorPanel /*API_DEPRECATED_WITH_REPLACEMENT("NSColorPanelModeCrayon", macosx(10.0, 10.12))*/ = NSColorPanelModeCrayon;

NS_ASSUME_NONNULL_END

