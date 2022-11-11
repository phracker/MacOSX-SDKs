/*
 *  CMRotationRateData.h
 *  CoreMotion
 *
 *  Copyright (c) 2020 Apple Inc. All rights reserved.
 *
 */

#import <CoreMotion/CMGyro.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMRotationRateData
 *
 *  Discussion:
 *    Contains a single rotation rate measurement.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos)
@interface CMRotationRateData : CMLogItem
{
@private
	id _internal;
}

/*
 *  rotationRate
 *
 *  Discussion:
 *    The rotation rate as measured by the gyro.
 *
 */
@property (readonly, nonatomic) CMRotationRate rotationRate;

@end

/*
 * CMRecordedRotationRateData
 *
 * Discussion:
 *   CMRecordedRotationRateData contains data for each rotation rate sample.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos)
@interface CMRecordedRotationRateData : CMRotationRateData

/*
 * startDate
 *
 * Discussion:
 *   Time at which the rotation rate was observed.
 *
 */
@property (readonly) NSDate *startDate;

@end

NS_ASSUME_NONNULL_END
