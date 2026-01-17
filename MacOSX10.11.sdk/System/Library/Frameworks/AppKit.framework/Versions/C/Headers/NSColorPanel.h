/*
	NSColorPanel.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/NSApplication.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColorList, NSMutableArray;

typedef NS_ENUM(NSInteger, NSColorPanelMode) {
    /* If the color panel is not displaying a mode, the NSNoModeColorPanel will be returned */
    NSNoModeColorPanel NS_ENUM_AVAILABLE_MAC(10_5) = -1,
    NSGrayModeColorPanel		= 0,
    NSRGBModeColorPanel			= 1,
    NSCMYKModeColorPanel		= 2,
    NSHSBModeColorPanel			= 3,
    NSCustomPaletteModeColorPanel	= 4,
    NSColorListModeColorPanel		= 5,
    NSWheelModeColorPanel		= 6,
    NSCrayonModeColorPanel		= 7
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
+ (BOOL)dragColor:(NSColor *)color withEvent:(NSEvent *)theEvent fromView:(NSView *)sourceView;
+ (void)setPickerMask:(NSColorPanelOptions)mask;
+ (void)setPickerMode:(NSColorPanelMode)mode;

@property (nullable, strong) NSView *accessoryView;
@property (getter=isContinuous) BOOL continuous;
@property BOOL showsAlpha;
@property NSColorPanelMode mode;
@property (copy) NSColor *color;
@property (readonly) CGFloat alpha;
- (void)setAction:(nullable SEL)aSelector;
- (void)setTarget:(nullable id)anObject;
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
APPKIT_EXTERN NSString * NSColorPanelColorDidChangeNotification;

NS_ASSUME_NONNULL_END

