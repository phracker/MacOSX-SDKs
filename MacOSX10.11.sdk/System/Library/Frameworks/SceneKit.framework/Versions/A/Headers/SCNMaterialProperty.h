//
//  SCNMaterialProperty.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef NS_ENUM(NSInteger, SCNFilterMode) {
    SCNFilterModeNone    NS_ENUM_AVAILABLE(10_9, 8_0) = 0,
    SCNFilterModeNearest NS_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNFilterModeLinear  NS_ENUM_AVAILABLE(10_9, 8_0) = 2
};

/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef NS_ENUM(NSInteger, SCNWrapMode) {
    SCNWrapModeClamp NS_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNWrapModeRepeat NS_ENUM_AVAILABLE(10_9, 8_0) = 2,
    SCNWrapModeClampToBorder NS_ENUM_AVAILABLE(10_9, 9_0) = 3,
    SCNWrapModeMirror NS_ENUM_AVAILABLE(10_9, 8_0) = 4,
};

/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNMaterialProperty : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @method materialPropertyWithContents:
 @abstract Creates and initialize a property instance with the specified contents.
 */
+ (instancetype)materialPropertyWithContents:(id)contents NS_AVAILABLE(10_9, 8_0);

/*! 
 @property contents
 @abstract Specifies the receiver's contents. This can be a color (NSColor/UIColor), an image (NSImage/CGImageRef), a layer (CALayer), a path (NSString or NSURL), a SpriteKit scene (SKScene) or a texture (SKTexture, id<MTLTexture> or GLKTextureInfo). Animatable when set to a color.
 @discussion CGColorRef and CGImageRef can also be set. An array (NSArray) of 6 images is allowed for cube maps, only for reflective property. This array must contain images of the exact same dimensions, in the following order, in a left-handed coordinate system : +X, -X, +Y, -Y, +Z, -Z or if you prefer Right, Left, Top, Bottom, Front, Back. 
     Setting the contents to an instance of SKTexture will automatically update the wrapS, wrapT, contentsTransform, minification, magnification and mip filters according to the SKTexture settings.
 */
@property(nonatomic, retain, nullable) id contents;

/*!
 @property intensity
 @abstract Determines the receiver's intensity. This intensity is used to modulate the properties in several ways.
 It dims the diffuse, specular and emission properties, it varies the bumpiness of the normal property and the
 filter property is blended with white. Default value is 1.0. Animatable.
 */
@property(nonatomic) CGFloat intensity NS_AVAILABLE(10_9, 8_0);

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
 @discussion Defaults to SCNFilterModeNone.
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
 @property borderColor
 @abstract Determines the receiver's border color (CGColorRef or NSColor). Animatable.
 @discussion The border color is ignored on iOS and is always considered as clear color (0,0,0,0) when the texture has an alpha channel and opaque back (0,0,0,1) otherwise.
 */
@property(nonatomic, retain, nullable) id borderColor;

/*! 
 @property mappingChannel
 @abstract Determines the receiver's mapping channel. Defaults to 0.
 @discussion Geometries potentially have multiple sources of texture coordinates. Every source has a unique mapping channel index. The mapping channel allows to select which source of texture coordinates is used to map the content of the receiver. 
 */
@property(nonatomic) NSInteger mappingChannel;      

/*!
 @property maxAnisotropy
 @abstract Specifies the receiver's max anisotropy. Defaults to MAXFLOAT.
 @discussion Anisotropic filtering reduces blur and preserves detail at extreme viewing angles.
 */
@property(nonatomic) CGFloat maxAnisotropy NS_AVAILABLE(10_9, 8_0);

@end
    
NS_ASSUME_NONNULL_END
