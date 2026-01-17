/*
	NSColorWell.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

@interface NSColorWell : NSControl
{
    /*All instance variables are private*/
    NSColor *_color;
    id _target;
    SEL _action;
    struct __cwFlags {
	unsigned int        isActive:1;
	unsigned int        isBordered:1;
	unsigned int        cantDraw:1;
	unsigned int        isNotContinuous:1;
	unsigned int	    reservedColorWell:28;
    } _cwFlags;
}

- (void)deactivate;
- (void)activate:(BOOL)exclusive;
- (BOOL)isActive;

- (void)drawWellInside:(NSRect)insideRect;

- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;

- (void)takeColorFrom:(id)sender;
- (void)setColor:(NSColor *)color;
- (NSColor *)color;

@end
