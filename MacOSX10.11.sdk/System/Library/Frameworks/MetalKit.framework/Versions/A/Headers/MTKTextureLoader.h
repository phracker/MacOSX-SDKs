/*!
 @header MTKTextureLoader.h
 @framework MetalKit
 @abstract MetalKit helper functionality for loading a Metal texture from image file data
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@protocol MTLDevice;
@protocol MTLTexture;

/*!
 @group MTKTextureLoaderErrors
 */

/*!
 @constant MTKTextureLoaderErrorDomain
 */
MTK_EXTERN NSString * __nonnull const MTKTextureLoaderErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant MTKTextureLoaderErrorKey
 */
MTK_EXTERN NSString * __nonnull const MTKTextureLoaderErrorKey NS_AVAILABLE(10_11, 9_0);


/*!
 @group MTKTextureLoaderOptions
 */

/*!
 @constant MTKTextureLoaderOptionAllocateMipmaps
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to allocate memory for mipmaps when creating the texture
 @discussion If the boolean value specified with this string is true, the resulting Metal texture will have been created with mipmaps whose contents are undefined. It is the responsibility of the caller to fill out the contents of the mipmap data. However, if the file being loaded contains data for mipmaps (such as in a PVR or KTX file) this option does need to be specified. In those cases the mipmap memory will be allocated and the image data loaded.
 */
MTK_EXTERN NSString * __nonnull const MTKTextureLoaderOptionAllocateMipmaps NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionSRGB
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to create the texture with an sRGB (gamma corrected) pixel format
 @discussion If the boolean value specified with this string is true, the texture will be created with an sRGB pixel format regardless of whether the image file specifies that the data has already been gamma corrected. Likewise, if false, the texture will be created with a non-sRGB pixel format regardless of whether the image file specifies that the data has been gamma corrected. To use the sRGB information specified in the file, do not specify this in the options dictionary.
 */
MTK_EXTERN NSString * __nonnull const MTKTextureLoaderOptionSRGB NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureUsage
 @abstract Identifier to be used with an NSNumber specifying the MTLTextureUsage flags
 @discussion The resulting Metal texture will be created with the texture usage flags indicated by the NSNumber associated with this string.
 */
MTK_EXTERN NSString * __nonnull const MTKTextureLoaderOptionTextureUsage NS_AVAILABLE(10_11, 9_0);

typedef void (^MTKTextureLoaderCallback) (id <MTLTexture> __nullable texture, NSError * __nullable error);

/*!
 @class MTKTextureLoader
 @abstract Load Metal textures from files with the device specified at initialization
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKTextureLoader : NSObject

/*!
 @property device
 @abstract Metal device with which to create Metal textures
 */
@property (nonatomic, readonly, nonnull) id <MTLDevice> device;

- (nonnull instancetype)init __unavailable;

/*!
 @method initWithDevice:
 @abstract Initialize the loader
 @param device Metal device with which to create Metal textures
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device;

/*!
 @method textureWithContentsOfURL:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the file at URL
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when the texture has been loaded and fully initialized
 */
- (void)textureWithContentsOfURL:(nonnull NSURL *)URL
                         options:(nullable NSDictionary <NSString *, NSNumber *> *)options
               completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method textureWithData:options:completionHandler:
 @abstract Asynchronously create a Metal texture load texture with given file data
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)textureWithData:(nonnull NSData *)data
                options:(nullable NSDictionary <NSString *, NSNumber *> *)options
      completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method textureWithCGImage:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from given CGImageRef
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)textureWithCGImage:(nonnull CGImageRef)cgImage
                   options:(nullable NSDictionary <NSString *, NSNumber *> *)options
         completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method textureWithContentsOfURL:options:error:
 @abstract Synchronously create a Metal texture and load image data from file at URL
 @return The Metal texture. nil if an error occured
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)textureWithContentsOfURL:(nonnull NSURL *)URL
                                             options:(nullable NSDictionary <NSString *, NSNumber *> *)options
                                               error:(NSError *__nullable *__nullable)error;

/*!
 @method textureWithData:options:error:
 @abstract Synchronously create a Metal texture and load with given file data
 @return The Metal texture. nil if an error occured
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)textureWithData:(nonnull NSData *)data
                                    options:(nullable NSDictionary <NSString *, NSNumber *> *)options
                                      error:(NSError *__nullable *__nullable)error;

/*!
 @method textureWithCGImage:options:error:
 @abstract Synchronously create a Metal texture and load image data from given CGImageRef
 @return The Metal texture. nil if an error occured
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)textureWithCGImage:(nonnull CGImageRef)cgImage
                                       options:(nullable NSDictionary <NSString *, NSNumber *> *)options
                                         error:(NSError *__nullable *__nullable)error;

@end
