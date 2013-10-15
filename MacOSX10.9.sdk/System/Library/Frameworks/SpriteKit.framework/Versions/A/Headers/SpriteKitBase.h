//
//  SpriteKitBase.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>
#import <CoreGraphics/CGGeometry.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

#ifdef __cplusplus
#define SK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define SK_EXPORT extern __attribute__((visibility ("default")))
#endif
#define SK_AVAILABLE __OSX_AVAILABLE_STARTING

#if TARGET_OS_IPHONE
#define SK_NONATOMIC_IOSONLY nonatomic
#else
#define SK_NONATOMIC_IOSONLY atomic
#endif

#if TARGET_OS_IPHONE
#define SKColor UIColor
#else
#define SKColor NSColor
#endif


#ifndef CGVECTOR_DEFINED
#define CGVECTOR_DEFINED 1
struct CGVector {
    CGFloat dx;
    CGFloat dy;
};

typedef struct CGVector CGVector;

CG_INLINE CGVector CGVectorMake(CGFloat dx, CGFloat dy) {
    CGVector vector; vector.dx = dx; vector.dy = dy; return vector;
}
#endif
