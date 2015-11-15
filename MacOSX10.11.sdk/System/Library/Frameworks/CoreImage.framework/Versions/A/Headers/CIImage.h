/* 
   CoreImage - CIImage.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved. 
*/

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>
#if !TARGET_OS_IPHONE
#import <IOSurface/IOSurface.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif

@class CIContext, CIFilterShape, CIColor, CIFilter;

@protocol MTLTexture;

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIImage : NSObject <NSSecureCoding, NSCopying>
{
#if !TARGET_OS_IPHONE
    void *_state;
#endif
	void *_priv;
}

/* Pixel formats. */

typedef int CIFormat;

CORE_IMAGE_EXPORT CIFormat kCIFormatARGB8 NS_AVAILABLE(10_4, 6_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatBGRA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatABGR8 NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA16 NS_AVAILABLE_MAC(10_4);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAf NS_AVAILABLE(10_4, 7_0);

/* RGBA values that are IEEE 754-2008 half float compliant. */
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAh NS_AVAILABLE(10_4, 6_0);


CORE_IMAGE_EXPORT CIFormat kCIFormatA8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatA16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatAh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatAf NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatR8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatR16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRf NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRG8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRG16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGf NS_AVAILABLE(10_11, 9_0);


/* Image options dictionary keys. 
   These keys can be passed with appropriate values to the methods:
     + [CIImage imageWith... options:]
     - [CIImage initWith... options:]
   to modify the default behavior of how CIImages are created.
*/

/* A CGColorSpaceRef defining the color space of the image. This value 
 * overrides the image's implicit color space. 
 * If [NSNull null] then dont color manage the image. */
CORE_IMAGE_EXPORT NSString * const kCIImageColorSpace;


/* A NSDictionary of metadata properties to pass to CIImage initialization methods.
 * When used with imageWithCGImage:options:, initWithCGImage:options:, imageWithData:options:, initWithData:options:
 *   If this option is not specified, the properties will be set to CGImageSourceCopyPropertiesAtIndex.
 *   If this option is [NSNull null], the properties will be set to nil.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageProperties NS_AVAILABLE(10_8, 5_0);

CORE_IMAGE_EXPORT NSString * const kCIImageTextureTarget NS_AVAILABLE_MAC(10_9);
CORE_IMAGE_EXPORT NSString * const kCIImageTextureFormat NS_AVAILABLE_MAC(10_9);


/* Creates a new image from the contents of 'image'. */
+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options;

/* Creates a new image from the contents of 'layer'. */
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer NS_DEPRECATED_MAC(10_4,10_11);
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_DEPRECATED_MAC(10_4,10_11);

/* Creates a new image whose bitmap data is from 'data'. Each row contains 'bytesPerRow'
 * bytes. The dimensions of the image are defined by 'size'. 'format' defines
 * the format and size of each pixel. 'colorSpace' defines the color space
 * that the image is defined in, if nil, the image is not color matched. */
+ (CIImage *)imageWithBitmapData:(NSData *)data
                     bytesPerRow:(size_t)bytesPerRow
                            size:(CGSize)size
                          format:(CIFormat)format
                      colorSpace:(nullable CGColorSpaceRef)colorSpace;

/* Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flipped' is true, then the contents of the texture are
 * flipped vertically when referenced. 'colorSpace' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.*/
+ (CIImage *)imageWithTexture:(unsigned int)name
                         size:(CGSize)size
                      flipped:(BOOL)flipped
                   colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_4, 6_0);

/* In the options dictionary you can specify the following:
 * - kCIImageColorSpace which should be a CGColorSpaceRef or [NSNull null]
 * - kCIImageTextureTarget which should be a NSNumber with either GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB.
 * - kCIImageTextureFormat which should be a NSNumber with a CIFormat value
 */
+ (CIImage *)imageWithTexture:(unsigned int)name
                         size:(CGSize)size
					  flipped:(BOOL)flipped
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_9);

+ (CIImage *)imageWithMTLTexture:(id<MTLTexture>)texture
                         options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 9_0);

+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url;
+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url
                                     options:(nullable CI_DICTIONARY(NSString*,id) *)options;

+ (nullable CIImage *)imageWithData:(NSData *)data;
+ (nullable CIImage *)imageWithData:(NSData *)data
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_4, 9_0);

/* Creates a new image whose data is from the contents of a CVPixelBufferRef. */
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 5_0);

/* Creates a new image from the contents of an IOSurface. */
#if !TARGET_OS_IPHONE
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE_MAC(10_6);
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_6);
#endif

/* Return or initialize a new image with an infinite amount of the color
 * 'color'. */
+ (CIImage *)imageWithColor:(CIColor *)color;

/* Create an empty Image. */
+ (CIImage *)emptyImage;

/* Initializers. */

- (instancetype)initWithCGImage:(CGImageRef)image;
- (instancetype)initWithCGImage:(CGImageRef)image
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options;

- (instancetype)initWithCGLayer:(CGLayerRef)layer
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage: instead.");
- (instancetype)initWithCGLayer:(CGLayerRef)layer
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage:options instead.");

- (nullable instancetype)initWithData:(NSData *)data;
- (nullable instancetype)initWithData:(NSData *)data
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options;

- (instancetype)initWithBitmapData:(NSData *)data
                       bytesPerRow:(size_t)bytesPerRow
                              size:(CGSize)size
                            format:(CIFormat)format
                        colorSpace:(nullable CGColorSpaceRef)colorSpace;

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                     colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_4, 6_0);

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_9);

- (instancetype)initWithMTLTexture:(id<MTLTexture>)texture
                           options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 9_0);

- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url
                                       options:(nullable CI_DICTIONARY(NSString*,id) *)options;

#if !TARGET_OS_IPHONE
- (instancetype)initWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE_MAC(10_6);

- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                          options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_6);

- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                            plane:(size_t)plane
                           format:(CIFormat)format
                          options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_DEPRECATED_MAC(10_9,10_11);
#endif

- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_4, 9_0);

- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 5_0);

- (instancetype)initWithColor:(CIColor *)color;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */
- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* Returns a new image representing the original image with a transform
 * appied to it based on an orientation value.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns original image if the image is of infinite extent. */
- (CIImage *)imageByApplyingOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Returns a CGAffineTransform for an orientation value that can be appied to an image.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns CGAffineTransformIdentity if the image is of infinite extent.*/
- (CGAffineTransform)imageTransformForOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Return a new image formed by compositing the receiver image over 'dest'. */
- (CIImage *)imageByCompositingOverImage:(CIImage *)dest NS_AVAILABLE(10_4, 8_0);

/* Return a new image cropped to a rectangle. */
- (CIImage *)imageByCroppingToRect:(CGRect)rect;

/* Return a new infinte image by replicating the pixels of the receiver image's extent. */
- (CIImage *)imageByClampingToExtent NS_AVAILABLE(10_10, 8_0);

/* A convenience method for applying a filter to an image.
 * The method returns outputImage of the filter after setting the
 * filter's inputImage to the method receiver and other parameters
 * from from the key/value pairs of 'params'. */
- (CIImage *)imageByApplyingFilter:(NSString *)filterName
               withInputParameters:(nullable CI_DICTIONARY(NSString*,id) *)params NS_AVAILABLE(10_10, 8_0);


/* Return a rect the defines the bounds of non-(0,0,0,0) pixels */
@property (NS_NONATOMIC_IOSONLY, readonly) CGRect extent;

/* Returns the metadata properties of an image. If the image is the
 * output of one or more CIFilters, then the metadata of the root inputImage
 * will be returned. See also kCIImageProperties. */
@property (atomic, readonly) CI_DICTIONARY(NSString*,id) *properties NS_AVAILABLE(10_8, 5_0);

/* Return the Domain of Definition of the image. */
@property (atomic, readonly) CIFilterShape *definition NS_AVAILABLE_MAC(10_4);

/* Returns the URL of the image when the image was created using the imageWithContentsOfURL APIs.
 * This method will return nil, if the URL cannot be determined. */
@property (atomic, readonly, nullable) NSURL *url NS_AVAILABLE(10_4, 9_0);

/* Returns if possible the color space of the image it was defined in.
 * This method will return nil, if the color space cannot be determined. */
@property (atomic, readonly, nullable) CGColorSpaceRef colorSpace NS_AVAILABLE(10_4, 9_0) CF_RETURNS_NOT_RETAINED;

/* Returns the rectangle of 'image' that is required to render the
 * rectangle 'rect' of the receiver.  This may return a null rect. */
- (CGRect)regionOfInterestForImage:(CIImage *)image
                            inRect:(CGRect)rect NS_AVAILABLE(10_11, 6_0);

@end


@interface CIImage (AutoAdjustment)

/* Image auto adjustment keys. */

/* These are the options dictionary keys which can be specified when calling 
 * the autoAdjustmentFiltersWithOptions: method.
 */

/* If CFBoolean value is false then dont attempt to apply enhancement filters.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustEnhance NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then dont attempt to apply red eye filter.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustRedEye NS_AVAILABLE(10_8, 5_0);

/* If value is an array of detected CIFeatures, then use these features
 * to determine the AutoAdjustEnhance and or AutoAdjustRedEye filters.
 * If not specified, receiver will call CIDetector.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustFeatures NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then don't attempt to apply crop filter.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustCrop NS_AVAILABLE(10_10, 8_0);

/* If CFBoolean value is false then don't attempt to apply auto-level.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustLevel NS_AVAILABLE(10_10, 8_0);


/* Return an array of filters to apply to an image to improve its
 * skin tones, saturation, contrast, shadows and repair red-eyes or LED-eyes.
 *
 * The options dictionary can contain a CIDetectorImageOrientation key value. 
 * The value for this key is an integer NSNumber from 1..8 such as that
 * found in kCGImagePropertyOrientation.  If present, the adjustment will be done
 * based on that orientation but any coordinates in the returned filters will
 * still be based on those of the sender image.
 */
- (CI_ARRAY(CIFilter *) *)autoAdjustmentFiltersWithOptions:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_8, 5_0);

@end

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
