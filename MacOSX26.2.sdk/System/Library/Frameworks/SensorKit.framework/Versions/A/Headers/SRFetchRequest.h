//
//  SRFetchRequest.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <SensorKit/SRAbsoluteTime.h>
#import <SensorKit/SRDevice.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos)
@interface SRFetchRequest : NSObject

/**
 * @brief Fetch data starting after this time.
 * @discussion This value must be specified for a valid request to be performed.
 * If it is not specified, this will result in a SRErrorInvalidRequest error in the
 * -sensorReader:fetchingRequest:failedWithError: SRSensorReaderDelegate callback.
 *
 * The time range for fetching will be exclusive of start time and inclusive of end time:
 * (start, end] . An SRSensorReader can use this to continue fetching a stream of
 * data based on the last sample timestamp they have read.
 */
@property (assign) SRAbsoluteTime from;

/**
 * @brief Fetch data ending at this time.
 * @discussion This value must be specified for a valid request to be performed.
 * If it is not specified, this will result in a SRErrorInvalidRequest error in the
 * -sensorReader:fetchingRequest:failedWithError: SRSensorReaderDelegate callback.
*/
@property (assign) SRAbsoluteTime to;

/**
 * @brief Fetch data generated on this device
 * @discussion If this is not specified, the current device will be used.
 */
@property (strong) SRDevice *device;

@end

NS_ASSUME_NONNULL_END
