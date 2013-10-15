/* CoreImage - CIVector.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>
#import <stddef.h>

@interface CIVector: NSObject <NSCopying, NSCoding>
{
    size_t _count;

    union {
	float vec[4];
	float *ptr;
    } _u;
}

/* Create a new vector object. */

+ (CIVector *)vectorWithValues:(const float *)values count:(size_t)count;

+ (CIVector *)vectorWithX:(float)x;
+ (CIVector *)vectorWithX:(float)x Y:(float)y;
+ (CIVector *)vectorWithX:(float)x Y:(float)y Z:(float)z;
+ (CIVector *)vectorWithX:(float)x Y:(float)y Z:(float)z W:(float)w;

+ (CIVector *)vectorWithString:(NSString *)representation;

/* Initializers. */

- (id)initWithValues:(const float *)values count:(size_t)count;

- (id)initWithX:(float)x;
- (id)initWithX:(float)x Y:(float)y;
- (id)initWithX:(float)x Y:(float)y Z:(float)z;
- (id)initWithX:(float)x Y:(float)y Z:(float)z W:(float)w;

/* Return the value from the vector at position 'index' (zero-based).
 * Any 'index' value is valid, if the component would otherwise be
 * undefined, zero is returned. */

- (float)valueAtIndex:(size_t)index;

/* Return the number of values stored in the vector. */

- (size_t)count;

/* Getters. */

- (float)X;
- (float)Y;
- (float)Z;
- (float)W;

/* Return a string representing the vector such that a similar vector
 * can be created by calling the vectorWithString: method. */

- (NSString *)stringRepresentation;

@end
