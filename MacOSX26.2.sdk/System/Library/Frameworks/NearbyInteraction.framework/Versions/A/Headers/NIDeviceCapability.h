//
//  NIDeviceCapability.h
//  NearbyInteraction
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@protocol NIDeviceCapability

/**
 Whether or not this device is capable of participating in a nearby interaction session with precise ranging
 */
@property (nonatomic, readonly) BOOL supportsPreciseDistanceMeasurement;

/**
 Whether or not this device is capable of participating in a nearby interaction session with instantaneous direction
 */
@property (nonatomic, readonly) BOOL supportsDirectionMeasurement;

/**
 Whether or not this device is capable of participating in a nearby interaction session with camera assistance
 */
@property (nonatomic, readonly) BOOL supportsCameraAssistance;

/**
 Whether or not this device is capable of extended distance measurement capabilities
 */
@property (nonatomic, readonly) BOOL supportsExtendedDistanceMeasurement API_AVAILABLE(ios(17.0), watchos(10.0), macos(14.0), tvos(17.0));


/**
 Whether or not this device is capable of participating in a nearby interaction DL-TDOA ranging.
 */
@property (nonatomic, readonly) BOOL supportsDLTDOAMeasurement API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

@end

NS_ASSUME_NONNULL_END
