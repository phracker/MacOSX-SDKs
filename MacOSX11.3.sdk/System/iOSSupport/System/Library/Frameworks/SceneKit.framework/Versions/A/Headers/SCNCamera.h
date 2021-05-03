//
//  SCNCamera.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

typedef NS_ENUM(NSInteger, SCNCameraProjectionDirection) {
    SCNCameraProjectionDirectionVertical   = 0,
    SCNCameraProjectionDirectionHorizontal = 1,
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

NS_ASSUME_NONNULL_BEGIN

@class SCNMaterialProperty;

/*!
 @class SCNCamera
 @abstract SCNCamera represents a camera that can be attached to a SCNNode. 
 @discussion A node with a camera can be used as a point of view to visualize a 3D scene.
 */

SCN_EXPORT
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
 @property fieldOfView
 @abstract Determines the receiver's field of view (in degree). Defaults to 60°. Animatable.
 @discussion The fieldOfView is automatically updated when the sensorHeight or focalLength are set. Setting the fieldOfView will update the focalLength according to the new fieldOfView and the current sensorHeight.
 */
@property(nonatomic) CGFloat fieldOfView API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property projectionDirection
 @abstract Determines whether the fieldOfView (or orthographicScale) is vertical or horizontal. Defaults to vertical.
 */
@property(nonatomic) SCNCameraProjectionDirection projectionDirection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focalLength
 @abstract Determines the receiver's focal length in millimeter. Defaults to 50mm. Animatable.
 @discussion The focalLength is automatically updated when the sensorHeight or fieldOfView are set. Setting the focalLength will update the fieldOfView according to the new focalLength and the current sensorHeight.
 */
@property(nonatomic) CGFloat focalLength API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property sensorHeight
 @abstract Determines the vertical size of the sensor in millimeter. Defaults to 24mm. Animatable.
 @discussion Setting the sensorHeight will automatically update the fieldOfView according to the new sensorHeight and the current focalLength.
 */
@property(nonatomic) CGFloat sensorHeight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

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
 @abstract Determines whether the receiver automatically adjusts the zFar value. Defaults to NO.
 @discussion When set to YES, the near and far planes are automatically set to fit the bounding box of the entire scene at render time. 
 */
@property(nonatomic) BOOL automaticallyAdjustsZRange API_AVAILABLE(macos(10.9));

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
@property(nonatomic) double orthographicScale API_AVAILABLE(macos(10.9));

/*!
 @property projectionTransform
 @abstract Determines the projection transform used by the camera to project the world onscreen. 
 */
@property(nonatomic) SCNMatrix4 projectionTransform;
- (SCNMatrix4)projectionTransformWithViewportSize:(CGSize)viewportSize API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// MARK: Depth of Field

/*!
 @property wantsDepthOfField
 @abstract Determines if the receiver has depth of field. Defaults to NO.
 */
@property(nonatomic) BOOL wantsDepthOfField API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focusDistance
 @abstract Determines the receiver's focus distance. Animatable.
 @discussion Defaults to 2.5
 */
@property(nonatomic) CGFloat focusDistance API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focalBlurSampleCount
 @abstract Determines the receiver's sample count for depth of field effect.
 @discussion Defaults to 25.
 */
@property(nonatomic) NSInteger focalBlurSampleCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property fStop
 @abstract Determines the receiver's fstop. Animatable.
 @discussion Defaults to 5.6.
 */
@property(nonatomic) CGFloat fStop API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property apertureBladeCount
 @abstract Determines the receiver's blade count of the aperture.
 @discussion Defaults to 6.
 */
@property(nonatomic) NSInteger apertureBladeCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property motionBlurIntensity
 @abstract Determines the intensity of the motion blur. Animatable. Defaults to 0.
 @discussion An intensity of zero means no motion blur. The intensity should not exceeed 1.
 */
@property(nonatomic) CGFloat motionBlurIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

// MARK: Screen Space Ambient Occlusion

/*!
 @property screenSpaceAmbientOcclusionIntensity
 @abstract Determines the intensity of the screen space ambient occlusion. Animatable.
 @discussion defaults to 0.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionIntensity API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionRadius
 @abstract Determines the screen space ambient occlusion radius in scene unit. Animatable.
 @discussion defaults to 5.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionBias
 @abstract Determines self occlusion bias in scene unit.
 @discussion defaults to 0.03.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionBias API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionDepthThreshold
 @abstract Determines the depth blur threshold in scene unit.
 @discussion defaults to 0.2.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionDepthThreshold API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionNormalThreshold
 @abstract Determines the normal blur threshold.
 @discussion defaults to 0.3.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionNormalThreshold API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// MARK: High Dynamic Range

/*!
 @property wantsHDR
 @abstract Determines if the receiver has a high dynamic range. Defaults to NO.
 */
@property(nonatomic) BOOL wantsHDR API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureOffset
 @abstract Determines the logarithmic exposure biasing, in EV. Defaults to 0.
 */
@property(nonatomic) CGFloat exposureOffset API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property averageGray
 @abstract Determines the average gray level desired in the final image. Defaults to 0.18.
 */
@property(nonatomic) CGFloat averageGray API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property whitePoint
 @abstract Determines the smallest luminance level that will be mapped to white in the final image. Defaults to 1.
 */
@property(nonatomic) CGFloat whitePoint API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property wantsExposureAdaptation
 @abstract Determines if the receiver should simulate an eye and continuously adjust to luminance. Defaults to YES.
 */
@property(nonatomic) BOOL wantsExposureAdaptation API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from bright areas to dark areas. Defaults to 0.4.
 */
@property(nonatomic) CGFloat exposureAdaptationBrighteningSpeedFactor API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from dark areas to bright areas. Defaults to 0.6.
 */
@property(nonatomic) CGFloat exposureAdaptationDarkeningSpeedFactor API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property minimumExposure
 @abstract Determines the minimum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat minimumExposure API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property maximumExposure
 @abstract Determines the maximum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat maximumExposure API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomThreshold
 @abstract Determines the luminance threshold for the bloom effect. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat bloomThreshold API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomIteration
 @abstract Determines the number of blur iterations. Defaults to 1.
 */
@property(nonatomic) NSInteger bloomIterationCount API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property bloomIterationSpread
 @abstract Determines how the bloom iterations are spread. Defaults to 0.
 */
@property(nonatomic) CGFloat bloomIterationSpread API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property bloomIntensity
 @abstract Determines the intensity of the bloom effect. Animatable. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat bloomIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomBlurRadius
 @abstract Determines the radius of the bloom effect in points. Animatable. Defaults to 4.
 */
@property(nonatomic) CGFloat bloomBlurRadius API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingPower
 @abstract Controls the shape of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingPower API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingIntensity
 @abstract Controls the intensity of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeStrength
 @abstract Controls the strength of the color shift effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat colorFringeStrength API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeIntensity
 @abstract Controls the intensity of the color shift effect. Defaults to 1.
 */
@property(nonatomic) CGFloat colorFringeIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property saturation
 @abstract Controls the overall saturation of the scene. Defaults to 1 (no effect).
 */
@property(nonatomic) CGFloat saturation API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property contrast
 @abstract Controls the overall contrast of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat contrast API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property grainIntensity
 @abstract Controls the intensity of the grain. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat grainIntensity API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property grainScale
 @abstract Controls the scale of the grain. Defaults to 1.
 */
@property(nonatomic) CGFloat grainScale API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property grainIsColored
 @abstract Determines if the grain is colored or not. Defaults to NO.
 */
@property(nonatomic) BOOL grainIsColored API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property whiteBalanceTemperature
 @abstract Controls the overall white balance temperature of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat whiteBalanceTemperature API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property whiteBalanceTint
 @abstract Controls the overall white balance tint of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat whiteBalanceTint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property colorGrading
 @abstract Specifies a lookup texture to apply color grading. The contents must a 2D image representing `n` slices of a unit color cube texture, arranged in an horizontal row of `n` images. For instance, a color cube of dimension 16x16x16 should be provided as an image of size 256x16.
 */
@property(nonatomic, readonly) SCNMaterialProperty *colorGrading API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that are visible from the receiver. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
