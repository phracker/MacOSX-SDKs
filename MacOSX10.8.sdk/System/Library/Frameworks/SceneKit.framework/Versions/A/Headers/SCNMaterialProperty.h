//
//  SCNMaterialProperty.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef enum
{
	SCNNoFiltering      = 0,	
	SCNNearestFiltering = 1,		
	SCNLinearFiltering  = 2,
} SCNFilterMode;


/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef enum
{
	SCNClamp = 1,		
	SCNRepeat = 2,
	SCNClampToBorder = 3,
	SCNMirror = 4,
} SCNWrapMode;


/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNMaterialProperty : NSObject <SCNAnimatable>
{
@private
	id _reserved;
}

/*! 
 @property contents
 @abstract Specifies the receiver's contents. It can be a color (NSColor), an image (NSImage) or a layer (CALayer). Animatable.
 @discussion CGColorRef and CGImageRef can also be set. An array (NSArray) of 6 images is allowed for cube maps, only for reflective property. 
 This array must be contains images of the exact same dimensions, in the following order : +X, -X, +Y, -Y, +Z, -Z or if you prefer Right, Left, Top, Bottom, Back, Front. 
 */
@property(nonatomic, retain) id contents; 

/*! 
 @property minificationFilter
 @abstract Specifies the filter type to use when rendering the contents (specified in the `contents' property).
 @discussion The minification filter is used when to reduce the size of image data. See above the list of available modes.
 */
@property(nonatomic) SCNFilterMode minificationFilter;

/*! 
 @property magnificationFilter
 @abstract Specifies the filter type to use when rendering the the contents (specified in the `contents' property).
 @discussion The magnification filter is used when to increase the size of image data. See above the list of available modes.
 */
@property(nonatomic) SCNFilterMode magnificationFilter;

/*! 
 @property mipFilter
 @abstract Specifies the mipmap filter to use during minification.
 */
@property(nonatomic) SCNFilterMode mipFilter;

/*! 
 @property contentsTransform
 @abstract Determines the receiver's contents transform. Animatable.
 */
@property(nonatomic) CATransform3D contentsTransform;

/*! 
 @property wrapS
 @abstract Determines the receiver's wrap mode for the s texture coordinate.
 */
@property(nonatomic) SCNWrapMode wrapS;

/*! 
 @property wrapT
 @abstract Determines the receiver's wrap mode for the t texture coordinate.
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

@end
