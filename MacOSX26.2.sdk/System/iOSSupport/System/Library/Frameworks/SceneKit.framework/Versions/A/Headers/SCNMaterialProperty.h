//
//  SCNMaterialProperty.h
//  SceneKit
//
//  Copyright © 2012-2021 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>

@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef NS_ENUM(NSInteger, SCNFilterMode) {
    SCNFilterModeNone    = 0,
    SCNFilterModeNearest = 1,
    SCNFilterModeLinear  = 2
} API_AVAILABLE(macos(10.9));

/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef NS_ENUM(NSInteger, SCNWrapMode) {
    SCNWrapModeClamp         = 1,
    SCNWrapModeRepeat        = 2,
    SCNWrapModeClampToBorder = 3,
    SCNWrapModeMirror        = 4
} API_AVAILABLE(macos(10.9));

/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

SCN_EXPORT
@interface SCNMaterialProperty : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @method materialPropertyWithContents:
 @abstract Creates and initialize a property instance with the specified contents.
 */
+ (instancetype)materialPropertyWithContents:(id)contents API_AVAILABLE(macos(10.9));

/*! 
 @property contents
 @abstract Specifies the receiver's contents. This can be a color (NSColor, UIColor, CGColorRef), an image (NSImage, UIImage, CGImageRef), a layer (CALayer), a path (NSString or NSURL), a SpriteKit scene (SKScene), a texture (SKTexture, id<MTLTexture> or GLKTextureInfo), or a floating value between 0 and 1 (NSNumber) for metalness and roughness properties. AVCaptureDevice is supported on iOS 11 and AVPlayer is supported on macOS 10.13, iOS 11 and tvOS 11. Animatable when set to a color.
 @discussion Setting the contents to an instance of SKTexture will automatically update the wrapS, wrapT, contentsTransform, minification, magnification and mip filters according to the SKTexture settings.
             When a cube map is expected (e.g. SCNMaterial.reflective, SCNScene.background, SCNScene.lightingEnvironment) you can use
               1. A horizontal strip image                          where `6 * image.height ==     image.width`
               2. A vertical strip image                            where `    image.height == 6 * image.width`
               3. A spherical projection image (latitude/longitude) where `2 * image.height ==     image.width`
               4. A NSArray of 6 images. This array must contain images of the exact same dimensions, in the following order, in a left-handed coordinate system: +X, -X, +Y, -Y, +Z, -Z (or Right, Left, Top, Bottom, Front, Back).
 */
@property(nonatomic, retain, nullable) id contents;

/*!
 @property intensity
 @abstract Determines the receiver's intensity. This intensity is used to modulate the properties in several ways.
 It dims the diffuse, specular and emission properties, it varies the bumpiness of the normal property and the
 filter property is blended with white. Default value is 1.0. Animatable.
 */
@property(nonatomic) CGFloat intensity API_AVAILABLE(macos(10.9));

/*! 
 @property minificationFilter
 @abstract Specifies the filter type to use when rendering the contents (specified in the `contents' property).
 @discussion The minification filter is used when to reduce the size of image data. See above the list of available modes. Defaults to SCNFilterModeLinear.
 */
@property(nonatomic) SCNFilterMode minificationFilter;

/*! 
 @property magnificationFilter
 @abstract Specifies the filter type to use when rendering the the contents (specified in the `contents' property).
 @discussion The magnification filter is used when to increase the size of image data. See above the list of available modes. Defaults to SCNFilterModeLinear.
 */
@property(nonatomic) SCNFilterMode magnificationFilter;

/*! 
 @property mipFilter
 @abstract Specifies the mipmap filter to use during minification.
 @discussion Defaults to SCNFilterModeNearest starting macOS 10.12, iOS 10, tvOS 10 and watchOS 3. Defaults to SCNFilterModeNone in previous versions.
 */
@property(nonatomic) SCNFilterMode mipFilter;

/*! 
 @property contentsTransform
 @abstract Determines the receiver's contents transform. Animatable.
 */
@property(nonatomic) SCNMatrix4 contentsTransform;

/*! 
 @property wrapS
 @abstract Determines the receiver's wrap mode for the s texture coordinate. Defaults to SCNWrapModeClamp.
 */
@property(nonatomic) SCNWrapMode wrapS;

/*! 
 @property wrapT
 @abstract Determines the receiver's wrap mode for the t texture coordinate. Defaults to SCNWrapModeClamp.
 */
@property(nonatomic) SCNWrapMode wrapT;

/*! 
 @property mappingChannel
 @abstract Determines the receiver's mapping channel. Defaults to 0.
 @discussion Geometries potentially have multiple sources of texture coordinates. Every source has a unique mapping channel index. The mapping channel allows to select which source of texture coordinates is used to map the content of the receiver. 
 */
@property(nonatomic) NSInteger mappingChannel;      

/*!
 @property textureComponents
 @abstract Specifies the texture components to sample in the shader. Defaults to SCNColorMaskRed for displacement property, and to SCNColorMaskAll for other properties.
 @discussion Use this property to when using a texture that combine multiple informations in the different texture components. For example if you pack the roughness in red and metalness in blue etc... You can specify what component to use from the texture for this given material property. This property is only supported by Metal renderers.
 */
@property(nonatomic) SCNColorMask textureComponents API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property maxAnisotropy
 @abstract Specifies the receiver's max anisotropy. Defaults to 1.0.
 @discussion Anisotropic filtering reduces blur and preserves detail at extreme viewing angles.
 */
@property(nonatomic) CGFloat maxAnisotropy API_AVAILABLE(macos(10.9));

/*!
 @method precomputedLightingEnvironmentContentsWithURL:error:
 @abstract Returns an object suitable for a scene's `lightingEnvironment.contents` and initialized with data that was previously created by `+precomputedLightingEnvironmentDataForContents:device:error:`.
 */
+ (nullable id)precomputedLightingEnvironmentContentsWithURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @method precomputedLightingEnvironmentContentsWithData:error:
 @abstract Returns an object suitable for a scene's `lightingEnvironment.contents` and initialized with data that was previously created by `+precomputedLightingEnvironmentDataForContents:device:error:`.
 */
+ (nullable id)precomputedLightingEnvironmentContentsWithData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
 @method precomputedLightingEnvironmentDataForContents:device:error:
 @abstract Returns an `NSData` instance containing the result of CPU and GPU-intensive operations that is suitable for caching.
 @discussion This method can be leveraged in a custom offline asset pipeline, or at run time at a convenient time before the scene is presented to the user.
 */
+ (nullable NSData *)precomputedLightingEnvironmentDataForContents:(id)contents device:(nullable id<MTLDevice>)device error:(NSError **)error API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

@end
    
NS_ASSUME_NONNULL_END
