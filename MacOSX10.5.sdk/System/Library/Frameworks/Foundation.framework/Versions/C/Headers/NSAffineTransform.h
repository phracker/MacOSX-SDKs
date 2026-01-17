/*	NSAffineTransform.h
        Copyright (c) 1997-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CGAffineTransform.h>

typedef struct {
    CGFloat m11, m12, m21, m22;
    CGFloat tX, tY;
} NSAffineTransformStruct;

@interface NSAffineTransform : NSObject <NSCopying, NSCoding> {
    @private
    NSAffineTransformStruct _transformStruct;
}

// Creation
+ (NSAffineTransform *)transform;

// Initialization
- (id)initWithTransform:(NSAffineTransform *)transform;

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
- (NSAffineTransformStruct)transformStruct;
- (void)setTransformStruct:(NSAffineTransformStruct)transformStruct;

@end

