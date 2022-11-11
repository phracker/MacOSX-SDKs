//
//  SpriteKitBase.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//
#ifndef PHYSICSKIT_MINUS_GL_IMPORTS
#define PHYSICSKIT_MINUS_GL_IMPORTS 1
#endif

#import <Availability.h>
#import <TargetConditionals.h>
#import <CoreGraphics/CGGeometry.h>
#import <Foundation/Foundation.h>

#import <SpriteKit/SKVersion.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif


#if TARGET_OS_IPHONE && !__has_include(<UIKit/UIView.h>)
#define SKVIEW_AVAILABLE 0
#else
#define SKVIEW_AVAILABLE 1
#endif

#ifdef __cplusplus
#define SK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define SK_EXPORT extern __attribute__((visibility ("default")))
#endif
#define SK_AVAILABLE __OSX_AVAILABLE_STARTING
#define SK_WEAK_LINK __attribute__((weak_import))

#if TARGET_OS_IPHONE
#define SKColor UIColor
#else
#define SKColor NSColor
#endif

typedef float vector_float3 __attribute__((__ext_vector_type__(3)));

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

