/* CoreImage - CIFilterShape.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>

@interface CIFilterShape : NSObject <NSCopying>
{
@public
    uint32_t _pad;
    void *_priv;
}

/* Create a shape representing the smallest integral rect containing 'r'. */

+ (id)shapeWithRect:(CGRect)r;

/* Initializer. */

- (id)initWithRect:(CGRect)r;

/* Create a shape from the result of transforming the shape by 'm'. If
 * 'flag' is false the new shape will contain all pixels in the
 * transformed shape (and possibly some outside the transformed shape).
 * If 'flag' is false the new shape will contain a subset of the pixels
 * in the transformed shape (but none of those outside the transformed
 * shape). */

- (CIFilterShape *)transformBy:(CGAffineTransform)m interior:(BOOL)flag;

/* Create a shape representing the shape inset by 'delta'. */

- (CIFilterShape *)insetByX:(int)dx Y:(int)dy;

/* Create a shape representing the union of the shape and 's2'. */

- (CIFilterShape *)unionWith:(CIFilterShape *)s2;

/* Create a shape representing the union of the shape and the smallest
 * integral rect containing 'r'. */

- (CIFilterShape *)unionWithRect:(CGRect)r;

/* Create a shape representing the intersection of the shape and 's2'. */

- (CIFilterShape *)intersectWith:(CIFilterShape *)s2;

/* Create a shape representing the intersection of the shape and the smallest
 * integral rect containing 'r'. */

- (CIFilterShape *)intersectWithRect:(CGRect)r;

@end
