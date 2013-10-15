/*
	NSColorPicker.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSColorPicking.h>

@interface NSColorPicker : NSObject <NSColorPickingDefault>
{
    /*All instance variables are private*/
    id _imageObject;
    NSColorPanel *_colorPanel;
    NSString *_buttonToolTip;
}
- (id)initWithPickerMask:(int)mask colorPanel:(NSColorPanel *)owningColorPanel;
- (NSColorPanel *)colorPanel;
- (NSImage *)provideNewButtonImage;
- (void)insertNewButtonImage:(NSImage *)newButtonImage in:(NSButtonCell *)buttonCell;
- (void)viewSizeChanged:(id)sender;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
- (void)setMode:(int)mode;

@end
