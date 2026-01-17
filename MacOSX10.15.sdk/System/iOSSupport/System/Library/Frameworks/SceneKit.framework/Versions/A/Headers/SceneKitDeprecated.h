//
//  SceneKitDeprecated.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface SCNLight (SCNDeprecated) <SCNTechniqueSupport>
@end


@interface SCNCamera (SCNDeprecated)

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius API_DEPRECATED("Use fStop instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double xFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double yFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Defaults to 1/8.0.
 */
@property(nonatomic) CGFloat aperture API_DEPRECATED("Use -[SCNCamera fStop] instead with fStop = sensorHeight / aperture.", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0 prior to macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Defaults to 2.5 otherwise.
 */
@property(nonatomic) CGFloat focalDistance API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

@end


@interface SCNRenderer (SCNDeprecated)

// Deprecated
/*!
 @method render
 @abstract renders the receiver's scene at the current system time.
 @discussion This method only work if the receiver was allocated with an OpenGL context and it is deprecated (use renderAtTime: instead). Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)render API_DEPRECATED_WITH_REPLACEMENT("-renderAtTime:withEncoder:pass:commandQueue:", macos(10.8, 10.11), ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst);

@end


@interface SCNMaterialProperty (SCNDeprecated)

/*!
 @property borderColor
 @abstract Determines the receiver's border color (CGColorRef or UIColor). Animatable.
 @discussion The border color is ignored on iOS and is always considered as clear color (0,0,0,0) when the texture has an alpha channel and opaque back (0,0,0,1) otherwise.
 */
@property(nonatomic, retain, nullable) id borderColor API_DEPRECATED("Deprecated", macos(10.8, 10.12), ios(8.0, 10.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst);

@end

NS_ASSUME_NONNULL_END
