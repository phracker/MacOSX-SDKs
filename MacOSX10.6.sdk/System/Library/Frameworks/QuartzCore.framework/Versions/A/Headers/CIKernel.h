/* CoreImage - CIKernel.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>

@class CIImage;
@class NSArray;

@interface CIKernel : NSObject
{
    void *_priv;
}

/* The string 's' should contain a program in the CoreImage dialect
 * of the OpenGL Shading Language. Each function marked as a kernel is
 * converted to a CIKernel object, all objects are then returned in
 * an array. */

+ (NSArray *)kernelsWithString:(NSString *)s;

/* Returns the name of the kernel. */

- (NSString *)name;

/* Sets the selector used by the kernel to query the region of interest
 * of the kernel. The method should have the following signature:
 *
 * - (CGRect)regionOf:(int)samplerIndex destRect:(CGRect)r userInfo:obj;
 *
 * where 'samplerIndex' is the texture unit being queried, and 'destRect'
 * is the extent of the region being rendered in global coordinates.
 * 'userInfo' is the object associated with the "user_info" when the
 * kernel was applied to its arguments. */

- (void)setROISelector:(SEL)aMethod;

@end
