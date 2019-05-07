//
//  MPSImageTypes.h
//  MPS
//
//  Created by Ian Ollmann on 8/20/16.
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef MPSImageTypes_h
#define MPSImageTypes_h

#import <MPSCore/MPSCoreTypes.h>


#ifdef __cplusplus
extern "C" {
#endif

    

/*! @typedef MPSAlphaType
 *  @abstract Premultiplication description for the color channels of a texture
 *  @discussion Some image data is premultiplied. That is to say that the color channels
 *              are stored instead as color * alpha. This is an optimization for image compositing
 *              (alpha blending), but it can get in the way of most other image filters,
 *              especially those that apply non-linear affects like the MPSImageParametricCurveTransform
 *              multidimensional lookup tables, and functions like convolution or resampling filters
 *              that look at adjacent pixels, where the alpha may not be the same.
 *  @code
 *              Some basic conversion cases:
 *                  source                              destination                         operation
 *                  ------                              -----------                         ---------
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypeNonPremultiplied        <none>
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypeAlphaIsOne              composite with opaque background color
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypePremultiplied           multiply color channels by alpha
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypeNonPremultiplied        set alpha to 1
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypeAlphaIsOne              set alpha to 1
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypePremultiplied           set alpha to 1
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypeNonPremultiplied        divide color channels by alpha
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypeAlphaIsOne              composite with opaque background color
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypePremultiplied           <none>
 *  @endcode
 *
 *              Color space conversion operations require the format to be either MPSPixelAlpha_NonPremultiplied or
 *              MPSPixelAlpha_AlphaIsOne to work correctly. A number of MPSKernels have similar requirements. If
 *              premultiplied data is provided or requested, extra operations will be added to the conversion to
 *              ensure correct operation. Fully opaque images should use MPSAlphaTypeAlphaIsOne.
 *
 *  @constant   MPSAlphaTypeNonPremultiplied   Image is not premultiplied by alpha. Alpha is not guaranteed to be 1. (kCGImageAlphaFirst/Last)
 *  @constant   MPSAlphaTypeAlphaIsOne         Alpha is guaranteed to be 1, even if it is not encoded as 1 or not encoded at all. (kCGImageAlphaNoneSkipFirst/Last, kCGImageAlphaNone)
 *  @constant   MPSAlphaTypePremultiplied      Image is premultiplied by alpha. Alpha is not guaranteed to be 1. (kCGImageAlphaPremultipliedFirst/Last)
 */

#if defined(DOXYGEN)
typedef enum MPSAlphaType
#else
typedef NS_ENUM( NSUInteger, MPSAlphaType )
#endif
{
    MPSAlphaTypeNonPremultiplied   MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0)) MPS_SWIFT_NAME(nonPremultiplied)  = 0,
    MPSAlphaTypeAlphaIsOne         MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))  = 1,
    MPSAlphaTypePremultiplied      MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(10.0), tvos(10.0))  = 2
}
#if defined(DOXYGEN)
    MPSAlphaType
#endif
;
    

#ifdef __cplusplus
}
#endif

#endif /* MPSImageTypes_h */
