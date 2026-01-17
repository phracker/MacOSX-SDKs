/* CoreImage - CIKernel.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif

/* Block callback used by Core Image to ask what rectangles of a kernel's input images
 * are needed to produce a desired rectangle of the kernel's output image.
 *
 * 'index' is the 0-based index specifying which of the kernel's input images is being queried.
 * 'destRect' is the extent rectangle of kernel's output image being queried.
 *
 * Returns the rectangle of the index'th input image that is needed to produce destRect.
 * Returning CGRectNull indicates that the index'th input image is not needed to produce destRect.
 * The returned rectangle need not be contained by the extent of the index'th input image.
 */
typedef CGRect (^CIKernelROICallback)(int index, CGRect destRect);


@class CIImage;


/*
 * CIKernel is an object that encapsulates a Core Image Kernel Language
 * routine that generates a new images based on input images and agruments.
 *
 * General kernels functions are declared akin to this example:
 *   kernel vec4 myColorKernel (sampler fore, sampler back, vec4 params)
 *
 * The function must take a sampler argument for each input image.
 * Additional arguments can be of type float, vec2, vec3, vec4, or __color.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should call sample() with coordinates based on either
 * samplerCoord() or samplerTransform() to read pixel values from input images.
 * The function must return a vec4 pixel color.
 */
NS_CLASS_AVAILABLE(10_4, 8_0)
@interface CIKernel : NSObject
{
    void *_priv;
}

/* The string argument should contain a program in the Core Image Kernel Language.
 * All the kernel functions in the program are converted to instances of a CIKernel objects
 * and returned in an array.
 * On OSX 10.10 and before, the array will contain instances of CIKernel class.
 * On OSX after 10.10, the array will contain instances of CIKernel, CIColorKernel or CIWarpKernel classes.
 * On iOS, the array will contain instances of CIKernel, CIColorKernel or CIWarpKernel classes.
 */
+ (nullable CI_ARRAY(CIKernel*) *)kernelsWithString:(NSString *)string  NS_AVAILABLE(10_4, 8_0);

/* The string argument should contain a program with one kernel.
 * On OSX 10.10 and before, this returns a CIKernel object.
 * On OSX after 10.10, this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

/* The name of the kernel. */
@property (atomic, readonly) NSString *name  NS_AVAILABLE(10_4, 8_0);

/* Sets the selector used by Core Image to ask what rectangles of a kernel's input images
 * are needed to produce a desired rectangle of the kernel's output image.
 *
 * Using setROISelector: is suppoted but not recommended.
 * The selector is only used if one the [CIFilter apply:...] methods is used.
 * Instead, use one of the [CIKernel applyWithExtent:roiCallback:...] methods.
 *
 * The method should have one of the following signatures:
 *  - (CGRect)regionOf:(int)samplerIndex destRect:(CGRect)r userInfo:obj;
 *  - (CGRect)regionOf:(int)samplerIndex destRect:(CGRect)r;
 *
 * 'samplerIndex' is the 0-based index specifying which of the kernel's input images is being queried.
 * 'destRect' is the extent rectangle of kernel's output image being queried.
 * 'userInfo' is the object associated with the kCIApplyOptionUserInfo when the kernel was applied.
 *
 * The method should return the rectangle of the index'th input image that is needed to produce destRect.
 * Returning CGRectNull indicates that the index'th input image is not needed to produce destRect.
 */
- (void)setROISelector:(SEL)method  NS_AVAILABLE(10_4, 9_0);

/* Apply the receiver CIKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all non-clear pixels produced by the kernel.
 *
 * The 'callback' is a block that should return the rectangle of each input image
 * that is needed to produce a given rectangle in the coordinate space of the
 * new image.
 *
 * The 'args' is an array of parameters needed to describe the new image.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a sampler,
 * then the first object in the array must be a CIImage.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                          roiCallback:(CIKernelROICallback)callback
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end



/*
 * CIColorKernel is an object that encapsulates a Core Image Kernel Language
 * routine that processes only the color information in images.
 *
 * Color kernels functions are declared akin to this example:
 *   kernel vec4 myColorKernel (__sample fore, __sample back, vec4 params)
 *
 * The function must take a __sample argument for each input image.
 * Additional arguments can be of type float, vec2, vec3, vec4, or __color.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), sampleCoord(), or samplerTransform().
 * The function must return a vec4 pixel color.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface CIColorKernel : CIKernel
{
}

/* The string argument should contain a program with one color kernel.
 * On iOS8 [CIColorKernel kernelWithString:] can return a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS9 [CIColorKernel kernelWithString:] will return a CIColorKernel object or nil.
 * On OS X [CIColorKernel kernelWithString:] will return a CIColorKernel object or nil.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

/* Apply the receiver CIColorKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all non-clear pixels produced by the kernel.
 *
 * The 'args' is an array of parameters needed to describe the new image.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a __sample,
 * then the first object in the array must be a CIImage.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end


/*
 * CIWarpKernel is an object that encapsulates a Core Image Kernel Language
 * function that processes only the geometry of an image.
 *
 * Warp kernels functions are declared akin to this example:
 *   kernel vec2 myWarpKernel (vec4 params)
 *
 * Additional arguments can be of type float, vec2, vec3, vec4.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), sampleCoord(), or samplerTransform().
 * The function must return a vec2 source location.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface CIWarpKernel : CIKernel
{
}

/* The string argument should contain a program with one warp kernel.
 * On iOS8 [CIWarpKernel kernelWithString:] can return a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS9 [CIWarpKernel kernelWithString:] will return a CIWarpKernel object or nil.
 * On OS X [CIWarpKernel kernelWithString:] will return a CIWarpKernel object or nil.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

/* Apply the receiver CIWarpKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all pixel coordinates that are warped by the
 * kernel to fall within the extent of 'image'.
 *
 * The 'image' is the input image that will be warped into a new image.
 *
 * The 'callback' is a block that should return the rectangle of the input image
 * that is needed to produce a given rectangle in the coordinate space of the
 * new image.
 *
 * The 'args' is an array of parameters needed to describe the warping function.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a vec3,
 * then the first object in the array must be a CIVector of count 3.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                          roiCallback:(CIKernelROICallback)callback
                           inputImage:(CIImage*)image
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
