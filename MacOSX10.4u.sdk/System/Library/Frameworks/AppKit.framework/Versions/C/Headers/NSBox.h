/*
	NSBox.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>

@class NSFont;

typedef enum _NSTitlePosition {
    NSNoTitle				= 0,
    NSAboveTop				= 1,
    NSAtTop				= 2,
    NSBelowTop				= 3,
    NSAboveBottom			= 4,
    NSAtBottom				= 5,
    NSBelowBottom			= 6
} NSTitlePosition;

typedef enum {
    NSBoxPrimary	= 0,	// default
    NSBoxSecondary	= 1,
    NSBoxSeparator	= 2,
    NSBoxOldStyle	= 3	// use border type
} NSBoxType;

@interface NSBox : NSView
{
    /*All instance variables are private*/
    id                  _titleCell;
    id                  _contentView;
    NSSize              _offsets;
    NSRect              _borderRect;
    NSRect              _titleRect;
    struct __bFlags {
	NSBorderType	borderType:2;
	NSTitlePosition	titlePosition:3;
	unsigned int	transparent:1;
        unsigned int	boxType:2;
        unsigned int	needsTile:1;
        unsigned int	_RESERVED:23;
    } _bFlags;
    id			_unused;
}

- (NSBorderType)borderType;
- (NSTitlePosition)titlePosition;
- (void)setBorderType:(NSBorderType)aType;
- (void)setBoxType:(NSBoxType)boxType;
- (NSBoxType)boxType;
- (void)setTitlePosition:(NSTitlePosition)aPosition;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSRect)borderRect;
- (NSRect)titleRect;
- (id)titleCell;
- (void)sizeToFit;
- (NSSize)contentViewMargins;
- (void)setContentViewMargins:(NSSize)offsetSize;
- (void)setFrameFromContentFrame:(NSRect)contentFrame;
- (id)contentView;
- (void)setContentView:(NSView *)aView;

@end

@interface NSBox(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end
