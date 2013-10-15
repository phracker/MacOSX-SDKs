/* CoreImage - CISampler.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSDictionary;
@class CIFilterShape, CIImage;

@interface CISampler : NSObject <NSCopying>
{
    void *_priv;
}

/* Creates a new sampler object refencing 'im'. */

+ (CISampler *)samplerWithImage:(CIImage *)im;

/* Creates a new sampler object from 'im' specifying key/value option
 * pairs. Each key is an NSString. Supported keys include:
 *
 * kCISamplerAffineMatrix: An NSArray [a b c d tx ty] defining the
 * transformation to be applied to the sampler.
 *
 * kCISamplerWrapMode: An NSString defining how pixels outside the
 * sampler's extent are produced. Options include kCISamplerWrapBlack
 * (pixels are transparent black, the default) and kCISamplerWrapClamp
 * (coordinates are clamped to the extent).
 *
 * kCISamplerFilterMode: An NSString defining the filter to use when
 * sampling the image. One of kCISamplerFilterNearest (point sampling)
 * or kCISamplerFilterLinear (bilinear interpolation, the default). */

+ (CISampler *)samplerWithImage:(CIImage *)im keysAndValues:key0, ...;
+ (CISampler *)samplerWithImage:(CIImage *)im options:(NSDictionary *)dict;

/* Initializers. */

- (id)initWithImage:(CIImage *)im;
- (id)initWithImage:(CIImage *)im keysAndValues:key0, ...;
- (id)initWithImage:(CIImage *)im options:(NSDictionary *)dict;

/* Returns the shape containing the Domain Of Definition (DOD) of the
 * sampler. The DOD is defined such that it contains all non-transparent
 * pixels produced by referencing the sampler. */

- (CIFilterShape *)definition;

/* Returns the extent of the sampler. Sampling outside the extent will
 * bring the sampler's wrap mode into action. */

- (CGRect)extent;

@end


/* Sampler options. */

extern NSString *kCISamplerAffineMatrix AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCISamplerWrapMode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCISamplerFilterMode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern NSString *kCISamplerWrapBlack, *kCISamplerWrapClamp AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCISamplerFilterNearest, *kCISamplerFilterLinear AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
