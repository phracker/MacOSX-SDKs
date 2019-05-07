/*
	NSColorWell.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSColorWell : NSControl
{
    /*All instance variables are private*/
    NSColor *_color APPKIT_IVAR;
    id _reserved APPKIT_IVAR;
    SEL _reserved2 APPKIT_IVAR;
    struct __cwFlags {
	unsigned int        isActive:1;
	unsigned int        isBordered:1;
	unsigned int        cantDraw:1;
	unsigned int        isNotContinuous:1;
        unsigned int        refusesFR:1;
	unsigned int	    reservedColorWell:27;
    } _cwFlags APPKIT_IVAR;
}

- (void)deactivate;
- (void)activate:(BOOL)exclusive;
@property (getter=isActive, readonly) BOOL active;

- (void)drawWellInside:(NSRect)insideRect;

@property (getter=isBordered) BOOL bordered;

- (void)takeColorFrom:(nullable id)sender;
@property (copy) NSColor *color;

@end

NS_ASSUME_NONNULL_END
