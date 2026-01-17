/*!
 @header MDLCamera.h
 @framework ModelIO
 @abstract Represent a physically plausible camera model
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLTexture;

/**
 MDLCamera
 
 @summary MDLCamera models a physically plausible camera.
 
 @discussion Values are represented as float in MDLCamera as it offers sufficient 
 precision, and because calculations will be identical on any processor
 architecture. This consistency is a requirement of the model.

 MDLCamera provides the a model of the parameters governing the physical process 
 of transforming a scene into an image.

 This process is modeled as a series of steps, each governed by the physical
 properties of real world cameras.
 
 1. The position and orientation of the camera
    @see MDLObject transform property
 
    The MDLTransformComponent on an MDLCamera is an MDLTransform.
 
 2. Visible Objects and Lights
    @property nearVisibilityDistance The minimum distance from the camera of a 
              visible object
    @property farVisibilityDistance The maximum distance from the camera of a 
              visible object
 
    Those objects existing between nearVisibilityDistance and farVisibilityDistance 
    are considered to be visible. All lights are considered, irrespective of 
    nearVisibilityDistance and farVisibilityDistance, to compute scene luminance.
 
    @property worldToMetersConversionScale
 
    Some calculations, such as the calculation of stereo view matrices, require
    calculations to occur in world space. Significant quantities measured in mm
    therefore use this conversion scale to perform the calculation. The default
    value is 1.0.
 
 3. Scene Luminance through the lens
 
    @property barrelDistorion
    @property fisheyeDistortion
 
    Illuminated objects result in scene luminance, which passes through the lens.
    All lenses impose some amount of radial distortion which can be computed from 
    focal length. However, some lenses introduce error, and radial distortion can 
    be used as an aesthetic control as well. Therefore radial distortion is 
    provided as a property. If r is the radial distance of a pixel from the center 
    of the projection, then radial distortion is computed as
 
         r' = r * (1 + barrelDistorion * r^2 + fisheyeDistortion * r^4)

    radialDistortion sufficiently describes the distortion characteristic of most 
    lenses. In order to simulate certain other lenses, such as those found in 
    security cameras, fisheye lenses, plastic toy lenses, sport cameras, or some 
    VR headsets, radialDistortion2 is introduced.
 
    The default for the radial distortion parameters is zero, resulting in a 
    rectilinear projection.
 
    @property opticalVignetting
 
    Optical vignetting occurs to some degree in all lenses. It results from light 
    at the edge of an image being blocked as it travels past the lens hood and 
    the internal lens apertures. It is more prevalent with wide apertures. A 
    value of zero indicates no optical vignetting is occuring, and a value of one 
    indicates that vignetting affects all locations in the image according to 
    radial distance. Optical vignetting also occurs in head mounted displays, and 
    the value here can be used as an intended amount of vignetting to apply to an
    image.
 
    @property chromaticAberration
    
    Chromatic aberration occurs to some degree in all lenses. It results from a 
    lens bringing different wavelengths of light to focus at different places on 
    the image plane. A value of zero indicates no chromatic aberration is 
    occurring, and one indicates maximum. Chromatic aberration affects all 
    locations in the image according to radial distance. Chromatic aberration 
    also occurs in head mounted displays, and the value here can be used as an 
    intended amount of chromatic aberration to apply to an image.
 
 4. Geometry of the lens
 
    This is a thin lens model.
 
    @property focalLength
 
    The default focal length is 50mm, corresponding to a field of view of 54 
    degrees, and vertical sensor aperture of 24mm. Changing focalLength will 
    update the field of view property.
 
    @property focusDistance
 
    The distance, in meters, at which the lens is focused. The default is 2.5m.
 
    @property fieldOfView
 
    The field of view is calcualted from the focal length and sensor aperture.
    Changing the field of view will update the focalLength property with respect 
    to the sensor aperture. The default is 54 degrees, corresponding to a focal 
    length of 50mm, and a vertical sensor aperture of 24mm.
 
    @property fStop
 
    The f-stop is the ratio of the lens' focal length to the diameter of the 
    entrance pupil. The default is 5.6. It controls the amount of light that 
    reaches the sensor, as well as the size of out of focus parts of the image.
    The diameter of the entrance pupil, is therefore obtained
    by dividing the fStop by the focalLength.
 
 5. Lens exit aperture
 
    @property apertureBladeCount
 
    The shape of out of focus highlights in a scene is commonly known as "bokeh". 
    The aesthetic quality of a lens' bokeh is one of the characteristics that 
    drives the choice of a lens for a particular scene. To a large degree, the 
    appearance of bokeh is governed by the shape of the lens aperture. Typical 
    lens apertures are controlled by a series of overlapping blades that can be 
    irised open and closed. A lens with a five blade aperture will yield a five
    sided bokeh. The default is zero, which is to be interpreted as a perfectly 
    round aperture.
 
    Note that the effect of a filter on the front of the lens can be modeled 
    equivalently at the exit aperture. The MIOCamera does not explicitly provide 
    specification of such effects, but a simulation could incorporate them at 
    this stage.
 
    @property maximumCircleOfConfusion

    Although the size of an out of focus bokeh highlight can be computed from
    other camera properties, it is often necessary to limit the size of the 
    circle of confusion for aesthetic reasons. The circle of confusion is 
    specified in mm, and the default is 0.05mm. The units are mm on the sensor 
    plane.
 
    @property shutterOpenInterval
 
    The length of time in seconds the shutter is open, impacting the amount of 
    light that reaches the sensor and also the length of motion blur trails. The 
    shutter time is not the same thing as scene frame rate. The rule of thumb for 
    movies is that the shutter time should be half the frame rate, so to achieve
    a "filmic" look, the shutter time choice might be 1/48 of a second, since 
    films are usually projected at 24 frames per second. Shutter time is 
    independent of simulation frame rate because motion blur trails and exposure 
    times should be held constant in order to avoid flicker artifacts.
 
 6. Sensor illuminance
 
    @property sensorVerticalAperture
 
    The default aperture is 24mm, corresponding to a 35mm stills camera.
    _____________________
    [][][][][][][][][][][              ^
     \     |         |  \      ^       |
      \    |         |   \    24mm   35mm
       \   |         |    \    v       |
       ][][][][][][][][][][]           v
       ---------------------
           <- 36mm -->
 
    Changing the aperture will update the field of view property with respect to 
    the focal length. The horizontal aperture can be calculated from the aspect 
    property.
 
    @property sensorAspect
    aspect ratio of width versus height of the sensor aperture. The default is 
    36mm/24mm, ie: 1.5.
 
    @property sensorEnlargement

    The sensor enlargment property scales the active region of the sensor. A 
    zoom factor of 2 will result in the central portion of the image being 
    cropped and expanded to fill the image plane. The default is 1.
 
    @property sensorShift
    
    The sensor shift property moves the center of the sensor relative to the 
    lens. This is useful in certain calculations, such as shadow or reflection
    projections, as well as to provide vergence in a parallel stereoscopic camera.

 5. Exposure
 
    Finally, the sensor values need to be converted for display.
 
    @property flash
 
    Flashing is applied to a film stock some time before processing. It is a 
    small and even level of exposure added to the entire image intended shift 
    the brightness and color of darker areas of the image. Since exposure is 
    logarithmic, flash does not affect midtones or highlights.
    
    The equivalent to flash in a color grading system is known as lift. Typically 
    red, green, and blue can be controlled independently.
 
    A negative value for flash can be used to subtract color.
 
    @property exposure
 
    Finally, exposure should be applied to the compressed value. Red,
    green, and blue exposure can be specified separately. The default is 1.0.

    @property exposureCompression
 
    Gamma curve compression where values below the x value are to be passed through,
    about the y value, values are to be clamped at maximum display brightness,
    and a function such as a logarithmic ramp is to be applied in between. The
    default is (1,0, 1.0).

    A displayable value is therefore obtained via
       pow(exposureCompression((sensor value + flash) * exposure), displayGamma)

 */

typedef NS_ENUM(NSUInteger, MDLCameraProjection)
{
    MDLCameraProjectionPerspective = 0,
    MDLCameraProjectionOrthographic = 1,
};


NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLCamera : MDLObject

/**
 The projection matrix is calculated from the near and far visibility distances,
 and the field of view.
 @see nearVisibilityDistance, nearVisibilityDistance
 */
@property (nonatomic, readonly) matrix_float4x4 projectionMatrix;

/**
 */
@property (nonatomic, assign) MDLCameraProjection projection;

/**
 Move the camera back and orient the camera so that a bounding box is framed 
 within the current field of view. Uses the Y axis as up.
 If setNearAndFar is YES, the near and far visibility distances will be set.
 */
- (void)frameBoundingBox:(MDLAxisAlignedBoundingBox)boundingBox setNearAndFar:(BOOL)setNearAndFar;

/**
 Orient the camera so that the camera points at focusPosition. Assumes that the 
 Y axis is up.
 */
- (void)lookAt:(vector_float3)focusPosition;

/**
 Set the position of the camera and orient it so that it points at focusPosition. 
 Assumes that the Y axis is up.
 */
- (void)lookAt:(vector_float3)focusPosition from:(vector_float3)cameraPosition;

/**
 A convenience function to calculate a ray from the camera to a pixel in a 
 viewport of a given size
 */
- (vector_float3)rayTo:(vector_int2)pixel forViewPort:(vector_int2)size;

/**
 Bounding distance for visible objects 
 */
@property (nonatomic, assign) float nearVisibilityDistance;
@property (nonatomic, assign) float farVisibilityDistance;

/**
 World to meters conversion scale. Required for certain calculations.
 */
@property (nonatomic, assign) float worldToMetersConversionScale;

/**
 Radial distortion of the lens, second order term
 */
@property (nonatomic, assign) float barrelDistortion;

/**
 Radial distortion of the lens, fourth order term
 */
@property (nonatomic, assign) float fisheyeDistortion;

/**
 Amount of optical vignetting, rom zero to one.
 */
@property (nonatomic, assign) float opticalVignetting;

/**
 Amount of chromatic abberation, from zero to one.
 */
@property (nonatomic, assign) float chromaticAberration;

/**
 Lens focal length in mm.
 @see fieldOfView
 */
@property (nonatomic, assign) float focalLength;

/**
 Focus distance
 */
@property (nonatomic, assign) float focusDistance;

/**
 The field of view, in degrees.
 @see focalLength
 */
@property (nonatomic, assign) float fieldOfView;

/**
 f-stop, default is 5.6
 */
@property (nonatomic, assign) float fStop;

/**
  Aperture blade count, where zero indicates a circle.
 */
@property (nonatomic, assign) NSUInteger apertureBladeCount;

/**
 Maximum circle of confusion size in mm on the image plane
 */
@property (nonatomic, assign) float maximumCircleOfConfusion;

/**
 Create a bokeh kernel corresponding to the apertureBladeCount
 */
- (MDLTexture *)bokehKernelWithSize:(vector_int2)size;

/**
 Shutter open interval, in seconds
 */
@property (nonatomic, assign) NSTimeInterval shutterOpenInterval;

/**
 vertical aperture of the sensor or film gate, default is 24mm
 @see sensorAspect
*/
@property (nonatomic, assign) float sensorVerticalAperture;

/** 
 Sensor or film gate aperture aspect ratio, default is 1.5
 @see sensorVerticalAperture
 */
@property (nonatomic, assign) float sensorAspect;

/** 
 Sensor zoom factor
 */
@property (nonatomic, assign) vector_float2 sensorEnlargement;

/**
 Sensor shift factor in mm.
 */
@property (nonatomic, assign) vector_float2 sensorShift;

/**
 Flash amount, unit less
 */
@property (nonatomic, assign) vector_float3 flash;

/**
 exposure curve compression where values below the x value are to be passed through,
 above the y value, values are to be clamped at maximum display brightness, and a
 function such as a logarithmic ramp is to be applied in between.
 */
@property (nonatomic, assign) vector_float2 exposureCompression;

/**
 Exposure amount, unit less
 */
@property (nonatomic, assign) vector_float3 exposure;


@end


NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLStereoscopicCamera : MDLCamera

/**
 Inter-pupillary distance in mm.
 Default is 63mm.
 */
@property (nonatomic, assign) float interPupillaryDistance;

/**
 Vergence in a stereoscopic camera can be controlled in two ways. A toed-in 
 binocular stereoscopic camera rotates the lens and sensor together such that a 
 ray projected from the center of either sensor and lens meets at a point. A 
 parallel binocular stereoscopic camera accomplishes the same thing by shifting 
 the relative centers of the sensor and lens.
 
 If a parallel binocular stereoscopic camera is modeled, the sensor should be 
 considered to have shifted by an amount h. If left and right vergence are equal,
   h = (focal length * interOcularDistance) / distance to vergence point.
 
 Vergence is measured in degrees towards center and is usually positive.
 */

@property (nonatomic, assign) float leftVergence;
@property (nonatomic, assign) float rightVergence;

/**
 The amount, as a percentage of image width to offset an image towards the other 
 camera. This value is used in a stereo grade to enhance or reduce the intensity 
 of the stereoscopic effect
 */
@property (nonatomic, assign) float overlap;

/**
 Convenience utilities to create view and projection matrices. The view matrix
 calculations requires that the world to meters conversion scale be set.
 
 @see worldToMetersConversionScale
 */
@property (nonatomic, readonly) matrix_float4x4 leftViewMatrix;
@property (nonatomic, readonly) matrix_float4x4 rightViewMatrix;
@property (nonatomic, readonly) matrix_float4x4 leftProjectionMatrix;
@property (nonatomic, readonly) matrix_float4x4 rightProjectionMatrix;



@end

NS_ASSUME_NONNULL_END

