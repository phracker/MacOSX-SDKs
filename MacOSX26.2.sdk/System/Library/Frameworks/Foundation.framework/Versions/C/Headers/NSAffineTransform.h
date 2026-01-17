/*	NSAffineTransform.h
        Copyright (c) 1997-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <CoreFoundation/CFCGTypes.h>

#if TARGET_OS_OSX
#ifndef __swift__
#import <CoreGraphics/CGAffineTransform.h>
#endif
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef struct NS_SWIFT_SENDABLE {
    CGFloat m11, m12, m21, m22;
    CGFloat tX, tY;
} NSAffineTransformStruct;

@interface NSAffineTransform : NSObject <NSCopying, NSSecureCoding>

// Creation
+ (NSAffineTransform *)transform;

// Initialization
- (instancetype)initWithTransform:(NSAffineTransform *)transform;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Translating
- (void)translateXBy:(CGFloat)deltaX yBy:(CGFloat)deltaY;

// Rotating
- (void)rotateByDegrees:(CGFloat)angle;
- (void)rotateByRadians:(CGFloat)angle;

// Scaling
- (void)scaleBy:(CGFloat)scale;
- (void)scaleXBy:(CGFloat)scaleX yBy:(CGFloat)scaleY;

// Inverting
- (void)invert;

// Transforming with transform
- (void)appendTransform:(NSAffineTransform *)transform;
- (void)prependTransform:(NSAffineTransform *)transform;

// Transforming points and sizes
- (NSPoint)transformPoint:(NSPoint)aPoint;
- (NSSize)transformSize:(NSSize)aSize;

// Transform Struct
@property NSAffineTransformStruct transformStruct;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
