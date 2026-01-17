//
//  HKWorkoutSession.h
//  HealthKit
//
//  Copyright (c) 2015-2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKLiveWorkoutBuilder.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKWorkout.h>
#import <HealthKit/HKWorkoutActivity.h>
#import <HealthKit/HKWorkoutBuilder.h>
#import <HealthKit/HKWorkoutConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKLiveWorkoutBuilder;
@class HKQuantityType;
@protocol HKWorkoutSessionDelegate;

/*!
 @enum          HKWorkoutSessionState
 @abstract      This enumerated type is used to represent the state of a workout session.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionState) {
    HKWorkoutSessionStateNotStarted = 1,
    HKWorkoutSessionStateRunning,
    HKWorkoutSessionStateEnded,
    HKWorkoutSessionStatePaused API_AVAILABLE(watchos(3.0)),
    HKWorkoutSessionStatePrepared API_AVAILABLE(watchos(5.0)),
    HKWorkoutSessionStateStopped API_AVAILABLE(watchos(5.0)),
} API_AVAILABLE(ios(17.0), watchos(2.0));

/*!
 @enum          HKWorkoutSessionType
 @abstract      This enumerated type is used to represent the type of a workout session.
 
 @constant      HKWorkoutSessionTypePrimary      Represents a workout session running locally on the current device.
 @constant      HKWorkoutSessionTypeMirrored     Represents a workout session being mirrored from a different device.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionType) {
    HKWorkoutSessionTypePrimary = 0,
    HKWorkoutSessionTypeMirrored,
} API_AVAILABLE(ios(17.0), watchos(10.0));

/*!
 @class         HKWorkoutSession
 @abstract      An HKWorkoutSession is an object describing the properties of a workout activity session.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(17.0), watchos(2.0))
@interface HKWorkoutSession : NSObject <NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout that will be performed during the session.
 */
@property (readonly) HKWorkoutActivityType activityType API_DEPRECATED_WITH_REPLACEMENT("workoutConfiguration", watchos(2.0, 3.0));

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) where the workout will take place.
 @discussion    Knowing the location type allows for more accurate measurements and better performance.
 */
@property (readonly) HKWorkoutSessionLocationType locationType API_DEPRECATED_WITH_REPLACEMENT("workoutConfiguration", watchos(2.0, 3.0));

/*!
 @property      workoutConfiguration
 @abstract      The configuration object describing the workout.
 @discussion    This returns a copy of the configuration passed when creating the HKWorkoutSession. Changes made to
                the returned object have no impact on the HKWorkoutSession.
 */
@property (readonly, copy) HKWorkoutConfiguration *workoutConfiguration API_AVAILABLE(ios(17.0), watchos(3.0));

/*!
 @property      delegate
 @abstract      The session delegate, which receives
 @discussion    The session delegate object is the one implementing the methods that get called when the session
                state changes or a failure occurs in the session.
 */
@property (weak, nullable) id<HKWorkoutSessionDelegate> delegate;

/*!
 @property      state
 @abstract      Indicates the current state of the workout session.
 @discussion    Each time this value is updated, the delegate method workoutSession:didChangeToState:fromState:date:
                will be called.
 */
@property (readonly) HKWorkoutSessionState state;

/*!
 @property      type
 @abstract      Indicates the type of the workout session.
 @discussion    A workout session created using an initializer will be primary, while a session retrieved with
                the `HKHealthStore` `workoutSessionMirroringStartHandler` property will be mirrored.
 */
@property (readonly) HKWorkoutSessionType type API_AVAILABLE(ios(17.0), watchos(10.0));

/*!
 @property      startDate
 @abstract      Indicates the date when the workout session started running.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateRunning.
 */
@property (readonly, nullable) NSDate *startDate;

/*!
 @property      endDate
 @abstract      Indicates the date when the workout session stopped.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateStopped.
 */
@property (readonly, nullable) NSDate *endDate;

/*!
 @property      currentActivity
 @abstract      The current workout activity.
 @discussion    This returns a copy of the session's current workout activity. It will return
                a copy of the main workout activity if no new activity has begun. Changes made
                to the returned object have no impact on the HKWorkoutSession.
 */
@property (readonly, copy) HKWorkoutActivity *currentActivity API_AVAILABLE(ios(17.0), watchos(9.0));

/*!
 @method        initWithActivityType:locationType:

 @param         activityType    The activity type of the workout session.
 @param         locationType    The type of location where the workout will be performed.
 */
- (instancetype)initWithActivityType:(HKWorkoutActivityType)activityType
                        locationType:(HKWorkoutSessionLocationType)locationType API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(2.0, 3.0)) API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(macos, macCatalyst, tvos);

/*!
 @method        initWithConfiguration:error:
 
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(3.0, 5.0)) API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(macos, macCatalyst, tvos);

/*!
 @method        initWithHealthStore:configuration:error:
 
 @param         healthStore          Specifies the HKHealthStore object to use.
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                               configuration:(HKWorkoutConfiguration *)workoutConfiguration
                                       error:(NSError **)error API_AVAILABLE(ios(26.0), watchos(5.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, macCatalyst);

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        prepare
 @abstract      Prepares the workout session for starting.
 @discussion    This method will asynchronously prepare the workout session for starting. The state of the workout session
                will transition to HKWorkoutSessionStatePrepared. A prepared session will put the system in session mode,
                but will not start the session activity.
                You might call this methods, for example, prior to displaying a countdown on your application while waiting
                for the activity to start.
 */
- (void)prepare API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        startActivityWithDate:

 @param         date                Start date for the workout session activity
 @abstract      Starts the workout session activity.
 @discussion    This method will asynchronously begin the workout session activity. The state of the workout session will
                transition to HKWorkoutSessionStateRunning. Once a session activity is started the system will be in session
                mode and sensor algorithms will be applied to generate data for the workout activity.
 */
- (void)startActivityWithDate:(nullable NSDate *)date API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        stopActivityWithDate:
 @param         date                Stop date for the workout session activity
 @abstract      Stops the workout session activity.
 @discussion    This method will asynchronously stop the session activity if it is currently running. The state of the workout
                session will transition to HKWorkoutSessionStateStopped. Once a workout session is stopped, it cannot be reused to
                start a new workout session. Sensor algorithms will be stopped and no new data will be generated for this session.
                However, the system will remain in session mode.
 */
- (void)stopActivityWithDate:(nullable NSDate *)date API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        end
 @abstract      Ends the workout session.
 @discussion    This method will end the session if it is currently running or stopped. The state of the workout session will
                transition to HKWorkoutSessionStateEnded. Once a workout session is ended, it cannot be reused to start a new
                workout session. Sensor algorithms will be stopped, no new data will be generated for this session, and the
                system will exit session mode.
 */
- (void)end API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        pause
 @abstract      Pauses the workout session.
 @discussion    This method will pause the session if it is currently running. The state of the workout session
                will transition to HKWorkoutSessionStatePaused. An HKWorkoutEventTypePause will be generated and
                delivered to the workout session's delegate.
 */
- (void)pause API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        resume
 @abstract      Resumes the workout session.
 @discussion    This method will resume the session if it is currently paused. The state of the workout session
                will transition to HKWorkoutSessionStateRunning. An HKWorkoutEventTypeResume will be generated and
                delivered to the workout session's delegate.
 */
- (void)resume API_AVAILABLE(ios(17.0), watchos(5.0));

/*!
 @method        associatedWorkoutBuilder
 @abstract      Retrieves (and creates if necessary) an HKLiveWorkoutBuilder associated with this session.
 @discussion    A session may have associated with it an HKLiveWorkoutBuilder that will be used to record the workout
                for this session. This method will return the session's associated builder, creating it if needed.
                Calling this method more than once will return the previously-created builder. If this session was not
                initialized with initWithHealthStore:configuration:error:, an exception will be thrown.
 */
- (HKLiveWorkoutBuilder *)associatedWorkoutBuilder API_AVAILABLE(ios(26.0), watchos(5.0)) API_UNAVAILABLE(tvos, visionos) API_UNAVAILABLE(macos, macCatalyst);

/*!
 @method        beginNewActivityWithConfiguration:date:metadata:
 @abstract      Begins a new workout activity for this session.
 @discussion    This method will asynchronously begin the workout activity. The delegate for this session would be
                informed once the activity effectively begins.  Sensor algorithms to generate data would be updated
                to match the new activity.
 */
- (void)beginNewActivityWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration
                                     date:(NSDate *)date
                                 metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(17.0), watchos(9.0)) NS_SWIFT_NAME(beginNewActivity(configuration:date:metadata:));

/*!
 @method        endCurrentActivityOnDate:
 @abstract      Ends the current workout activity.
 @discussion    This method will end the current activity, reverting to the main session activity. The delegate for this session
                would be informed once the activity effectively ends. Sensor algorithms to generate data would be updated to
                match the main session activity.
 */
- (void)endCurrentActivityOnDate:(NSDate *)date API_AVAILABLE(ios(17.0), watchos(9.0));

/*!
 @method        startMirroringToCompanionDeviceWithCompletion:
 @abstract      Starts mirroring the session to the companion device.
 @discussion    Calling this method will result in your app on the companion device being launched in the background.
                When your app is launched set the `HKHealthStore` `workoutSessionMirroringStartHandler` property to retrieve
                the mirrored session.
                This method will fail if called for a session that is ended.
                The completion handler will be executed on an arbitrary background queue.
 */
- (void)startMirroringToCompanionDeviceWithCompletion:(void (^NS_SWIFT_SENDABLE)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(watchos(10.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macos, macCatalyst, tvos) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @method        stopMirroringToCompanionDeviceWithCompletion:
 @abstract      Stops mirroring the session to the companion device.
 @discussion    Calling this method will stop sending data to the companion device. The mirrored session's delegate method
                `didDisconnectFromRemoteDeviceWithError:` will be called to indicate that.
                When a workout session is ended, mirroring is automatically stopped.
                The completion handler will be executed on an arbitrary background queue.
 */
- (void)stopMirroringToCompanionDeviceWithCompletion:(void (^NS_SWIFT_SENDABLE)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(watchos(10.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macos, macCatalyst, tvos) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @method        sendDataToRemoteWorkoutSession:completion:
 @abstract      Sends an NSData object to the connected remote workout session.
 @discussion    This method can be called to send data from a primary session to its mirrored counterpart and vice-versa.
                It's only intended to be used for data that describes the current state of the workout, such as accumulated metrics, and any
                data needed to keep your app on both devices in sync.
                The maximum amount of data that can be sent is 100 KB in any given 10-second time window.
                If this limit is exceeded, an error will be returned in the completion handler.
                An error will also be returned if the session is not mirroring.
                The completion handler will be executed on an arbitrary background queue.
 */
- (void)sendDataToRemoteWorkoutSession:(NSData *)data
                            completion:(void (^NS_SWIFT_SENDABLE)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(ios(17.0), watchos(10.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) NS_SWIFT_NAME(sendToRemoteWorkoutSession(data:completion:)) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

@end

/*!
 @enum          HKWorkoutSessionStateDelegate
 @abstract      This protocol should be implemented to be notified when a workout session's state changes.
 @discussion    The methods on this protocol are called on an anonymous serial background queue.
 */
API_AVAILABLE(ios(17.0), watchos(2.0))
@protocol HKWorkoutSessionDelegate <NSObject>

/*!
 @method        workoutSession:didChangeToState:fromState:date:
 @abstract      This method is called when a workout session transitions to a new state.
 @discussion    The date is provided to indicate when the state change actually happened.  If your application is
                suspended then the delegate will receive this call once the application resumes, which may be much later
                than when the original state change ocurred.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession
      didChangeToState:(HKWorkoutSessionState)toState
             fromState:(HKWorkoutSessionState)fromState
                  date:(NSDate *)date;

/*!
 @method        workoutSession:didFailWithError:
 @abstract      This method is called when an error occurs that stops a workout session.
 @discussion    When the state of the workout session changes due to an error occurring, this method is always called
                before workoutSession:didChangeToState:fromState:date:.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didFailWithError:(NSError *)error;

@optional

/*!
 @method        workoutSession:didGenerateEvent:
 @abstract      This method is called whenever the system generates a workout event.
 @discussion    Whenever a workout event is generated, such as pause or resume detection, the event will be passed
                to the session delegate via this method. Clients may save the generated events to use when creating an
                HKWorkout object.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didGenerateEvent:(HKWorkoutEvent *)event API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @method        workoutSession:didBeginActivityWithConfiguration:date:
 @abstract      This method is called whenever a new activity begins.
 @discussion    Whenever a new workout activity begins, the new configuration would be passed to the session delegate
                via this method. Clients may use this data to create a workout activity to save when building an HKWorkout
                object.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession
didBeginActivityWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration
                  date:(NSDate *)date API_AVAILABLE(ios(17.0), watchos(9.0));

/*!
 @method        workoutSession:didEndActivityWithConfiguration:date:
 @abstract      This method is called whenever the current workout activity ends.
 @discussion    Whenever a new workout activity ends, the new configuration would be passed to the session delegate
                via this method. Clients may use this data to create a workout activity to save when building an HKWorkout
                object.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession
didEndActivityWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration
                  date:(NSDate *)date API_AVAILABLE(ios(17.0), watchos(9.0));

/*!
 @method        workoutSession:didReceiveDataFromRemoteWorkoutSession:
 @abstract      This method is called when the session receives data from its remote counterpart.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didReceiveDataFromRemoteWorkoutSession:(NSArray<NSData *> *)data API_AVAILABLE(ios(17.0), watchos(10.0));

/*!
 @method        workoutSession:didDisconnectFromRemoteDeviceWithError:
 @abstract      This method is called when the session is disconnected from its remote counterpart.
 @discussion    After this method is called for a mirrored workout session, it is no longer considered valid.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didDisconnectFromRemoteDeviceWithError:(nullable NSError *)error API_AVAILABLE(ios(17.0), watchos(10.0));

@end

NS_ASSUME_NONNULL_END
