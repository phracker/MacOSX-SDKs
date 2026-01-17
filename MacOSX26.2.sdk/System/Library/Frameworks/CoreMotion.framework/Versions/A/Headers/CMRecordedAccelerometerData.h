/*
 *  CMRecordedAccelerometerData.h
 *  CoreMotion
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 */

#import <CoreMotion/CMAccelerometer.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMRecordedAccelerometerData
 *
 * Discussion:
 *   CMRecordedAccelerometerData contains data for each accelerometer sample.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(9.0), watchos(2.0)) API_UNAVAILABLE(macos)
@interface CMRecordedAccelerometerData : CMAccelerometerData

/*
 * identifier
 *
 * Discussion:
 *   Unique identifier that identifies the batch for which the accelerometer sample
 *   was recorded in. This identifier will be monotonically increased
 *   for each new sensor batch recorded and can be used as an anchor for future queries.
 */
@property (readonly) uint64_t identifier;

/*
 * startDate
 *
 * Discussion:
 *   Time at which the acceleration measurement was observed.
 *
 */
@property (readonly) NSDate *startDate;

@end

NS_ASSUME_NONNULL_END
