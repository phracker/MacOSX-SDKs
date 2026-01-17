/*
*  CMWaterSubmersionManager.h
*  CoreMotion
*
*  Copyright (c) 2021 Apple Inc. All rights reserved.
*/
#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>
#import <CoreMotion/CMWaterSubmersionData.h>

NS_ASSUME_NONNULL_BEGIN

@class CMWaterSubmersionManager;

COREMOTION_EXPORT API_AVAILABLE(watchos(9.0), ios(16.0)) API_UNAVAILABLE(macos, tvos, macCatalyst)
/*
 * CMWaterSubmersionManagerDelegate
 *
 * Discussion:
 *   	Delegate protocol to receive updates from the CMWaterSubmersionManager API.  Methods will be invoked
 *      on the main queue.
 */
@protocol CMWaterSubmersionManagerDelegate<NSObject>

/*
 * manager:didUpdateEvent
 *
 * Discussion:
 *     Delegate method is called when there is a new event available.
 *     When the delegate is first set, this method will invoked immediately so
 *     that the client always has the current state.
 */
- (void)manager:(CMWaterSubmersionManager*)manager didUpdateEvent:(CMWaterSubmersionEvent*)event;

/*
 * manager:didUpdateMeasurement:
 *
 * Discussion:
 * 	   Delegate method is called when there is a new depth/pressure measurement available. When
 *     the device is not in the Submerged state, the measurement will only include the surface
 *     pressure and submersion state.
 *
 *
 */
- (void)manager:(CMWaterSubmersionManager*)manager didUpdateMeasurement:(CMWaterSubmersionMeasurement*)measurement;

/*
 * manager:didUpdateTemperature:
 *
 * Discussion:
 * 	   Delegate method is called when there is a new temperature measurement available.
 *     New measurements will only be available while device is in the WaterSubmerged state.
 */
- (void)manager:(CMWaterSubmersionManager*)manager didUpdateTemperature:(CMWaterTemperature*)measurement;

/*
 * manager:errorOccurred:
 * Discussion:
 * 	   Delegate method is called when an error has occurred.
 */
- (void)manager:(CMWaterSubmersionManager*)manager errorOccurred:(NSError*)error;
@end

COREMOTION_EXPORT API_AVAILABLE(watchos(9.0), ios(16.0)) API_UNAVAILABLE(macos, tvos, macCatalyst)
/*
 *  CMWaterSubmersionManager
 *
 *  Discussion:
 *  	API to retrieve values related to device state with respect to water
 * 		submersion and measurements updates when device is submerged.
 */
@interface CMWaterSubmersionManager : NSObject
/*
 *  delegate
 *
 *  Discussion:
 *      The delegate object to receive event and measurements updates.
 *      Setting of the delegate will invoke TCC, and updates are subject
 *      to client being authorized.  By setting the delegate to a non-nil value,
 *      start event and measurement updates.  Setting the delegate to nil will
 *      stop all updates.
 */
@property (weak, nonatomic, nullable) id <CMWaterSubmersionManagerDelegate> delegate;

/*
 *  waterSubmersionAvailable
 *
 *  Discussion:
 *   	Determines whether this feature is available on the current platform.
 */
@property (class, nonatomic, readonly) BOOL waterSubmersionAvailable;

/*
 *  authorizationStatus
 *
 *  Discussion:
 *      Checks to see if the client is authorized to use this API via TCC
 *      under Motion & Fitness.
 */
@property (class, nonatomic, readonly) CMAuthorizationStatus authorizationStatus;

/*
 *  maximumDepth
 *
 *  Discussion:
 *      Returns the maximum depth threshold that this client is authorized to
 *      receive. This is the threshold at which the API will change state
 *      to CMWaterSubmersionDepthStatePastMaxDepth. The API will continue
 *      to vend data until CMWaterSubmersionDepthStateSensorDepthError, 10%
 *      above this threshold.
 *
 *      Returns nil if client is not authorized for submersion data.
 */
@property (nonatomic, readonly, nullable) NSMeasurement<NSUnitLength *> *maximumDepth;
@end

NS_ASSUME_NONNULL_END
