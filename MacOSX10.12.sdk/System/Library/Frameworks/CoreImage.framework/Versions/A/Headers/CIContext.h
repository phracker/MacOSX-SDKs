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

/* A boolean NSNumber controlling the quality of affine downsample operations.
 * @YES implies that more quality is desired.
 * On iOS the default value is @NO.
 * On OSX the default value is @YES. */
CORE_IMAGE_EXPORT NSString * const kCIContextHighQualityDownsample NS_AVAILABLE(10_11,9_0);

/* A boolean NSNumber controlling whether output renders produce alpha-premultiplied pixels.
 * The default value is @YES. */
CORE_IMAGE_EXPORT NSString * const kCIContextOutputPremultiplied NS_AVAILABLE(10_4,7_0);

/* A boolean NSNumber controlling how intermediate buffers are cached.
 * If @NO, the context will empty intermediates during and after renders.
 * The default value is @YES. */
CORE_IMAGE_EXPORT NSString * const kCIContextCacheIntermediates NS_AVAILABLE(10_12,10_0);

/* An NSNumber with a boolean value. When @YES the context will use
 * software rendering. */
CORE_IMAGE_EXPORT NSString * const kCIContextUseSoftwareRenderer;

/* An NSNumber with a boolean value. When @YES the context will use 
 * low priority rendering on the GPU. */
CORE_IMAGE_EXPORT NSString * const kCIContextPriorityRequestLow NS_AVAILABLE(10_12, 8_0);


#pragma mark - contextWithCGLContext

/* Create a new CoreImage context object, all output will be drawn
 * into the surface attached to the OpenGL context 'cglctx'. If 'pixelFormat' is
 * non-null it should be the pixel format object used to create 'cglctx';
 * it's required to be valid for the lifetime of the CIContext.
 * The colorspace should be set to the colorspace of your target otherwise
 * CI will take the colorspace from the CGLContext if available. */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
						  colorSpace:(nullable CGColorSpaceRef)colorSpace
							 options:(nullable NSDictionary<NSString*,id> *)options
    NS_AVAILABLE_MAC(10_6);
#endif

/* DEPRECATED, please use the method above or if you need this
* for backward capability, make sure that you specify the colorspace
* in the options dictionary */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
							 options:(nullable NSDictionary<NSString*,id> *)options
    NS_DEPRECATED_MAC(10_4,10_6);
#endif


#pragma mark - contextWithCGContext

/* Create a context specifying a destination CGContext.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will render to the CGContext.
 */
+ (CIContext *)contextWithCGContext:(CGContextRef)cgctx
                            options:(nullable NSDictionary<NSString*,id> *)options
    NS_AVAILABLE(10_4,9_0);


#pragma mark - context without specifying a destination

/* Create a context without specifying a destination CG/GL/Metal context.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will not operate on this type
 * of context.
 */

+ (CIContext *)contextWithOptions:(nullable NSDictionary<NSString*,id> *)options
    NS_AVAILABLE(10_4,5_0);

+ (CIContext *)context NS_AVAILABLE(10_4,5_0);

- (instancetype)initWithOptions:(nullable NSDictionary<NSString*,id> *)options
NS_AVAILABLE(10_4,5_0);

- (instancetype)init NS_AVAILABLE(10_4,5_0);


#pragma mark - contextWithEAGLContext

/* Create a context specifying a destination EAGLContext.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will render to the EAGLContext.
 */
#if TARGET_OS_IPHONE
+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
    NS_AVAILABLE_IOS(5_0);

+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
                              options:(nullable NSDictionary<NSString*,id> *)options
    NS_AVAILABLE_IOS(5_0);
#endif


#pragma mark - contextWithMTLDevice

/* If a system has more than one MTLDevice, then you can create a CIContext
 * that uses a specific device. If a client wishes to use the default MTLDevice
 * then call [CIContext contextWithOptions:] instead. */
+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device NS_AVAILABLE(10_11,9_0);

+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device
                            options:(nullable NSDictionary<NSString*,id> *)options
    NS_AVAILABLE(10_11,9_0);


#pragma mark - properties

// The working color space of the CIContext
// The property will be null if the context was created with color management disabled.
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
@property (nullable, nonatomic, readonly) CGColorSpaceRef workingColorSpace NS_AVAILABLE(10_11,9_0);
#else
@property (nonatomic, readonly) CGColorSpaceRef workingColorSpace NS_AVAILABLE(10_11,9_0);
#endif

// The working pixel format of the CIContext used for intermediate buffers
@property (nonatomic, readonly) CIFormat workingFormat NS_AVAILABLE(10_11,9_0);


#pragma mark - render methods

/* DEPRECATED, please use drawImage:inRect:fromRect: instead.
 * Render the subregion 'fromRect' of 'image' to point 'atPoint' in the context's destination. */
- (void)drawImage:(CIImage *)image
          atPoint:(CGPoint)atPoint
         fromRect:(CGRect)fromRect NS_DEPRECATED(10_4,10_8, 5_0,6_0);

/* Render the rectangle 'fromRect' of 'image' to the rectangle 'inRect' in the
 * context's destination. */
- (void)drawImage:(CIImage *)image
           inRect:(CGRect)inRect
         fromRect:(CGRect)fromRect;

/* Render the region 'fromRect' of image 'image' into a temporary buffer using
 * the context, then create and return a new CoreGraphics image with
 * the results. The caller is responsible for releasing the returned image.
 * The return value will be null if size is empty or too big. */
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
CF_RETURNS_RETAINED;
#else
- (CGImageRef)createCGImage:(CIImage *)image
                   fromRect:(CGRect)fromRect
CF_RETURNS_RETAINED;
#endif

/* Create a new CGImage from the specified subrect of the image. If
 * non-nil the new image will be created in the specified format and colorspace.
 * The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome
 * and must match the specified CIFormat.
 * This will return null if fromRect is empty or infinite or the format isn't supported.
 */
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
                              format:(CIFormat)format
                          colorSpace:(nullable CGColorSpaceRef)colorSpace
CF_RETURNS_RETAINED;
#else
- (CGImageRef)createCGImage:(CIImage *)image
                   fromRect:(CGRect)fromRect
                     format:(CIFormat)format
                 colorSpace:(nullable CGColorSpaceRef)colorSpace
CF_RETURNS_RETAINED;
#endif

/* Create a new CGImage from the specified subrect of the image.
 * The new CGImageRef will be created in the specified format and colorspace.
 * The return value will be null if fromRect is empty or infinite.
 * The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome
 * and must match the specified CIFormat.
 * This will return null if fromRect is empty or infinite or the format isn't supported.
 * If deferred is NO, then the CIImage will be rendered once when this method is called.
 * If deferred is YES, then the CIImage will be rendered whenever the CGImage is rendered.
 */
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
                              format:(CIFormat)format
                          colorSpace:(nullable CGColorSpaceRef)colorSpace
                            deferred:(BOOL)deferred
CF_RETURNS_RETAINED NS_AVAILABLE(10_12,10_0);
#else
- (CGImageRef)createCGImage:(CIImage *)image
                   fromRect:(CGRect)fromRect
                     format:(CIFormat)format
                 colorSpace:(nullable CGColorSpaceRef)colorSpace
                   deferred:(BOOL)deferred
CF_RETURNS_RETAINED NS_AVAILABLE(10_12,10_0);
#endif

/* Create a CoreGraphics layer object suitable for creating content for
 * subsequently rendering into this CI context. The 'info' parameter is
 * passed into CGLayerCreate () as the auxiliaryInfo dictionary.
 * This will return null if size is empty or infinite. */
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
- (nullable CGLayerRef)createCGLayerWithSize:(CGSize)size
                                        info:(nullable CFDictionaryRef)info
CF_RETURNS_RETAINED NS_DEPRECATED_MAC(10_4,10_11);
#else
- (CGLayerRef)createCGLayerWithSize:(CGSize)size
                               info:(nullable CFDictionaryRef)info
CF_RETURNS_RETAINED NS_DEPRECATED_MAC(10_4,10_11);
#endif

/* Render 'image' to the given bitmap.
 * Passing a 'colorSpace' value of null means:
 *   Disable output color management if app is linked against iOS SDK
 *   Disable output color management if app is linked against OSX 10.11 SDK or later
 *   Match to context's output color space if app is linked against OSX 10.10 SDK or earlier
 */
- (void)render:(CIImage *)image
	  toBitmap:(void *)data
	  rowBytes:(ptrdiff_t)rowBytes
		bounds:(CGRect)bounds
		format:(CIFormat)format
	colorSpace:(nullable CGColorSpaceRef)colorSpace;

#if !TARGET_OS_IPHONE
/* Render 'image' to the given IOSurface.
 * The 'bounds' parameter has the following behavior:
 *    The 'image' is rendered into 'surface' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'surface'.
 *      The 'bounds' acts like a clip rect to limit what region of 'surface' is modified.
 */
- (void)render:(CIImage *)image
   toIOSurface:(IOSurfaceRef)surface
		bounds:(CGRect)bounds
	colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE_MAC(10_6);
#endif

/* Render 'image' into the given CVPixelBuffer. 
 * In OS X 10.11.3 and iOS 9.3 and later
 *   CI will color match to the colorspace of the buffer.
 * otherwise
 *   CI will color match to the context's output colorspace.
 */
- (void)render:(CIImage *)image 
toCVPixelBuffer:(CVPixelBufferRef)buffer NS_AVAILABLE(10_11,5_0);

/* Render 'image' to the given CVPixelBufferRef.
 * The 'bounds' parameter has the following behavior:
 *    In OS X and iOS 9 and later:  The 'image' is rendered into 'buffer' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'buffer'.
 *      The 'bounds' acts like a clip rect to limit what region of 'buffer' is modified.
 *    In iOS 8 and earlier: The 'bounds' parameter acts to specify the region of 'image' to render.
 *      This region (regarless of its origin) is rendered at upper-left corner of 'buffer'.
 * If 'colorSpace' is nil, CI will not color match to the destination.
 */
- (void)render:(CIImage *)image
toCVPixelBuffer:(CVPixelBufferRef)buffer
        bounds:(CGRect)bounds
    colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,5_0);

/* Render 'bounds' of 'image' to a Metal texture, optionally specifying what command buffer to use.
 * Texture type must be MTLTexture2D.
 */
- (void)render:(CIImage *)image
  toMTLTexture:(id<MTLTexture>)texture
 commandBuffer:(nullable id<MTLCommandBuffer>)commandBuffer
        bounds:(CGRect)bounds
    colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,9_0);


#pragma mark -

/* Runs the context's garbage collector to reclaim any resources that
 * are no longer required (e.g. removes textures from the texture cache
 * that reference deleted images.) This method is called automatically
 * after every rendering operation. */
- (void)reclaimResources NS_AVAILABLE_MAC(10_4);

/* Frees any cached data (such as temporary images) associated with the
 * context. This also runs the garbage collector. */
- (void)clearCaches NS_AVAILABLE(10_4,10_0);

/* Returns the maximum dimension for input images that can be processed 
 * on the context. */
- (CGSize)inputImageMaximumSize NS_AVAILABLE_IOS(5_0);

/* Returns the maximum dimension for image that can be rendered 
 * on the context. */
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
 * shared with other GL resources.  The return value will be null if index is 
 * out of range (e.g. if the device has no offline GPUs).
 */
#if !TARGET_OS_IPHONE
#if !defined(SWIFT_CLASS_EXTRA) || (defined(SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH) && SWIFT_SDK_OVERLAY_COREIMAGE_EPOCH >= 2)
+ (nullable CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index NS_AVAILABLE_MAC(10_10);
+ (nullable CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index
                                         colorSpace:(nullable CGColorSpaceRef)colorSpace
                                            options:(nullable NSDictionary<NSString*,id> *)options
                                      sharedContext:(nullable CGLContextObj)sharedContext NS_AVAILABLE_MAC(10_10);
#else
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index NS_AVAILABLE_MAC(10_10);
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index
                               colorSpace:(nullable CGColorSpaceRef)colorSpace
                                  options:(nullable NSDictionary<NSString*,id> *)options
                            sharedContext:(nullable CGLContextObj)sharedContext NS_AVAILABLE_MAC(10_10);
#endif
#endif


@end

@interface CIContext (ImageRepresentation)

/* Render a CIImage to TIFF data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (nullable NSData*) TIFFRepresentationOfImage:(CIImage*)image
                                        format:(CIFormat)format
                                    colorSpace:(CGColorSpaceRef)colorSpace
                                       options:(NSDictionary*)options NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to JPEG data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality */
- (nullable NSData*) JPEGRepresentationOfImage:(CIImage*)image
                                    colorSpace:(CGColorSpaceRef)colorSpace
                                       options:(NSDictionary*)options NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to TIFF file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (BOOL) writeTIFFRepresentationOfImage:(CIImage*)image
                                  toURL:(NSURL*)url
                                 format:(CIFormat)format
                             colorSpace:(CGColorSpaceRef)colorSpace 
                                options:(NSDictionary*)options
                                  error:(NSError **)errorPtr NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to JPEG file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality */
- (BOOL) writeJPEGRepresentationOfImage:(CIImage*)image
                                  toURL:(NSURL*)url
                             colorSpace:(CGColorSpaceRef)colorSpace
                                options:(NSDictionary*)options
                                  error:(NSError **)errorPtr NS_AVAILABLE(10_12,10_0);


@end

NS_ASSUME_NONNULL_END
