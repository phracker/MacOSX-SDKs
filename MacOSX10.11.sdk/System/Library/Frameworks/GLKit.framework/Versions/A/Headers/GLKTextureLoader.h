//
//  GLKTextureLoader.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

/*
 Convenience library for loading textures into OpenGL
 
 - Synchronous and asynchronous loading of textures
 - Supports most ImageIO formats as well as PVR files on iOS
 
 Default Texture Parameters
 
 - The following values will be set as the default for the OpenGL filter and wrap texture parameters:
 
 GL_TEXTURE_MIN_FILTER: GL_LINEAR_MIPMAP_LINEAR if textures are mipmapped, GL_LINEAR otherwise
 
 GL_TEXTURE_MAG_FILTER: GL_LINEAR
 
 GL_TEXTURE_WRAP_S / GL_TEXTURE_WRAP_T: GL_CLAMP_TO_EDGE
 
 Any texture parameter not specified above will be set to OpenGL's default value.
 */

#import <CoreGraphics/CoreGraphics.h>

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/EAGL.h>
#import <OpenGLES/gltypes.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gltypes.h>
#import <AppKit/AppKit.h>
#endif // !TARGET_OS_IPHONE

#import <GLKit/GLKitBase.h>

NS_ASSUME_NONNULL_BEGIN
#pragma mark -
#pragma mark Definitions
#pragma mark -

/*
 Dictionary keys for texture loader properties
 */
/*
 GLKTextureLoaderApplyPremultiplication - A boolean NSNumber.
 Non-alpha channels are premultiplied by corresponding alpha channel values.
 For compressed formats, this option must be omitted, or false.
 False by default.
 */
GLK_EXTERN NSString *const GLKTextureLoaderApplyPremultiplication NS_AVAILABLE(10_8, 5_0);

/*
 GLKTextureLoaderGenerateMipmaps - A boolean NSNumber
 Generates all levels of mipmaps for the current image being loaded as a texture.
 Generates mipmap levels for all faces when used with cube maps.
 Sets GL_TEXTURE_MIN_FILTER parameter to GL_LINEAR_MIPMAP_LINEAR when true.
 False by default. */
GLK_EXTERN NSString *const GLKTextureLoaderGenerateMipmaps NS_AVAILABLE(10_8, 5_0);

/*
 GLKTextureLoaderOriginBottomLeft - A boolean NSNumber.
 Transform image data to match OpenGL's bottom left orientation specification.
 False by default. */
GLK_EXTERN NSString *const GLKTextureLoaderOriginBottomLeft NS_AVAILABLE(10_8, 5_0);

/*
 GLKTextureLoaderGrayscaleAsAlpha - A boolean NSNumber.
 If true, a single channel grayscale image is loaded as GL_ALPHA.
 If false, it will be loaded as GL_LUMINANCE.
 Has no effect on non-grayscale images and on OS X.
 False by default.
 */
GLK_EXTERN NSString *const GLKTextureLoaderGrayscaleAsAlpha NS_AVAILABLE_IOS(5_0);


/*
 GLKTextureLoaderSRGB - A boolean NSNumber.
 If true, the texture will be loaded as sRGB.
 If false, it will be loaded as linear.
 False by default.
 */
#if TARGET_OS_IPHONE || defined(MAC_OS_X_VERSION_10_9)
GLK_EXTERN NSString *const GLKTextureLoaderSRGB NS_AVAILABLE(10_9, 7_0);
#else
GLK_EXTERN NSString *const GLKTextureLoaderSRGB;
#endif

/*
 Error domain for GLKTextureLoader
 */
GLK_EXTERN NSString *const GLKTextureLoaderErrorDomain NS_AVAILABLE(10_8, 5_0);

/*
 Error keys for obtaining more error information
 */
GLK_EXTERN NSString *const GLKTextureLoaderErrorKey NS_AVAILABLE(10_8, 5_0);
GLK_EXTERN NSString *const GLKTextureLoaderGLErrorKey NS_AVAILABLE(10_8, 5_0);

/*
 Error codes
 */
typedef NS_ENUM(GLuint, GLKTextureLoaderError)
{
    GLKTextureLoaderErrorFileOrURLNotFound = 0,
    GLKTextureLoaderErrorInvalidNSData = 1,
    GLKTextureLoaderErrorInvalidCGImage = 2,
    GLKTextureLoaderErrorUnknownPathType = 3,
    GLKTextureLoaderErrorUnknownFileType = 4,
    GLKTextureLoaderErrorPVRAtlasUnsupported = 5,
    GLKTextureLoaderErrorCubeMapInvalidNumFiles = 6,
    GLKTextureLoaderErrorCompressedTextureUpload = 7,
    GLKTextureLoaderErrorUncompressedTextureUpload = 8,
    GLKTextureLoaderErrorUnsupportedCubeMapDimensions = 9,
    GLKTextureLoaderErrorUnsupportedBitDepth = 10,
    GLKTextureLoaderErrorUnsupportedPVRFormat = 11,
    GLKTextureLoaderErrorDataPreprocessingFailure = 12,
    GLKTextureLoaderErrorMipmapUnsupported = 13,
    GLKTextureLoaderErrorUnsupportedOrientation = 14,
    GLKTextureLoaderErrorReorientationFailure = 15,
    GLKTextureLoaderErrorAlphaPremultiplicationFailure = 16,
    GLKTextureLoaderErrorInvalidEAGLContext = 17,
    GLKTextureLoaderErrorIncompatibleFormatSRGB = 18
} NS_ENUM_AVAILABLE(10_8, 5_0);

#pragma mark -
#pragma mark GLKTextureInfo
#pragma mark -

/*
 Alpha state of loaded texture
 */
typedef NS_ENUM(GLint, GLKTextureInfoAlphaState)
{
    GLKTextureInfoAlphaStateNone = 0,
    GLKTextureInfoAlphaStateNonPremultiplied,
    GLKTextureInfoAlphaStatePremultiplied
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Image origin of loaded texture
 */
typedef NS_ENUM(GLint, GLKTextureInfoOrigin)
{
    GLKTextureInfoOriginUnknown = 0,
    GLKTextureInfoOriginTopLeft,
    GLKTextureInfoOriginBottomLeft
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Immutable Texture Object Data
 */
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKTextureInfo : NSObject <NSCopying>
{
@private
    GLuint                      name;
    GLenum                      target;
    GLuint                      width;
    GLuint                      height;
    GLKTextureInfoAlphaState    alphaState;
    GLKTextureInfoOrigin        textureOrigin;
    BOOL                        containsMipmaps;
}

@property (readonly) GLuint                     name;
@property (readonly) GLenum                     target;
@property (readonly) GLuint                     width;
@property (readonly) GLuint                     height;
@property (readonly) GLKTextureInfoAlphaState   alphaState;
@property (readonly) GLKTextureInfoOrigin       textureOrigin;
@property (readonly) BOOL                       containsMipmaps;

@end

#pragma mark -
#pragma mark GLKTextureLoader
#pragma mark -

typedef void (^GLKTextureLoaderCallback) (GLKTextureInfo * __nullable textureInfo, NSError * __nullable outError);

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKTextureLoader : NSObject
{
    
}

#pragma mark Synchronous Methods

/*
 Synchronously load an image from disk into an OpenGL texture.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

+ (nullable GLKTextureInfo *)textureWithContentsOfURL:(NSURL *)url                                           /* The URL from which to read. */
                                              options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously create a texture from data residing in memory.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithContentsOfData:(NSData *)data                                         /* NSData containing image contents. */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously create a texture from a CGImageRef.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithCGImage:(CGImageRef)cgImage                                    /* CGImage reference. */
                                        options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                          error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously load six images from disk into an OpenGL cubemap texture.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error' which is nil otherwise.
 */
+ (nullable GLKTextureInfo*)cubeMapWithContentsOfFiles:(NSArray<id> *)paths                                   /* An array of paths (NSStrings or NSURLs). */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Otions that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously creates an OpenGL cubemap texture by splitting one image into six parts.
 Takes a single image file where height = 6 * width or width = 6 * height.
 The former (vertical orientation) is preferred to avoid image data extraction overhead.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error' which is nil otherwise.
 */
+ (nullable GLKTextureInfo*)cubeMapWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                                              options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                error:(NSError * __nullable * __nullable)outError;           /* Error description. */


+ (nullable GLKTextureInfo*)cubeMapWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                                             options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                               error:(NSError * __nullable * __nullable)outError;           /* Error description. */

#pragma mark Asynchronous Methods

/*
 Internally creates a new shared context that will handle the texture creation operations.
 The sharegroup will be released upon releasing the GLKTextureLoader object.
 */
#if TARGET_OS_IPHONE
- (instancetype)initWithSharegroup:(EAGLSharegroup *)sharegroup;
#else
- (instancetype)initWithShareContext:(NSOpenGLContext *)context;
#endif

/*
 Asynchronously load an image from disk into an OpenGL texture.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

- (void)textureWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                         options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                           queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
               completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

/*
 Asynchronously create a texture from data residing in memory.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithContentsOfData:(NSData *)data                                         /* NSData containing image contents. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

/*
 Asynchronously create a texture from a CGImageRef.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithCGImage:(CGImageRef)cgImage                                    /* CGImage reference. */
                   options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                     queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
         completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


/*
 Asynchronously load six images from disk into an OpenGL cubemap texture.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)cubeMapWithContentsOfFiles:(NSArray<id> *)paths                                   /* An array of paths (NSStrings or NSURLs). */
                           options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                             queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                 completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


/*
 Asynchronously creates an OpenGL cubemap texture by splitting one image into six parts.
 Takes a single image file where height = 6 * width or width = 6 * height.
 The former (vertical orientation) is preferred to avoid image data extraction overhead.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)cubeMapWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


- (void)cubeMapWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                         options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                           queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
               completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

@end
NS_ASSUME_NONNULL_END
