/*!
 @header MTKTextureLoader.h
 @framework MetalKit
 @abstract MetalKit helper functionality for loading a Metal texture from image file data
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */
#import <TargetConditionals.h>
#import <MetalKit/MTKDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>



@protocol MTLDevice;
@protocol MTLTexture;
@class MDLTexture;

/*!
 @group MTKTextureLoaderErrors
 */

typedef NSString * MTKTextureLoaderError NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Error);

/*!
 @constant MTKTextureLoaderErrorDomain
 */
MTK_EXTERN MTKTextureLoaderError __nonnull const MTKTextureLoaderErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant MTKTextureLoaderErrorKey
 */
MTK_EXTERN MTKTextureLoaderError __nonnull const MTKTextureLoaderErrorKey NS_AVAILABLE(10_11, 9_0);

/*!
 @group MTKTextureLoaderOptions
 */

typedef NSString * MTKTextureLoaderOption NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Option);

/*!
 @constant MTKTextureLoaderOptionAllocateMipmaps
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to allocate memory for mipmaps when creating the texture
 @discussion If the boolean value specified with this string is true, the resulting Metal texture will have been created with mipmaps whose contents are undefined. It is the responsibility of the caller to fill out the contents of the mipmap data unless MTLTextureLoaderOptionGenerateMipmaps is specified. If the file being loaded contains data for mipmaps (such as in a PVR or KTX file) this option does not need to be specified. In those cases the mipmap memory will be allocated and the image data loaded.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionAllocateMipmaps NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionGenerateMipmaps
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to generate mipmaps when creating the texture
 @discussion If the boolean value specified with this string is true, the resulting Metal texture will be created with mipmaps. If the file being loaded contains data for mipmaps (such as in a PVR or KTX file), specifying this option will overwrite the existing mipmap data in the loaded texture. This option can only be used if the pixel format of the texture is color filterable and color renderable. This option implies MTKTextureLoaderOptionAllocateMipmaps. Specifying this option will cause the MTKTextureLoader to submit work to the GPU on behalf of the caller.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionGenerateMipmaps NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOptionSRGB
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to create the texture with an sRGB (gamma corrected) pixel format
 @discussion If the boolean value specified with this string is true, the texture will be created with an sRGB pixel format regardless of whether the image file specifies that the data has already been gamma corrected. Likewise, if false, the texture will be created with a non-sRGB pixel format regardless of whether the image file specifies that the data has been gamma corrected. To use the sRGB information specified in the file, do not specify this in the options dictionary.
 @warning When deploying to OS's prior to macOS 10.15 / iOS 13.0, this option is ignored for loading KTX textures.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionSRGB NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureUsage
 @abstract Identifier to be used with an NSNumber specifying the MTLTextureUsage flags
 @discussion The resulting Metal texture will be created with the MTLTextureUsage flags indicated by the NSNumber associated with this string.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureUsage NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureCPUCacheMode
 @abstract Identifier to be used with an NSNumber specifying the MTLCPUCacheMode
 @discussion The resulting Metal texture will be created with the MTLCPUCacheMode indicated by the NSNumber associated with this string.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureCPUCacheMode NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureStorageMode
 @abstract Identifier to be used with an NSNumber specifying the MTLStorageMode
 @discussion The resulting Metal texture will be created with the MTLStorageMode indicated by the NSNumber associated with this string. If this option is omitted, the texture will be created with the default storage mode for Metal textures: MTLStorageModeShared on iOS, and MTLStorageModeManaged on OS X. Specifying this option with MTLTextureStorageModePrivate cause the MTKTextureLoader to submit work to the GPU on behalf of the caller.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureStorageMode NS_AVAILABLE(10_12, 10_0);


typedef NSString * MTKTextureLoaderCubeLayout NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.CubeLayout);

/*!
 * @constant MTKTextureLoaderOptionCubeLayout
 * @abstract Identifier to be used in an options NSDictionary with an MTKTextureLoaderCubeLayout NSString specifying whether to create a cubemap from a 2D image
 * @discussion The NSString value specified with this string must be one option of MTKTextureLoaderCubeLayout. If this option is omitted, the texture loader will not create cubemaps from 2D textures. This option cannot be used with PVR files, KTX files, or MDLTextures, which support cube textures directly.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionCubeLayout NS_AVAILABLE(10_12, 10_0);

/*!
 * @constant MTKTextureLoaderCubeLayoutVertical
 * @abstract Identifier specifying that the texture loader will create a cube texture from six faces arranged vertically within a single 2D image
 * @discussion A texture cube will be created from six faces arranged vertically within a single 2D image. The image height must be six times the image width, with faces arranged in the following order from top to bottom: +X, -X, +Y, -Y, +Z, -Z.
 */
MTK_EXTERN MTKTextureLoaderCubeLayout __nonnull const MTKTextureLoaderCubeLayoutVertical NS_AVAILABLE(10_12, 10_0);

typedef NSString * MTKTextureLoaderOrigin NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Origin);

/*!
 * @constant MTKTextureLoaderOptionOrigin
 * @abstract Identifier to be used in an options NSDictionary with an MTKTextureLoaderOrigin NSString specifying whether to flip textures vertically
 * @discussion The NSString value specified with this string must be one option of MTKTextureLoaderOrigin. If this option is omitted, the texture loader will not flip loaded textures. This option cannot be used with block-compressed texture formats, and can only be used with 2D, 2D array, and cube map textures. Each mipmap level and slice of a texture will be flipped.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionOrigin NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginTopLeft
 @abstract Identifier specifying that the texture loader should flip textures whose origin is in the bottom-left corner
 @discussion The texture will be flipped vertically if metadata in the file being loaded indicates that the source data starts with the bottom-left corner of the texture.
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginTopLeft NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginBottomLeft
 @abstract Identifier specifying that the texture loader should flip textures whose origin is in the top-left corner
 @discussion The texture will be flipped vertically if metadata in the file being loaded indicates that the source data starts with the top-left corner of the texture.
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginBottomLeft NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginFlippedVertically
 @abstract Identifier specifying that the texture loader should always flip textures
 @discussion The texture will be flipped vertically regardless of any metadata in the file indicating the placement of the origin in the source data
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginFlippedVertically NS_AVAILABLE(10_12, 10_0);

typedef void (^MTKTextureLoaderCallback) (id <MTLTexture> __nullable texture, NSError * __nullable error) NS_SWIFT_NAME(MTKTextureLoader.Callback);

typedef void (^MTKTextureLoaderArrayCallback) (NSArray<id <MTLTexture>> * __nonnull textures, NSError * __nullable error) NS_SWIFT_NAME(MTKTextureLoader.ArrayCallback) NS_AVAILABLE(10_12, 10_0);

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

- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithDevice:
 @abstract Initialize the loader
 @param device Metal device with which to create Metal textures
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device;

/*!
 @method newTextureWithContentsOfURL:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the file at URL
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when the texture has been loaded and fully initialized
 */
- (void)newTextureWithContentsOfURL:(nonnull NSURL *)URL
                            options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                  completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithName:scaleFactor:bundle:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from a given texture or image 
           asset name
 @param name A texture or image asset name
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the 
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the asset is located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset:
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigin
 @param completionHandler Block called when texture has been loaded and fully initialized
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with thw name iven.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name
 */
- (void)newTextureWithName:(nonnull NSString *)name
               scaleFactor:(CGFloat)scaleFactor
                    bundle:(nullable NSBundle *)bundle
                   options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
         completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler NS_AVAILABLE(10_12, 10_0);


/*!
 @method newTexturesWithContentsOfURLs:options:completionHandler:
 @abstract Asynchronously create an array of Metal textures and load image data from the files at URLs
 @param URLs Locations of image files from which to create the textures
 @param options Dictonary of MTKTextureLoaderOptions, which will be used for every texture loaded
 @param completionHandler Block called when all of the textures have been loaded and fully initialized. The array of MTLTextures will be the same length and in the same order as the requested array of paths. If an error occurs while loading a texture, the corresponding array index will contain NSNull. The NSError will be null if all of the textures are loaded successfully, or will correspond to one of the textures which failed to load.
 */
- (void)newTexturesWithContentsOfURLs:(nonnull NSArray<NSURL *> *)URLs
                              options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                    completionHandler:(nonnull MTKTextureLoaderArrayCallback)completionHandler NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTexturesWithNames:scaleFactor:bundle:options:completionHandler:
 @abstract Asynchronously create Metal textures and load image data from a given texture or image
           asset names
 @param names An array texture or image asset names.  If an error occurs while loading a texture,
              the corresponding index in the returned array contain [NSNull null]
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the assets are located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigin
 @param completionHandler Block called when all of the textures have been loaded and fully
                          initialized. The NSError will be null if all of the textures are loaded
                          successfully, or will correspond to one of the textures which failed to
                          load.
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with each name iven.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name.
 */
- (void)newTexturesWithNames:(nonnull NSArray<NSString *> *)names
                 scaleFactor:(CGFloat)scaleFactor
                      bundle:(nullable NSBundle *)bundle
                     options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
           completionHandler:(nonnull MTKTextureLoaderArrayCallback)completionHandler NS_AVAILABLE(10_12, 10_0);


/*!
 @method newTextureWithData:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the NSData object provided
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithData:(nonnull NSData *)data
                   options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
         completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithCGImage:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the given CGImageRef
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithCGImage:(nonnull CGImageRef)cgImage
                      options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
            completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithMDLTexture:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the given MDLTexture
 @param texture MDLTexture containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithMDLTexture:(nonnull MDLTexture *)texture
                         options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
               completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextureWithContentsOfURL:options:error:
 @abstract Synchronously create a Metal texture and load image data from the file at URL
 @return The Metal texture. nil if an error occured
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithContentsOfURL:(nonnull NSURL *)URL
                                                options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                                  error:(NSError *__nullable *__nullable)error;

/*!
 @method newTexturesWithContentsOfURLs:options:completionHandler:
 @abstract Synchronously create an array of Metal textures and load image data from the files at URLs
 @return An array of MTLTextures of the same length and in the same order as the requested array of
         paths.  If an error occurs while loading a texture, the corresponding array index will
         contain [NSNull null].
 @param URLs Locations of image files from which to create the textures
 @param options Dictonary of MTKTextureLoaderOptions, which will be used for every texture loaded
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred.
              Will be null if all of the textures are loaded successfully, or will correspond to
              one of the textures which failed to load.
 */
- (NSArray <id <MTLTexture>> * __nonnull)newTexturesWithContentsOfURLs:(nonnull NSArray <NSURL *> *)URLs
                                                               options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                                                 error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextureWithData:options:error:
 @abstract Synchronously create a Metal texture and load image data from the NSData object provided
 @return The Metal texture. nil if an error occured
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithData:(nonnull NSData *)data
                                       options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                         error:(NSError *__nullable *__nullable)error;

/*!
 @method newTextureWithCGImage:options:error:
 @abstract Synchronously create a Metal texture and load image data from the given CGImageRef
 @return The Metal texture. nil if an error occured
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithCGImage:(nonnull CGImageRef)cgImage
                                          options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                            error:(NSError *__nullable *__nullable)error;

/*!
 @method newTextureWithMDLTexture:options:error:
 @abstract Synchronously create a Metal texture and load image data from the given MDLTexture
 @return The Metal texture. nil if an error occured
 @param texture MDLTexture containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithMDLTexture:(nonnull MDLTexture *)texture
                                             options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                               error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextursWithName:scaleFactor:bundle:options:error:
 @abstract Synchronously create a Metal texture with texture data from a given texture or image 
           asset name
 @return The Metal texture. nil if an error occured
 @param names An array of texture asset names
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the asset is located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigins
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with the name given.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name.
  */
- (nullable id <MTLTexture>)newTextureWithName:(nonnull NSString *)name
                                   scaleFactor:(CGFloat)scaleFactor
                                        bundle:(nullable NSBundle *)bundle
                                       options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                         error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);


@end
