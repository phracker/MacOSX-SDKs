#if !__has_include(<AVFCore/AVSpatialVideoConfiguration.h>)
/*
	File:  AVSpatialVideoConfiguration.h

	Framework:  AVFoundation
 
	Copyright 2025-2035 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

/// An AVSpatialVideoConfiguration specifies spatial video properties.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface AVSpatialVideoConfiguration: NSObject

/// Specifies intrinsic and extrinsic parameters for single or multiple lenses.
///
/// The property value is an array of dictionaries describing the camera calibration data for each lens. The camera calibration data includes intrinsics and extrinics with other parameters.  This property is only applicable when the projection kind is kCMTagProjectionTypeParametricImmersive.  Can be nil if the value is unknown.
@property (atomic, copy, nullable) NSArray<NSDictionary<NSString *, id> *> * cameraCalibrationDataLensCollection;

/// Specifies horizontal field of view in thousandths of a degree. Can be nil if the value is unknown.
@property (atomic, copy, nullable) NSNumber *horizontalFieldOfView;

/// Specifies the distance between centers of the lenses of the camera system that created the video.
///
/// The distance is in micrometers or thousandths of a millimeter. Can be nil if the value is unknown.
@property (atomic, copy, nullable) NSNumber *cameraSystemBaseline;

/// Specifies a relative shift of the left and right images, which changes the zero parallax plane.
///
/// The value is in normalized image space and measured over the range of -10000 to 10000 mapping to the uniform range [-1.0...1.0]. The interval of 0.0 to 1.0 or 0 to 10000 maps onto the stereo eye view image width. The negative interval 0.0 to -1.0 or 0 to -10000 similarly map onto the stereo eye view image width. Can be nil if the value is unknown.
@property (atomic, copy, nullable) NSNumber *disparityAdjustment;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Initializes an AVSpatialVideoConfiguration with a format description.
///
/// The format description is not stored.
/// - Parameter formatDescription: Format description to use to initialize the AVSpatialVideoConfiguration.
///
/// - Returns: An instance of AVSpatialVideoConfiguration
- (instancetype)initWithFormatDescription:(CMFormatDescriptionRef)formatDescription;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSpatialVideoConfiguration.h>
#endif
