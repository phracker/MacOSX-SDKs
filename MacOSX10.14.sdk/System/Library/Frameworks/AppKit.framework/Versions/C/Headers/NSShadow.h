/*
        NSShadow.h
        Application Kit
	Copyright (c) 2002-2018, Apple Inc.
        All rights reserved.
*/

/* NSShadow stores the properties of a drop shadow to be added to drawing.  */

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor;

@interface NSShadow : NSObject <NSCopying, NSSecureCoding> {
    /*All instance variables are private*/
    NSUInteger _shadowFlags APPKIT_IVAR;
    NSSize _shadowOffset APPKIT_IVAR;
    CGFloat _shadowBlurRadius APPKIT_IVAR;
    NSColor *_shadowColor APPKIT_IVAR;
    CGFloat _reservedFloat[3] APPKIT_IVAR;
    void *_reserved APPKIT_IVAR;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;     // designated initializer, returns a default shadow with zero offset, zero blur radius, and default color

@property NSSize shadowOffset;  // offset in user space of the shadow from the original drawing, in default user space units, where positive values are up and to the right

@property CGFloat shadowBlurRadius;      // blur radius of the shadow in default user space units

@property(nullable, copy) NSColor *shadowColor;   // color used for the shadow (default is black with an alpha value of 1/3)

- (void)set;

@end

NS_ASSUME_NONNULL_END
