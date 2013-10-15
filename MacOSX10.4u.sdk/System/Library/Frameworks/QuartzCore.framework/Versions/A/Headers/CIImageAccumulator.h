/* CoreImage - CIImageAccumulator.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <QuartzCore/CIImage.h>

@interface CIImageAccumulator : NSObject
{
    void *_state;
}

/* Create a new accumulator object. For pixel format options see
 * <QuartzCore/CIImage.h>. */

+ (CIImageAccumulator *)imageAccumulatorWithExtent:(CGRect)r format:(CIFormat)f;

- (id)initWithExtent:(CGRect)r format:(CIFormat)f;

/* Return the extent of the accumulator. */

- (CGRect)extent;

/* Return the pixel format of the accumulator. */

- (CIFormat)format;

/* Return an image representing the current contents of the accumulator.
 * <fixme>(Rendering the image after subsequently calling setImage: has
 * undefined behavior?)</fixme> */

- (CIImage *)image;

/* Set the image 'im' as the current contents of the accumulator. */

- (void)setImage:(CIImage *)im;

/* Set the image 'im' as the accumulator's contents. The caller guarantees
 * that the new contents only differ from the old within the specified
 * region. */

- (void)setImage:(CIImage *)im dirtyRect:(CGRect)r;

@end
