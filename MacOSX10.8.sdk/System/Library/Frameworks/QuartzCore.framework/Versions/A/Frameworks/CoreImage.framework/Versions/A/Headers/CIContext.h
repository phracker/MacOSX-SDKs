/* CoreImage - CIContext.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <CoreImage/CIImage.h>
#import <CoreImage/CoreImageDefines.h>
#import <OpenGL/CGLTypes.h>


@class CIFilter;

CORE_IMAGE_CLASS_EXPORT
@interface CIContext : NSObject
{
    id _priv;
}

/* Keys that may be passed in the dictionary while creating contexts: */

/* A CGColorSpaceRef object defining the color space that images are
 * converted to before rendering into the context. */
CORE_IMAGE_EXPORT NSString * const kCIContextOutputColorSpace AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* A CGColorSpaceRef object defining the color space in which all
 * intermediate operations are performed. */
CORE_IMAGE_EXPORT NSString * const kCIContextWorkingColorSpace AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* An NSNumber with a boolean value. In CICGContext, requires software
 * rendering when true. */
CORE_IMAGE_EXPORT NSString * const kCIContextUseSoftwareRenderer AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Create a new CoreImage context object, all output will be drawn
 * into the surface attached to the OpenGL context 'ctx'. If 'pf' is
 * non-null it should be the pixel format object used to create 'ctx';
 * it's required to be valid for the lifetime of the CIContext.
 * The colorspace should be set to the colorspace of your target otherwise
 * CI will take the colorspace from the CGLContext if available. */
+ (CIContext *)contextWithCGLContext:(CGLContextObj)ctx
						 pixelFormat:(CGLPixelFormatObj)pf
						  colorSpace:(CGColorSpaceRef)cs
							 options:(NSDictionary *)dict AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* DEPRECATED, please use contextWithCGLContext:pixelFormat:colorSpace:options: */
+ (CIContext *)contextWithCGLContext:(CGLContextObj)ctx
						 pixelFormat:(CGLPixelFormatObj)pf
							 options:(NSDictionary *)dict
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;

/* Create a new CoreImage context object, all output will be drawn
 * into the CG context 'ctx'. */
+ (CIContext *)contextWithCGContext:(CGContextRef)ctx
							options:(NSDictionary *)dict;

/* DEPRECATED, please use the drawImage:inRect:fromRect: instead.
 * Render the subregion 'src' of 'im' to point 'p' in the context's destination. */
- (void)drawImage:(CIImage *)im atPoint:(CGPoint)p fromRect:(CGRect)src
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_8;

/* Render the rectangle 'src' of 'im' to the rectangle 'dest' in the
 * context's destination. */
- (void)drawImage:(CIImage *)im inRect:(CGRect)dest fromRect:(CGRect)src;

/* Render the region 'r' of image 'im' into a temporary buffer using
 * the context, then create and return a new CoreGraphics image with
 * the results. The caller is responsible for releasing the returned
 * image. */
- (CGImageRef)createCGImage:(CIImage *)im fromRect:(CGRect)r
CF_RETURNS_RETAINED;

/* Create a new CGImage from the specified subrect of the image. If
 * non-nil the new image will be created in the specified format and
 * colorspace. */
- (CGImageRef)createCGImage:(CIImage *)im fromRect:(CGRect)r
					 format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs
CF_RETURNS_RETAINED;

/* Create a CoreGraphics layer object suitable for creating content for
 * subsequently rendering into this CI context. The 'd' parameter is
 * passed into CGLayerCreate () as the auxiliaryInfo dictionary. */
- (CGLayerRef)createCGLayerWithSize:(CGSize)size info:(CFDictionaryRef)d;

/* Render to the given bitmap. Null colorspace means to use the context's
   output colorspace. */
- (void)render:(CIImage *)im
	  toBitmap:(void *)data
	  rowBytes:(ptrdiff_t)rb
		bounds:(CGRect)r
		format:(CIFormat)f
	colorSpace:(CGColorSpaceRef)cs;

/* Render to the given IOSurface. */
- (void)render:(CIImage *)im
   toIOSurface:(IOSurfaceRef)surface
		bounds:(CGRect)r
	colorSpace:(CGColorSpaceRef)cs
AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Runs the context's garbage collector to reclaim any resources that
 * are no longer required (e.g. removes textures from the texture cache
 * that reference deleted images.) This method is called automatically
 * after every rendering operation. */
- (void)reclaimResources;

/* Frees any cached data (such as temporary images) associated with the
 * context. This also runs the garbage collector. */
- (void)clearCaches;

@end
