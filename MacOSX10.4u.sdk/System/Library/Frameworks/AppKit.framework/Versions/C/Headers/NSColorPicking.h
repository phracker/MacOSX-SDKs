/*
	NSColorPicking.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>

@class NSButtonCell, NSColor, NSColorPanel, NSColorList, NSImage, NSView;

@protocol NSColorPickingDefault

// The following methods are implemented by the generic base class:
// NSColorPicker, and only need be implemented (overridden) by the CustomPicker
// developer if there is a need.

// "mask" is the mask (if any) passed to the ColorPanel by the
// + setPickerMask: method.  If your picker supports any of the bits in
// the mask, return "self", otherwise, return "nil" (default is "self" if not
// overridden, since if the "setPickerMask" method is never called, the
// ColorPanel will just start off with the normal picker modes, of which
// your custom mode will not be a part). This method can be used to turn
// off some (or all) of your subpickers, if you have any (like sliders).
// If this method returns "nil", the object will be freed.
// 
// "owningColorPanel" is the id of the instantiating ColorPanel.  
// if this method is overridden, the base class' (NSColorPicker's) 
// initFromPickerMask method should be called before any subclass processing.
// The instance variable "colorPanel" is set in this method.
// FOR PERFORMANCE, DO NOT LOAD .NIBS, ETC. HERE!!  WAIT 'TILL PROVIDENEWVIEW!
- (id)initWithPickerMask:(int)mask colorPanel:(NSColorPanel *)owningColorPanel;
- (NSImage *)provideNewButtonImage;
- (void)insertNewButtonImage:(NSImage *)newButtonImage in:(NSButtonCell *)buttonCell;
- (void)viewSizeChanged:(id)sender;
- (void)alphaControlAddedOrRemoved:(id)sender;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
- (void)setMode:(int)mode;   

@end



@protocol NSColorPickingCustom

// These methods *MUST* be implemented by the CustomPicker, or an error
// will occur!

// Return No if "mode" not supported.
- (BOOL)supportsMode:(int)mode;   
- (int)currentMode;
// "Yes" on very first call (load your .nibs etc when "YES").
- (NSView *)provideNewView:(BOOL)initialRequest;  // "Yes" on very first call.
- (void)setColor:(NSColor *)newColor;

@end

