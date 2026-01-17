//
//  NIDLTDOAMeasurement.h
//  NearbyInteraction
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>
#import <simd/simd.h>

/**
 The coordinate types of DL-TDOA measurement updates that Nearby Interaction supports.
 */

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
typedef NS_ENUM(NSInteger, NIDLTDOACoordinatesType) {
    NIDLTDOACoordinatesTypeGeodetic = 0,
    NIDLTDOACoordinatesTypeRelative = 1,
};

/**
 The measurement types of DL-TDOA measurement updates that Nearby Interaction supports.
 */

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
typedef NS_ENUM(NSInteger, NIDLTDOAMeasurementType) {
    NIDLTDOAMeasurementTypePoll     = 0,
    NIDLTDOAMeasurementTypeResponse = 1,
    NIDLTDOAMeasurementTypeFinal    = 2,
};

/**
 Represents a single measurement relative to a DL-TDOA anchor.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst)
NI_EXPORT
@interface NIDLTDOAMeasurement : NSObject <NSCopying, NSSecureCoding>
/**
 Indicates the address of anchor of this measurement.
*/
@property (nonatomic, assign, readonly) NSUInteger address;

/**
 Indicates the type of this measurement.
*/
@property (nonatomic, assign, readonly) NIDLTDOAMeasurementType measurementType;

/**
 Indicates the transmission timestamp (in seconds).
*/
@property (nonatomic, assign, readonly) double transmitTime;

/**
 Indicates the reception timestamp (in seconds).
*/
@property (nonatomic, assign, readonly) double receiveTime;

/**
 Indicates the signal strength in dBm.
*/
@property (nonatomic, assign, readonly) double signalStrength;

/**
 Indicates the estimated carrier frequency offset (dimensionless).
*/
@property (nonatomic, assign, readonly) double carrierFrequencyOffset;

/**
 Inidicates the type of coordinates of this anchor.
*/
@property (nonatomic, assign, readonly) NIDLTDOACoordinatesType coordinatesType;

/**
 Indicates the anchor's coordinates:

 When coordinatesType == NIDLTDOACoordinatesTypeGeodetic:
    coordinates represent geodetic position in 3D space with format {latitude, longitude, altitude}.
 When coordinatesType == NIDLTDOACoordinatesTypeRelative:
    coordinates represent distances from anchor(s) along the 3 axes in 3D space  with format {x, y, z}.
 */
@property (nonatomic, assign, readonly) simd_double3 coordinates;

/** Unavailable  */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end
