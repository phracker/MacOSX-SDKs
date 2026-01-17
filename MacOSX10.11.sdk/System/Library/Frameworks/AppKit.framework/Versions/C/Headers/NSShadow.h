/*
        NSShadow.h
        Application Kit
	Copyright (c) 2002-2015, Apple Inc.
        All rights reserved.
*/

/* NSShadow stores the properties of a drop shadow to be added to drawing.  */

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor;

@interface NSShadow : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSUInteger _shadowFlags;
    NSSize _shadowOffset;
    CGFloat _shadowBlurRadius;
    NSColor *_shadowColor;
    CGFloat _reservedFloat[3];
    void *_reserved;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;     // designated initializer, returns a default shadow with zero offset, zero blur radius, and default color

@property NSSize shadowOffset;  // offset in user space of the shadow from the original drawing, in default user space units, where positive values are up and to the right

@property CGFloat shadowBlurRadius;      // blur radius of the shadow in default user space units

@property(nullable, copy) NSColor *shadowColor;   // color used for the shadow (default is black with an alpha value of 1/3)

- (void)set;

@end

NS_ASSUME_NONNULL_END
