//
//  SCNCamera.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNCamera
 @abstract SCNCamera represents a camera that can be attached to a SCNNode. 
 @discussion A node with a camera can be used as a point of view to visualize a 3D scene.
 */

@interface SCNCamera : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*! 
 @method camera
 @abstract Creates and returns a camera instance.
 */
+ (instancetype)camera;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*! 
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double xFov;

/*! 
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double yFov;

/*! 
 @property zNear
 @abstract Determines the receiver's near value. Animatable.
 @discussion The near value determines the minimal distance between the camera and a visible surface. If a surface is closer to the camera than this minimal distance, then the surface is clipped. The near value must be different than zero. Defaults to 1.
 */
@property(nonatomic) double zNear;

/*! 
 @property zFar
 @abstract Determines the receiver's far value. Animatable.
 @discussion The far value determines the maximal distance between the camera and a visible surface. If a surface is further from the camera than this maximal distance, then the surface is clipped. Defaults to 100.
 */
@property(nonatomic) double zFar;

/*!
 @property automaticallyAdjustsZRange
 @abstract Determines whether the receiver automatically adjusts the zNear and zFar values. Defaults to NO.
 @discussion When set to YES, the near and far planes are automatically set to fit the bounding box of the entire scene at render time. Setting the property zNear or zFar automatically resets this property to NO.
 */
@property(nonatomic) BOOL automaticallyAdjustsZRange API_AVAILABLE(macosx(10.9));

/*! 
 @property usesOrthographicProjection
 @abstract Determines whether the receiver uses an orthographic projection or not. Defaults to NO.
 */
@property(nonatomic) BOOL usesOrthographicProjection;

/*!
 @property orthographicScale
 @abstract Determines the receiver's orthographic scale value. Animatable. Defaults to 1.
 @discussion This setting determines the size of the camera's visible area. This is only enabled when usesOrthographicProjection is set to YES.
 */
@property(nonatomic) double orthographicScale API_AVAILABLE(macosx(10.9));

/*!
 @property projectionTransform
 @abstract Determines the projection transform used by the camera to project the world onscreen. 
 */
@property(nonatomic) SCNMatrix4 projectionTransform;
- (SCNMatrix4)projectionTransform;
- (void)setProjectionTransform:(SCNMatrix4)projectionTransform API_AVAILABLE(macosx(10.9));

/*!
 @functiongroup Depth of field
 */
/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0
 */
@property(nonatomic) CGFloat focalDistance API_AVAILABLE(macosx(10.9));

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize API_AVAILABLE(macosx(10.9));

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius API_AVAILABLE(macosx(10.9));

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Determines how fast the transition between in-focus and out-of-focus areas is. The greater the aperture is the faster the transition is. Defaults to 1/8.
 */
@property(nonatomic) CGFloat aperture API_AVAILABLE(macosx(10.9));

/*!
 @property motionBlurIntensity
 @abstract Determines the intensity of the motion blur. Animatable. Defaults to 0.
 @discussion An intensity of zero means no motion blur. The intensity should not exceeed 1.
 */
@property(nonatomic) CGFloat motionBlurIntensity API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @functiongroup High Dynamic Range
 */
/*!
 @property wantsHDR
 @abstract Determines if the receiver has a high dynamic range. Defaults to NO.
 */
@property(nonatomic) BOOL wantsHDR API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureOffset
 @abstract Determines the logarithimc exposure biasing, in EV. Defaults to 0.
 */
@property(nonatomic) CGFloat exposureOffset API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property averageGray
 @abstract Determines the average gray level desired in the final image. Defaults to 0.18.
 */
@property(nonatomic) CGFloat averageGray API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property whitePoint
 @abstract Determines the smallest luminance level that will be mapped to white in the final image. Defaults to 1.
 */
@property(nonatomic) CGFloat whitePoint API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property wantsExposureAdaptation
 @abstract Determines if the receiver should simulate an eye and continuously adjust to luminance. Defaults to YES.
 */
@property(nonatomic) BOOL wantsExposureAdaptation API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from bright areas to dark areas. Defaults to 0.4.
 */
@property(nonatomic) CGFloat exposureAdaptationBrighteningSpeedFactor API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed whien going from dark areas to bright areas. Defaults to 0.6.
 */
@property(nonatomic) CGFloat exposureAdaptationDarkeningSpeedFactor API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property minimumExposure
 @abstract Determines the minimum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat minimumExposure API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property maximumExposure
 @abstract Determines the maximum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat maximumExposure API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomThreshold
 @abstract Determines the luminance threshold for the bloom effect. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat bloomThreshold API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomIntensity
 @abstract Determines the intensity of the bloom effect. Animatable. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat bloomIntensity API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomBlurRadius
 @abstract Determines the radius of the bloom effect in pixels. Animatable. Defaults to 4.
 */
@property(nonatomic) CGFloat bloomBlurRadius API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingPower
 @abstract Controls the shape of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingPower API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingIntensity
 @abstract Controls the intensity of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingIntensity API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeStrength
 @abstract Controls the strength of the color shift effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat colorFringeStrength API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeIntensity
 @abstract Controls the intensity of the color shift effect. Defaults to 1.
 */
@property(nonatomic) CGFloat colorFringeIntensity API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property saturation
 @abstract Controls the overall saturation of the scene. Defaults to 1 (no effect).
 */
@property(nonatomic) CGFloat saturation API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property contrast
 @abstract Controls the overall contrast of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat contrast API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorGrading
 @abstract Specifies a lookup texture to apply color grading. The contents must a 2D image representing `n` slices of a unit color cube texture, arranged in an horizontal row of `n` images. For instance, a color cube of dimension 16x16x16 should be provided as an image of size 256x16.
 */
@property(nonatomic, readonly) SCNMaterialProperty *colorGrading API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that are visible from the receiver. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macosx(10.10));

@end

NS_ASSUME_NONNULL_END
