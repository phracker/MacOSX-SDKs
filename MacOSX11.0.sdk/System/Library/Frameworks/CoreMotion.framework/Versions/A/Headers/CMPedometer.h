/*
 *  CMPedometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMPedometerData
 *
 *  Discussion:
 *      A description of the user's pedestrian activity. At a minimum this
 *      object contains a step count. On supported platforms it also contains
 *      distance, flights of stairs, pace, and cadence.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(8.0))
@interface CMPedometerData : NSObject <NSSecureCoding, NSCopying>

/*
 *  startDate
 *
 *  Discussion:
 *      The start time of the period for which the pedometer data is valid.
 *
 *      This is the start time requested for the session or historical query.
 */
@property(readonly, nonatomic) NSDate *startDate;

/*
 *  endDate
 *
 *  Discussion:
 *      The end time of the period for which the pedometer data is valid.
 *
 *      For updates this is the time for the most recent update. For historical
 *      queries this is the end time requested.
 */
@property(readonly, nonatomic) NSDate *endDate;

/*
 *  numberOfSteps
 *
 *  Discussion:
 *      Number of steps taken by the user.
 */
@property(readonly, nonatomic) NSNumber *numberOfSteps;

/*
 *  distance
 *
 *  Discussion:
 *      Estimated distance in meters traveled by the user while walking and
 *      running. Value is nil unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *distance;

/*
 *  floorsAscended
 *
 *  Discussion:
 *      Approximate number of floors ascended by way of stairs. Value is nil
 *      on unsupported platforms.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsAscended;

/*
 *  floorsDescended
 *
 *  Discussion:
 *      Approximate number of floors descended by way of stairs. Value is nil
 *      on unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsDescended;

/*
 * currentPace
 *
 *
 * Discussion:
 *      For updates this returns the current pace, in s/m (seconds per meter).
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentPace COREMOTION_EXPORT API_AVAILABLE(ios(9.0));

/*
 * currentCadence
 *
 *
 * Discussion:
 *      For updates this returns the rate at which steps are taken, in steps per second.
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentCadence COREMOTION_EXPORT API_AVAILABLE(ios(9.0));

/*
 * averageActivePace
 *
 *
 * Discussion:
 *
 *      For updates this returns the average active pace since
 *      startPedometerUpdatesFromDate:withHandler:, in s/m (seconds per meter).
 *      For historical queries this returns average active pace between startDate
 *      and endDate. The average active pace omits the non-active time, giving
 *      the average pace from when the user was moving. Value is nil if any of
 *      the following are true:
 *
 *         (1) (For historical queries) this information is not available,
 *             e.g. the user did not move between startDate and endDate;
 *         (2) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *averageActivePace COREMOTION_EXPORT API_AVAILABLE(ios(10.0));

@end

/*
 *  CMPedometerEventType
 *
 *  Discussion:
 *      Events describing the transitions of pedestrian activity.
 */
typedef NS_ENUM(NSInteger, CMPedometerEventType) {
	CMPedometerEventTypePause,
	CMPedometerEventTypeResume
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*
 *  CMPedometerEvent
 *
 *  Discussion:
 *      An event marking the change in user's pedestrian activity.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(10.0), watchos(3.0))
@interface CMPedometerEvent : NSObject <NSSecureCoding, NSCopying>

/*
 *  date
 *
 *  Discussion:
 *      The time of occurence of event.
 */
@property(readonly, nonatomic) NSDate *date;

/*
 *  type
 *
 *  Discussion:
 *      Event type describing the transition of pedestrian activity.
 */
@property(readonly, nonatomic) CMPedometerEventType type;

@end

/*
 *  CMPedometerHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked when pedometer data is available. Error
 *      types are defined in "CMError.h".
 */
typedef void (^CMPedometerHandler)(CMPedometerData * __nullable pedometerData, NSError * __nullable error);

/*
 *  CMPedometerEventHandler
 *
 *  Discussion:
 *      Typedef of block that will be invoked when pedometer event is available.
 *      Error types are defined in "CMError.h".
 */
typedef void (^CMPedometerEventHandler)(CMPedometerEvent * __nullable pedometerEvent, NSError * __nullable error) COREMOTION_EXPORT API_AVAILABLE(ios(10.0), watchos(3.0));

/*
 *  CMPedometer
 *
 *  Discussion:
 *      CMPedometer allows access to the user's pedestrian activity. The
 *      activity can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the pedometer data is
 *      tabulated and returned.
 *      (See queryPedometerDataFromDate:toDate:withHandler:)
 *
 *      2. By providing a block to startPedometerUpdatesFromDate:withHandler:,
 *      pedometer updates will be provided on a best effort basis. Pedometer
 *      updates can be stopped by calling stopPedometerUpdates.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(8.0))
@interface CMPedometer : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting functionality.
 */
+ (BOOL)isStepCountingAvailable;

/*
 *  isDistanceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports distance estimation
 *      in addition to step counting.
 */
+ (BOOL)isDistanceAvailable;

/*
 *  isFloorCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports counting flights of stairs
 *      in addition to step counting.
 */
+ (BOOL)isFloorCountingAvailable;

/*
 *  isPaceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports pace estimation
 *      in addition to step counting.
 */
+ (BOOL)isPaceAvailable COREMOTION_EXPORT API_AVAILABLE(ios(9.0));

/*
 *  isCadenceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports cadence estimation
 *      in addition to step counting.
 */
+ (BOOL)isCadenceAvailable COREMOTION_EXPORT API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos);

/*
 *  isPedometerEventTrackingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports pedometer events.
 */
+ (BOOL)isPedometerEventTrackingAvailable COREMOTION_EXPORT API_AVAILABLE(ios(10.0), watchos(3.0)) API_UNAVAILABLE(macos);

/*
 *  authorizationStatus
 *
 *  Discussion:
 *      Returns the current authorization status for pedometer.
 */
+ (CMAuthorizationStatus)authorizationStatus COREMOTION_EXPORT API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos);

/*
 *  queryPedometerDataFromDate:toDate:withHandler:
 *
 *  Discussion:
 *      Queries for the user's pedestrian activity in the given time range. Data
 *      is available for up to 7 days. The data returned is computed from a
 *      system-wide history that is continuously being collected in the
 *      background. The result is returned on a serial queue.
 */
- (void)queryPedometerDataFromDate:(NSDate *)start
							toDate:(NSDate *)end
					   withHandler:(CMPedometerHandler)handler;

/*
 *  startPedometerUpdatesFromDate:withHandler:
 *
 *  Discussion:
 *      Starts a series of continuous pedometer updates to the
 *      handler on a serial queue. For each update, the app
 *      will receive the cumulative pedestrian activity since the
 *      start date specified and the timestamp associated with the
 *      latest determination. If the app is backgrounded and resumed
 *      at a later time, the app will receive all of the pedestrian
 *      activity accumulated during the background period in the
 *      very next update.
 */
- (void)startPedometerUpdatesFromDate:(NSDate *)start
						  withHandler:(CMPedometerHandler)handler;

/*
 *  stopPedometerUpdates
 *
 *  Discussion:
 *      Stops pedometer updates.
 */
- (void)stopPedometerUpdates;

/*
 *  startPedometerEventUpdatesWithHandler:
 *
 *  Discussion:
 *      Starts pedometer event updates on a serial queue.
 *      Events are available only when the apps are running in foreground / background.
 */
- (void)startPedometerEventUpdatesWithHandler:(CMPedometerEventHandler)handler COREMOTION_EXPORT API_AVAILABLE(ios(10.0), watchos(3.0)) API_UNAVAILABLE(macos);

/*
 *  stopPedometerEventUpdates
 *
 *  Discussion:
 *      Stops pedometer event updates.
 */
- (void)stopPedometerEventUpdates COREMOTION_EXPORT API_AVAILABLE(ios(10.0), watchos(3.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
