//
//  SCNMaterialProperty.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef NS_ENUM(NSInteger, SCNFilterMode) {
    SCNFilterModeNone    SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 0,
    SCNFilterModeNearest SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNFilterModeLinear  SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 2,
    SCNNoFiltering       = SCNFilterModeNone,    // Deprecated name for SCNFilterModeNone
    SCNNearestFiltering  = SCNFilterModeNearest, // Deprecated name for SCNFilterModeNearest
    SCNLinearFiltering   = SCNFilterModeLinear   // Deprecated name for SCNFilterModeLinear
};

/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef NS_ENUM(NSInteger, SCNWrapMode) {
    SCNWrapModeClamp SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNWrapModeRepeat SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 2,
    SCNWrapModeClampToBorder SCENEKIT_ENUM_AVAILABLE(10_9, NA) = 3,
    SCNWrapModeMirror SCENEKIT_ENUM_AVAILABLE(10_9, 8_0) = 4,
    SCNClamp = SCNWrapModeClamp,                 // Deprecated name for SCNWrapModeClamp
    SCNRepeat = SCNWrapModeRepeat,               // Deprecated name for SCNWrapModeRepeat
    SCNClampToBorder = SCNWrapModeClampToBorder, // Deprecated name for SCNWrapModeClampToBorder
    SCNMirror = SCNWrapModeMirror,               // Deprecated name for SCNWrapModeMirror
};

/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNMaterialProperty : NSObject <SCNAnimatable, NSSecureCoding>
{
@private
	id _reserved;
}

/*!
 @method materialPropertyWithContents:
 @abstract Creates and initialize a property instance with the specified contents.
 */
+ (instancetype)materialPropertyWithContents:(id)contents SCENEKIT_AVAILABLE(10_9, 8_0);

/*! 
 @property contents
 @abstract Specifies the receiver's contents. This can be a color (NSColor), an image (NSImage), a layer (CALayer), a path (NSString or NSURL), a SpriteKit scene (SKScene) or a SKTexture. Animatable when set to a color.
 @discussion CGColorRef and CGImageRef can also be set. An array (NSArray) of 6 images is allowed for cube maps, only for reflective property. This array must contain images of the exact same dimensions, in the following order : +X, -X, +Y, -Y, +Z, -Z or if you prefer Right, Left, Top, Bottom, Back, Front. 
     Setting the contents to an instance of SKTexture will automatically update the wrapS, wrapT, contentsTransform, minification, magnification and mip filters according to the SKTexture settings.
 */
@property(nonatomic, retain) id contents; 

/*!
 @property intensity
 @abstract Determines the receiver's intensity. This intensity is used to modulate the properties in several ways.
 It dims the diffuse, specular and emission properties, it varies the bumpiness of the normal property and the
 filter property is blended with white. Default value is 1.0. Animatable.
 */
@property(nonatomic) CGFloat intensity SCENEKIT_AVAILABLE(10_9, 8_0);

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
 @abstract Determines the receiver's border color.
 */
@property(nonatomic, retain) id borderColor;              /* color (CGColorRef, NSColor or UIColor). Animatable.*/

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
@property(nonatomic) CGFloat maxAnisotropy SCENEKIT_AVAILABLE(10_9, 8_0);

@end
