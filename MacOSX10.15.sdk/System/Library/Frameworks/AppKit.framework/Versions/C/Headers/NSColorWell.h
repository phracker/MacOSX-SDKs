/*
	NSColorWell.h
	Application Kit
	Copyright (c) 1994-2019, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@interface NSColorWell : NSControl

- (void)deactivate;
- (void)activate:(BOOL)exclusive;
@property (getter=isActive, readonly) BOOL active;

- (void)drawWellInside:(NSRect)insideRect;

@property (getter=isBordered) BOOL bordered;

- (void)takeColorFrom:(nullable id)sender;
@property (copy) NSColor *color;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
