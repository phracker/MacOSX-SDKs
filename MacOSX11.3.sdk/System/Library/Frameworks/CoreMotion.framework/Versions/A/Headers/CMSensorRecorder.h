/*
 *  CMSensorRecorder.h
 *  CoreMotion
 *
 *  Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMRecordedAccelerometerData.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMSensorDataList
 *
 * Discussion:
 *   Allows retrospective access to sensor data via enumeration.
 *   If created with accelerometerDataFromDate:toDate:
 *   each enumeration will yield an object of type CMRecordedAccelerometerData.
 *   Due to the large number of samples that can be processed, the
 *   enumeration should not be run on the main/UI thread.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(9.0), watchos(2.0)) API_UNAVAILABLE(macos)
@interface CMSensorDataList : NSObject <NSFastEnumeration>
@end

/*
 * CMSensorRecorder
 *
 * Discussion:
 *    CMSensorRecorder allows applications to record sensor data for periods
 *    during which the application is not active.  This data is then made
 *    available for later access (up to 3 days) when the application
 *    is run at a later time.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(9.0), watchos(2.0)) API_UNAVAILABLE(macos)
@interface CMSensorRecorder : NSObject

/*
 * isAccelerometerRecordingAvailable
 *
 * Discussion:
 *   Determines whether accelerometer recording is available.
 */
+ (BOOL)isAccelerometerRecordingAvailable;

/*
 * authorizationStatus
 *
 * Discussion:
 *   Returns the current authorization status for sensor recording.
 */
+ (CMAuthorizationStatus)authorizationStatus COREMOTION_EXPORT API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

/*
 * isAuthorizedForRecording
 *
 * Discussion:
 *   Determines whether the application is authorized for sensor recording.
 */
+ (BOOL)isAuthorizedForRecording __API_DEPRECATED_WITH_REPLACEMENT("authorizationStatus", ios(9_0, 11_0), watchos(2_0, 4_0));

/*
 * accelerometerDataFromDate:ToDate:
 *
 * Discussion:
 *    Gives access to recorded accelerometer samples given a time range (fromDate, toDate].
 *    A total duration of 12 hours of data can be requested at any one time.  Data can be delayed
 *    for up to 3 minutes before being available for retrieval.  An instance of CMSensorDataList
 *    should only be enumerated from a single thread.
 */
- (nullable CMSensorDataList *)accelerometerDataFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

/*
 * recordAccelerometerForDuration:
 *
 * Discussion:
 *    Starts recording accelerometer data for the duration given at 50hz.  Data can be recorded
 *    for up to 12 hours.
 */
- (void)recordAccelerometerForDuration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END
