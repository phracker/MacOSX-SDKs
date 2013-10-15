/*
    NSShadow.h
    Application Kit
    Copyright (c) 2002-2005, Apple Computer, Inc.
    All rights reserved.
*/

/* NSShadow stores the properties of a drop shadow to be added to drawing.  */

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSColor;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSShadow : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    unsigned int _shadowFlags;
    NSSize _shadowOffset;
    float _shadowBlurRadius;
    NSColor *_shadowColor;
    float _reservedFloat[3];
    void *_reserved;
}

- (id)init;     // designated initializer

- (NSSize)shadowOffset;  // offset in user space of the shadow from the original drawing, in default user space units, where positive values are up and to the right
- (void)setShadowOffset:(NSSize)offset;

- (float)shadowBlurRadius;      // blur radius of the shadow in default user space units
- (void)setShadowBlurRadius:(float)val;

- (NSColor *)shadowColor;   // color used for the shadow (default is black with an alpha value of 1/3)
- (void)setShadowColor:(NSColor *)color;

- (void)set;

@end

#endif
