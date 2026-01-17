/* CoreImage - CIImage.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <ApplicationServices/ApplicationServices.h>
#import <CoreVideo/CoreVideo.h>
#import <IOSurface/IOSurface.h>



@class NSData, NSURL, NSDictionary;

@class CIContext, CIFilterShape, CIColor;

CORE_IMAGE_CLASS_EXPORT
@interface CIImage : NSObject <NSCoding, NSCopying>
{
    __strong void *_state;
    void *_priv;
}

/* Pixel formats. */

typedef int CIFormat;

CORE_IMAGE_EXPORT CIFormat kCIFormatARGB8 __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA16 __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAf __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* RGBA values that are IEEE 754-2008 half float compliant. */
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAh __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Image dictionary keys. */

/* A CGColorSpaceRef defining the color space of the image. This value 
 * overrides the image's implicit color space. 
 * If [NSNull null] then dont color manage the image. */
CORE_IMAGE_EXPORT NSString *kCIImageColorSpace;

/* A NSDictionary of metadata properties to pass to CIImage initialization methods.
 * When used with imageWithCGImage:options:, initWithCGImage:options:, imageWithData:options:, initWithData:options:
 *   If this option is not specified, the properties will be set to CGImageSourceCopyPropertiesAtIndex.
 *   If this option is [NSNull null], the properties will be set to nil.
 */
CORE_IMAGE_EXPORT NSString *kCIImageProperties __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* Creates a new image from the contents of 'image'. */
+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

/* Creates a new image from the contents of 'layer'. */
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Creates a new image whose bitmap data is from 'd'. Each row contains 'bpr'
 * bytes. The dimensions of the image are defined by 'size'. 'f' defines
 * the format and size of each pixel. 'cs' defines the color space
 * that the image is defined in, if nil, the image is not color matched. */
+ (CIImage *)imageWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr
 size:(CGSize)size format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs;

/* Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flag' is true, then the contents of the texture are
 * flipped vertically when referenced. 'cs' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.*/
+ (CIImage *)imageWithTexture:(unsigned int)name size:(CGSize)size
 flipped:(BOOL)flag colorSpace:(CGColorSpaceRef)cs __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

+ (CIImage *)imageWithContentsOfURL:(NSURL *)url;
+ (CIImage *)imageWithContentsOfURL:(NSURL *)url options:(NSDictionary *)d;

+ (CIImage *)imageWithData:(NSData *)data;
+ (CIImage *)imageWithData:(NSData *)data options:(NSDictionary *)d;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
 options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Creates a new image whose data is from the contents of a CVPixelBufferRef. */
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)buffer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)buffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/* Creates a new image from the contents of an IOSurface. */
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface
AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface options:(NSDictionary *)d
AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Return or initialize a new image with an infinite amount of the color
 * 'color'. */
+ (CIImage *)imageWithColor:(CIColor *)color;

/* Create an empty Image. */
+ (CIImage *)emptyImage;

/* Initializers. */

- (id)initWithCGImage:(CGImageRef)image;
- (id)initWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

- (id)initWithCGLayer:(CGLayerRef)layer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
- (id)initWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

- (id)initWithData:(NSData *)data;
- (id)initWithData:(NSData *)data options:(NSDictionary *)d;

- (id)initWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr size:(CGSize)size 
format:(CIFormat)f colorSpace:(CGColorSpaceRef)c;

- (id)initWithTexture:(unsigned int)name size:(CGSize)size flipped:(BOOL)flag colorSpace:(CGColorSpaceRef)cs __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

- (id)initWithContentsOfURL:(NSURL *)url;
- (id)initWithContentsOfURL:(NSURL *)url options:(NSDictionary *)d;

- (id)initWithIOSurface:(IOSurfaceRef)surface __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
- (id)initWithIOSurface:(IOSurfaceRef)surface options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

- (id)initWithCVPixelBuffer:(CVPixelBufferRef)buffer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
- (id)initWithCVPixelBuffer:(CVPixelBufferRef)buffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

- (id)initWithColor:(CIColor *)color;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */
- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* Return a new image cropped to the rectangle or shape. */
- (CIImage *)imageByCroppingToRect:(CGRect)r;

/* Return a rect the defines the bounds of non-(0,0,0,0) pixels */
- (CGRect)extent;

/* Returns the metadata properties of an image. If the image is the
 * output of one or more CIFilters, then the metadata of the root inputImage
 * will be returned. See also kCIImageProperties. */
- (NSDictionary*)properties __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* Return the Domain of Definition of the image. */
- (CIFilterShape *)definition __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Returns the URL of the image when the image was created using the imageWithContentsOfURL APIs.
 * This method will return nil, if the URL cannot be determined. */
- (NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Returns if possible the color space of the image it was defined in.
 * This method will return nil, if the color space cannot be determined. */
- (CGColorSpaceRef)colorSpace __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

@end

@interface CIImage (AutoAdjustment)

/* Image auto adjustment keys. */

/* These are the options dictionarey keys which can be specified when calling 
 * the autoAdjustmentFiltersWithOptions: method.
 */

/* If CFBoolean value is false then dont attempt to apply enhancement filters.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustEnhance __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* If CFBoolean value is false then dont attempt to apply red eye filter.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustRedEye __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* If value is an array of detected CIFeatures, then use these features
 * to determine the AutoAdjustEnhance and or AutoAdjustRedEye filters.
 * If not specified, reciever will call CIDetector.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustFeatures __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);


/* Return an array of filters to apply to an image to improve its 
 * skin tones, saturation, contrast, shadows and repair red-eyes or LED-eyes.
 *
 * The options dictionary can contain a CIDetectorImageOrientation key value. 
 * The value for this key is an integer NSNumber from 1..8 such as that
 * found in kCGImagePropertyOrientation.  If present, the adjustment will be done
 * based on that orientation but any coordinates in the returned filters will
 * still be based on those of the sender image.
 */
- (NSArray *)autoAdjustmentFilters __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);
- (NSArray *)autoAdjustmentFiltersWithOptions:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

@end
