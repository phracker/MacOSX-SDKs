/* CoreImage - CIImageAccumulator.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <CoreImage/CIImage.h>
#import <CoreImage/CoreImageDefines.h>


CORE_IMAGE_CLASS_EXPORT
@interface CIImageAccumulator : NSObject
{
    __strong void *_state;
}

/** Create a new accumulator object. For pixel format options see
 <CoreImage/CIImage.h>.
 The specified color space is used to render the image. If no color space is specified, no color mathcing is done. */
+ (CIImageAccumulator *)imageAccumulatorWithExtent:(CGRect)extent
											format:(CIFormat)format;
+ (CIImageAccumulator *)imageAccumulatorWithExtent:(CGRect)extent
											format:(CIFormat)format
										colorSpace:(CGColorSpaceRef)colorSpace
AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

- (id)initWithExtent:(CGRect)extent format:(CIFormat)format;
- (id)initWithExtent:(CGRect)extent
			  format:(CIFormat)format
		  colorSpace:(CGColorSpaceRef)colorSpace
AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

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

/* Reset the accumulator, discarding any pending updates and current content. */
- (void)clear;

@end
