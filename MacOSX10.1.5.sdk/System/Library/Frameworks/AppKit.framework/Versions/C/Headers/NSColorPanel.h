/*
	NSColorPanel.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/NSApplication.h>

@class NSColorList, NSSet, NSMutableSet, NSDate;

enum {
    NSGrayModeColorPanel		= 0,
    NSRGBModeColorPanel			= 1,
    NSCMYKModeColorPanel		= 2,
    NSHSBModeColorPanel			= 3,
    NSCustomPaletteModeColorPanel	= 4,
    NSColorListModeColorPanel		= 5,
    NSWheelModeColorPanel		= 6
};

enum {
    NSColorPanelGrayModeMask		= 0x00000001,
    NSColorPanelRGBModeMask		= 0x00000002,
    NSColorPanelCMYKModeMask		= 0x00000004,
    NSColorPanelHSBModeMask		= 0x00000008,
    NSColorPanelCustomPaletteModeMask	= 0x00000010,
    NSColorPanelColorListModeMask	= 0x00000020,
    NSColorPanelWheelModeMask		= 0x00000040,
    NSColorPanelAllModesMask		= 0x0000ffff
};
    
    

@interface NSColorPanel : NSPanel
{
    /*All instance variables are private*/
    id			_colorSwatch;
    id			_colorSwatchBox;
    id			_colorWell;
    id			_colorWellView;
    id			_magnifyButton;
    id			_middleView;
    id			_opacitySlider;
    id			_opacityText;
    id			_opacityView;
    id			_paletteMatrix;
    id			_pickerView;
    id			_customViewsList;
    id			_customPickerList;
    id			_currViewObject;
    id			_splitView;
    id			_target;
    id			_accessoryView;
    SEL			_action;
    NSSize		_minColorPanelSize;
    NSSize		_maxColorPanelSize;
    NSSize		_minMiddleViewSize;
    NSSize		_minSwatchSize;
    float		_swatchOffsetFromBox;
    float		_prevSwatchHeight;
    BOOL		_continuous;
    BOOL		_allowColorSetting;
    BOOL		_stillInitializing;
    unsigned int 	_reservedColorPanel;
}

+ (NSColorPanel *)sharedColorPanel;
+ (BOOL)sharedColorPanelExists;
+ (BOOL)dragColor:(NSColor *)color withEvent:(NSEvent *)theEvent fromView:(NSView *)sourceView;
+ (void)setPickerMask:(int)mask;
+ (void)setPickerMode:(int)mode;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)setContinuous:(BOOL)flag;
- (BOOL)isContinuous;
- (void)setShowsAlpha:(BOOL)flag;
- (BOOL)showsAlpha;
- (void)setMode:(int)mode;
- (int)mode;
- (void)setColor:(NSColor *)color;
- (NSColor *)color;
- (float)alpha;
- (void)setAction:(SEL)aSelector;
- (void)setTarget:(id)anObject;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
@end

@interface NSApplication(NSColorPanel)
- (void)orderFrontColorPanel:(id)sender;
@end

@interface NSObject(NSColorPanelResponderMethod)
- (void)changeColor:(id)sender;
@end

/* Notifications */
APPKIT_EXTERN NSString *NSColorPanelColorDidChangeNotification;

