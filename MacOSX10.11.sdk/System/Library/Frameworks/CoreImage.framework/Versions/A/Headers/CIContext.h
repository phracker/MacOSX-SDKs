/* CoreImage - CIContext.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CIImage.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>

#if TARGET_OS_IPHONE
 #import <OpenGLES/EAGL.h>
#else
 #import <OpenGL/CGLTypes.h>
#endif 

@class CIFilter;

@protocol MTLDevice, MTLTexture, MTLCommandBuffer;

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIContext : NSObject
{
    void *_priv;
}

/* Keys that may be passed in the dictionary while creating contexts: */

/* A CGColorSpaceRef object defining the color space that images are
 * converted to before rendering into the context. */
CORE_IMAGE_EXPORT NSString * const kCIContextOutputColorSpace;

/* A CGColorSpaceRef object defining the color space in which all
 * intermediate operations are performed. */
CORE_IMAGE_EXPORT NSString * const kCIContextWorkingColorSpace;

/* An NSNumber with a CIFormat value defining the pixel format to use for intermediate buffers.
* On iOS GPU the supported values for this key are RGBA8 and RGBAh. If not specified RGBA8 us used.
* On iOS CPU the only supported value for this key is RGBAf. If not specified RGBAf us used.
* On OSX GPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used.
* On OSX CPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used. */
CORE_IMAGE_EXPORT NSString * const kCIContextWorkingFormat NS_AVAILABLE(10_4,8_0);

/* An NSNumber with a boolean value. When @YES the context will use
 * software rendering. */
CORE_IMAGE_EXPORT NSString * const kCIContextUseSoftwareRenderer;

/* An NSNumber with a boolean value. When @YES the context will use 
 * low priority rendering on the GPU. */
CORE_IMAGE_EXPORT NSString * const kCIContextPriorityRequestLow NS_AVAILABLE_IOS(8_0);

/* Create a new CoreImage context object, all output will be drawn
 * into the surface attached to the OpenGL context 'ctx'. If 'pf' is
 * non-null it should be the pixel format object used to create 'ctx';
 * it's required to be valid for the lifetime of the CIContext.
 * The colorspace should be set to the colorspace of your target otherwise
 * CI will take the colorspace from the CGLContext if available. */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)ctx
						 pixelFormat:(nullable CGLPixelFormatObj)pf
						  colorSpace:(nullable CGColorSpaceRef)cs
							 options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE_MAC(10_6);
#endif

/* DEPRECATED, please use the method above or if you need this
* for backward capability, make sure that you specify the colorspace
* in the options dictionary */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)ctx
						 pixelFormat:(nullable CGLPixelFormatObj)pf
							 options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_DEPRECATED_MAC(10_4,10_6);
#endif

/* Create a new CoreImage context object, all output will be drawn
 * into the CG context 'ctx'. */
+ (CIContext *)contextWithCGContext:(CGContextRef)ctx
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_4,9_0);

+ (CIContext *)contextWithOptions:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_11,5_0);

#if TARGET_OS_IPHONE
/* Create a new CoreImage context object using 'eaglContext' 
 * Calls to drawImage:atPoint:fromRect: and drawImage:inRect:fromRect:
 * will draw directly though the context. */
+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
    NS_AVAILABLE_IOS(5_0);

+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE_IOS(5_0);
#endif

// If a system has more than one MTLDevice, then you can create a CIContext
// that uses a specific device. If a client wishes to use the default MTLDevice
// then call [CIContext contextWithOptions:] instead.
+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device NS_AVAILABLE(10_11,9_0);

+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_11,9_0);

/* DEPRECATED, please use drawImage:inRect:fromRect: instead.
 * Render the subregion 'src' of 'im' to point 'p' in the context's destination. */
- (void)drawImage:(CIImage *)im
          atPoint:(CGPoint)p
         fromRect:(CGRect)src NS_DEPRECATED(10_4,10_8, 5_0,6_0);

/* Render the rectangle 'src' of 'im' to the rectangle 'dest' in the
 * context's destination. */
- (void)drawImage:(CIImage *)im
           inRect:(CGRect)dest
         fromRect:(CGRect)src;

/* Render the region 'r' of image 'im' into a temporary buffer using
 * the context, then create and return a new CoreGraphics image with
 * the results. The caller is responsible for releasing the returned
 * image. */
- (CGImageRef)createCGImage:(CIImage *)im fromRect:(CGRect)r
CF_RETURNS_RETAINED;

/* Create a new CGImage from the specified subrect of the image. If
 * non-nil the new image will be created in the specified format and
 * colorspace. */
- (CGImageRef)createCGImage:(CIImage *)im
                   fromRect:(CGRect)r
                     format:(CIFormat)f
                 colorSpace:(nullable CGColorSpaceRef)cs
CF_RETURNS_RETAINED;

/* Create a CoreGraphics layer object suitable for creating content for
 * subsequently rendering into this CI context. The 'd' parameter is
 * passed into CGLayerCreate () as the auxiliaryInfo dictionary. */
- (CGLayerRef)createCGLayerWithSize:(CGSize)size
                               info:(nullable CFDictionaryRef)d
CF_RETURNS_RETAINED NS_DEPRECATED_MAC(10_4,10_11);

/* Render to the given bitmap. 
 * Passing a colorspace value of null means:
 *   Disable output color management if app is linked against iOS SDK
 *   Disable output color management if app is linked against OSX 10.11 SDK or later
 *   Match to context's output color space if app is linked against OSX 10.10 SDK or earlier
 */
- (void)render:(CIImage *)im
	  toBitmap:(void *)data
	  rowBytes:(ptrdiff_t)rb
		bounds:(CGRect)r
		format:(CIFormat)f
	colorSpace:(nullable CGColorSpaceRef)cs;

#if !TARGET_OS_IPHONE
/* Render to the given IOSurface. */
- (void)render:(CIImage *)im
   toIOSurface:(IOSurfaceRef)surface
		bounds:(CGRect)r
	colorSpace:(nullable CGColorSpaceRef)cs NS_AVAILABLE_MAC(10_6);
#endif

/* Render 'image' into a CVPixelBuffer using the context. */
- (void)render:(CIImage *)image 
toCVPixelBuffer:(CVPixelBufferRef)buffer NS_AVAILABLE(10_11,5_0);

- (void)render:(CIImage *)image 
toCVPixelBuffer:(CVPixelBufferRef)buffer
        bounds:(CGRect)r
    colorSpace:(nullable CGColorSpaceRef)cs NS_AVAILABLE(10_11,5_0);

// Render the bounds 'r' of 'image' to a Metal texture
// optionally specifying what command buffer to use.
- (void)render:(CIImage *)image
  toMTLTexture:(id<MTLTexture>)texture
 commandBuffer:(nullable id<MTLCommandBuffer>)cb
        bounds:(CGRect)r
    colorSpace:(CGColorSpaceRef)cs NS_AVAILABLE(10_11,9_0);

/* Runs the context's garbage collector to reclaim any resources that
 * are no longer required (e.g. removes textures from the texture cache
 * that reference deleted images.) This method is called automatically
 * after every rendering operation. */
- (void)reclaimResources NS_AVAILABLE_MAC(10_4);

/* Frees any cached data (such as temporary images) associated with the
 * context. This also runs the garbage collector. */
- (void)clearCaches NS_AVAILABLE_MAC(10_4);

/* Returns the maximum dimension for input images that can be processed 
 * on the currect context. */
- (CGSize)inputImageMaximumSize NS_AVAILABLE_IOS(5_0);

/* Returns the maximum dimension for image that can be rendered 
 * on the currect context. */
- (CGSize)outputImageMaximumSize NS_AVAILABLE_IOS(5_0);

@end


@interface CIContext (OfflineGPUSupport)

/* Not all GPUs will be driving a display. If they are offline we can still use them
 * to do work with Core Image. This method returns the number of offline GPUs which
 * can be used for this purpose */
+(unsigned int)offlineGPUCount NS_AVAILABLE_MAC(10_10);

/* These two methods lets you create a CIContext based on an offline gpu index.
 * The first method takes only the GPU index as a parameter, the second, takes
 * an optional colorspace, options dictionary and a CGLContext which can be
 * shared with other GL resources.
 */
#if !TARGET_OS_IPHONE
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index NS_AVAILABLE_MAC(10_10);
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index
                               colorSpace:(nullable CGColorSpaceRef)colorSpace
                                  options:(nullable CI_DICTIONARY(NSString*,id) *)options
                            sharedContext:(nullable CGLContextObj)sharedContext NS_AVAILABLE_MAC(10_10);
#endif


@end

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
