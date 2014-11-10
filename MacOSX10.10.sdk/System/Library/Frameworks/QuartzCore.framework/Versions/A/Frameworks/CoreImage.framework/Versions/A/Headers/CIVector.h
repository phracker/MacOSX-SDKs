/* CoreImage - CIVector.h

   Copyright (c) 2004 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>
#import <stddef.h>



CORE_IMAGE_CLASS_EXPORT
@interface CIVector : NSObject <NSCopying, NSCoding>
{
    size_t _count;

    union {
        CGFloat vec[4];
        CGFloat *ptr;
    }
    _u;
}

/* Create a new vector object. */

+ (CIVector *)vectorWithValues:(const CGFloat *)values count:(size_t)count;

+ (CIVector *)vectorWithX:(CGFloat)x;
+ (CIVector *)vectorWithX:(CGFloat)x Y:(CGFloat)y;
+ (CIVector *)vectorWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z;
+ (CIVector *)vectorWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z W:(CGFloat)w;

/* the CGPoint x and y values are stored in the first X and Y values of the CIVector. */
+ (CIVector *)vectorWithCGPoint:(CGPoint)p __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);

/* the CGRect x, y, width, height values are stored in the first X, Y, Z, W values of the CIVector. */
+ (CIVector *)vectorWithCGRect:(CGRect)r __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);

/* the CGAffineTransform's six values are stored in the first six values of the CIVector. */
+ (CIVector *)vectorWithCGAffineTransform:(CGAffineTransform)t __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);

+ (CIVector *)vectorWithString:(NSString *)representation;

/* Initializers. */

- (id)initWithValues:(const CGFloat *)values count:(size_t)count;

- (id)initWithX:(CGFloat)x;
- (id)initWithX:(CGFloat)x Y:(CGFloat)y;
- (id)initWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z;
- (id)initWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z W:(CGFloat)w;
- (id)initWithCGPoint:(CGPoint)p __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);
- (id)initWithCGRect:(CGRect)r __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);
- (id)initWithCGAffineTransform:(CGAffineTransform)r __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);

- (id)initWithString:(NSString *)representation;

/* Return the value from the vector at position 'index' (zero-based).
 * Any 'index' value is valid, if the component would otherwise be
 * undefined, zero is returned. */
- (CGFloat)valueAtIndex:(size_t)index;

/* Return the number of values stored in the vector. */
- (size_t)count;

/* Getters. */

- (CGFloat)X;
- (CGFloat)Y;
- (CGFloat)Z;
- (CGFloat)W;
- (CGPoint)CGPointValue __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);
- (CGRect)CGRectValue __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);
- (CGAffineTransform)CGAffineTransformValue __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_5_0);

/* Return a string representing the vector such that a similar vector
 * can be created by calling the vectorWithString: method. */
- (NSString *)stringRepresentation;

@end
