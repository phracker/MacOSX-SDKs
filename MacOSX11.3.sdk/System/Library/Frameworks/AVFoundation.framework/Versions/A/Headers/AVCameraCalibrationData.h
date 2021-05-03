#if !__has_include(<AVFCapture/AVCameraCalibrationData.h>)
/*
    File:  AVCameraCalibrationData.h
 
    Framework:  AVFoundation
 
    Copyright 2016-2017 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <simd/matrix_types.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCameraCalibrationDataInternal;

/*!
 @class AVCameraCalibrationData
 @abstract
    AVCameraCalibrationData is a model object describing a camera's calibration information.
 
 @discussion
    When rendering effects to images produced by cameras, or performing computer vision tasks such as correcting images for geometric distortions, it is necessary to characterize the camera's calibration information, such as its pixel focal length, principal point, lens distortion characteristics, etc. AVCameraCalibrationData provides this information.
 */
API_AVAILABLE(macos(10.13), ios(11.0), macCatalyst(14.0), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface AVCameraCalibrationData : NSObject
{
@private
    AVCameraCalibrationDataInternal *_internal;
}

AV_INIT_UNAVAILABLE

/*!
 @property intrinsicMatrix
 @abstract
    A camera's intrinsic (K) matrix describes its geometric properties.
 
 @discussion
    The intrinsic matrix allows one to transform 3D coordinates to 2D coordinates on an image plane using the pinhole camera model. All values are expressed in pixels. The elements in the matrix are:
       /           \
       | fx 0   ox |
       | 0  fy  oy |
       | 0  0   1  |
       \           /
    where fx and fy describe the focal length. For square pixels, their values are identical.
    ox and oy are the offset of the principal point. The origin is the upper left of the frame.
 */
@property(nonatomic, readonly) matrix_float3x3 intrinsicMatrix;

/*!
 @property intrinsicMatrixReferenceDimensions
 @abstract
    The reference frame dimensions used in calculating a camera's principal point.
 
 @discussion
    A camera's intrinsic matrix expresses values in pixels with respect to a frame of this width and height.
 */
@property(nonatomic, readonly) CGSize intrinsicMatrixReferenceDimensions;

/*!
 @property extrinsicMatrix
 @abstract
    A camera's extrinsic matrix describes its pose (position and direction) in world coordinates.
 
 @discussion
    The extrinsic matrix consists of a unitless 3x3 rotation matrix (R) on the left and a translation (t) 3x1 column vector on the right. The translation vector's units are millimeters. The camera's pose is expressed with respect to a reference camera (camera-to-world view). If the rotation matrix is an identity matrix, then this camera is the reference camera. Note that a matrix_float4x3 matrix is column major with 3 rows and 4 columns.
               /                       \
       /   \   | r1,1  r1,2  r1,3 | t1 |
       |R|t| = | r2,1  r2,2  r2,3 | t2 |
       \   /   | r3,1  r3,2  r3,3 | t3 |
               \                       /
 */
@property(nonatomic, readonly) matrix_float4x3 extrinsicMatrix;

/*!
 @property pixelSize
 @abstract
    The size of one pixel at intrinsicMatrixReferenceDimensions in millimeters.
 */
@property(nonatomic, readonly) float pixelSize;

/*!
 @property lensDistortionLookupTable
 @abstract
    An NSData of floats describing the camera lens' radial distortions.
 
 @discussion
    Images captured by a camera are geometrically warped by radial distortions in the lens. In order to project from the 2D image plane back into the 3D world, the images must be distortion corrected, or made rectilinear. Lens distortion is modeled using a one-dimensional lookup table of 32-bit float values evenly distributed along a radius from the center of the distortion to the farthest corner, with each value representing an elongation or compression of the radius (0.0 for any given point indicates no elongation). This model assumes radially symmetric lens distortion. When dealing with AVDepthData, the disparity / depth map representations are geometrically distorted to align with images produced by the camera. For more information, see the reference implementation below.
 
    If the camera lacks the calibration data needed to accurately characterize lens distortions, this property's value is nil.
 */
@property(nullable, nonatomic, readonly) NSData *lensDistortionLookupTable;

/*!
 @property inverseLensDistortionLookupTable
 @abstract
    An NSData of floats describing the inverse lookup table required to reapply the camera lens' radial distortions to a rectified image.
 
 @discussion
    See lensDistortionLookupTable. If you've rectified an image by removing the distortions characterized by the lensDistortionLookupTable, and now wish to go back to geometrically distorted, you may use the inverseLensDistortionLookupTable. For more information, see the reference implementation below.
 
    If the camera lacks the calibration data needed to accurately characterize lens distortions, this property's value is nil.
 */
@property(nullable, nonatomic, readonly) NSData *inverseLensDistortionLookupTable;

/*!
 @property lensDistortionCenter
 @abstract
    A CGPoint describing the offset of the lens’ distortion center from the top left in intrinsicMatrixReferenceDimensions.
 
 @discussion
    Due to geometric distortions in the image, the center of the distortion may not be equal to the optical center (principal point) of the lens. When making an image rectilinear, the distortion center should be used rather than the optical center of the image. For more information, see the reference implementation below.
 
    If the camera lacks the calibration data needed to accurately characterize lens distortions, this property's value is set to CGPointZero and should not be used.
 */
@property(nonatomic, readonly) CGPoint lensDistortionCenter;

/*
    The following reference implementation illustrates how to use the lensDistortionLookupTable, inverseLensDistortionLookupTable, and lensDistortionCenter properties to find points in the lens-distorted or undistorted (rectilinear, corrected) space. If you have a distorted image (such as a photo taken by a camera) and want to find a particular point in a corresponding undistorted image, you would call the sample method below using the inverseLensDistortionLookupTable. If you have an undistorted (aka distortion-corrected) image and want to find a point in the distorted image's space, you would call the sample method below using the lensDistortionLookupTable.
 
    To apply distortion correction to an image, you'd begin with an empty destination buffer and iterate through it row by row, calling the sample implementation below for each point in the output image, passing the lensDistortionLookupTable to find the corresponding value in the distorted image, and write it to your output buffer. Please note that the "point", "opticalCenter", and "imageSize" parameters below must be in the same coordinate system, i.e. both at full resolution, or both scaled to a different resolution but with the same aspect ratio.
 
    The reference function below returns floating-point x and y values. If you wish to match the results with actual pixels in a bitmap, you should either round to the nearest integer value or interpolate from surrounding integer positions (i.e. bilinear interpolation from the 4 surrounding pixels).
 
- (CGPoint)lensDistortionPointForPoint:(CGPoint)point
                           lookupTable:(NSData *)lookupTable
               distortionOpticalCenter:(CGPoint)opticalCenter
                             imageSize:(CGSize)imageSize
{
    // The lookup table holds the relative radial magnification for n linearly spaced radii.
    // The first position corresponds to radius = 0
    // The last position corresponds to the largest radius found in the image.
 
    // Determine the maximum radius.
    float delta_ocx_max = MAX( opticalCenter.x, imageSize.width  - opticalCenter.x );
    float delta_ocy_max = MAX( opticalCenter.y, imageSize.height - opticalCenter.y );
    float r_max = sqrtf( delta_ocx_max * delta_ocx_max + delta_ocy_max * delta_ocy_max );
 
    // Determine the vector from the optical center to the given point.
    float v_point_x = point.x - opticalCenter.x;
    float v_point_y = point.y - opticalCenter.y;
 
    // Determine the radius of the given point.
    float r_point = sqrtf( v_point_x * v_point_x + v_point_y * v_point_y );
 
    // Look up the relative radial magnification to apply in the provided lookup table
    float magnification;
    const float *lookupTableValues = lookupTable.bytes;
    NSUInteger lookupTableCount = lookupTable.length / sizeof(float);
 
    if ( r_point < r_max ) {
        // Linear interpolation
        float val   = r_point * ( lookupTableCount - 1 ) / r_max;
        int   idx   = (int)val;
        float frac  = val - idx;
 
        float mag_1 = lookupTableValues[idx];
        float mag_2 = lookupTableValues[idx + 1];
 
        magnification = ( 1.0f - frac ) * mag_1 + frac * mag_2;
    }
    else {
        magnification = lookupTableValues[lookupTableCount - 1];
    }
 
    // Apply radial magnification
    float new_v_point_x = v_point_x + magnification * v_point_x;
    float new_v_point_y = v_point_y + magnification * v_point_y;
 
    // Construct output
    return CGPointMake( opticalCenter.x + new_v_point_x, opticalCenter.y + new_v_point_y );
}
 */

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCameraCalibrationData.h>
#endif
