/*
        NSAffineTransform.h
        Foundation Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

typedef struct _NSAffineTransformStruct {
    float m11, m12, m21, m22;
    float tX, tY;
} NSAffineTransformStruct;

@interface NSAffineTransform : NSObject <NSCopying, NSCoding>
{
    @private
    NSAffineTransformStruct _transformStruct;
}

// Creation
+ (NSAffineTransform *)transform;

// Initialization
- (id)initWithTransform:(NSAffineTransform *)transform;

// Translating
- (void)translateXBy:(float)deltaX yBy:(float)deltaY;

// Rotating
- (void)rotateByDegrees:(float)angle;
- (void)rotateByRadians:(float)angle;

// Scaling
- (void)scaleBy:(float)scale;
- (void)scaleXBy:(float)scaleX yBy:(float)scaleY;

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
