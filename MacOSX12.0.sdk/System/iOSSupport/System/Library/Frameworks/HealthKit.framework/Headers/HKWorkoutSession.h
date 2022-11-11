//
//  HKWorkoutSession.h
//  HealthKit
//
//  Copyright (c) 2015-2018 Apple. All rights reserved.
//

#import <HealthKit/HKLiveWorkoutBuilder.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKWorkout.h>
#import <HealthKit/HKWorkoutBuilder.h>
#import <HealthKit/HKWorkoutConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKLiveWorkoutBuilder;
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
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);


/*!
 @class         HKWorkoutSession
 @abstract      An HKWorkoutSession is an object describing the properties of a workout activity session.
 */
HK_EXTERN API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
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
@property (readonly, copy) HKWorkoutConfiguration *workoutConfiguration API_AVAILABLE(watchos(3.0));

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
 @property      startDate
 @abstract      Indicates the date when the workout session started running.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateRunning.
 */
@property (readonly, nullable) NSDate *startDate;

/*!
 @property      endDate
 @abstract      Indicates the date when the workout session ended.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateEnded.
 */
@property (readonly, nullable) NSDate *endDate;

/*!
 @method        initWithActivityType:locationType:

 @param         activityType    The activity type of the workout session.
 @param         locationType    The type of location where the workout will be performed.
 */
- (instancetype)initWithActivityType:(HKWorkoutActivityType)activityType
                        locationType:(HKWorkoutSessionLocationType)locationType API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(2.0, 3.0));

/*!
 @method        initWithConfiguration:error:
 
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(3.0, 5.0));

/*!
 @method        initWithHealthStore:configuration:error:
 
 @param         healthStore          Specifies the HKHealthStore object to use.
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                               configuration:(HKWorkoutConfiguration *)workoutConfiguration
                                       error:(NSError **)error API_AVAILABLE(watchos(5.0));

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
- (void)prepare API_AVAILABLE(watchos(5.0));

/*!
 @method        startActivityWithDate:

 @param         date                Start date for the workout session activity
 @abstract      Starts the workout session activity.
 @discussion    This method will asynchronously begin the workout session activity. The state of the workout session will
                transition to HKWorkoutSessionStateRunning. Once a session activity is started the system will be in session
                mode and sensor algorithms will be applied to generate data for the workout activity.
 */
- (void)startActivityWithDate:(nullable NSDate *)date API_AVAILABLE(watchos(5.0));

/*!
 @method        stopActivityWithDate:
 @param         date                Stop date for the workout session activity
 @abstract      Stops the workout session activity.
 @discussion    This method will asynchronously stop the session activity if it is currently running. The state of the workout
                session will transition to HKWorkoutSessionStateStopped. Once a workout session is stopped, it cannot be reused to
                start a new workout session. Sensor algorithms will be stopped and no new data will be generated for this session.
                However, the system will remain in session mode.
 */
- (void)stopActivityWithDate:(nullable NSDate *)date API_AVAILABLE(watchos(5.0));

/*!
 @method        end
 @abstract      Ends the workout session.
 @discussion    This method will end the session if it is currently running or stopped. The state of the workout session will
                transition to HKWorkoutSessionStateEnded. Once a workout session is ended, it cannot be reused to start a new
                workout session. Sensor algorithms will be stopped, no new data will be generated for this session, and the
                system will exit session mode.
 */
- (void)end API_AVAILABLE(watchos(5.0));

/*!
 @method        pause
 @abstract      Pauses the workout session.
 @discussion    This method will pause the session if it is currently running. The state of the workout session
                will transition to HKWorkoutSessionStatePaused. An HKWorkoutEventTypePause will be generated and
                delivered to the workout session's delegate.
 */
- (void)pause API_AVAILABLE(watchos(5.0));

/*!
 @method        resume
 @abstract      Resumes the workout session.
 @discussion    This method will resume the session if it is currently paused. The state of the workout session
                will transition to HKWorkoutSessionStateRunning. An HKWorkoutEventTypeResume will be generated and
                delivered to the workout session's delegate.
 */
- (void)resume API_AVAILABLE(watchos(5.0));

/*!
 @method        associatedWorkoutBuilder
 @abstract      Retrieves (and creates if necessary) an HKLiveWorkoutBuilder associated with this session.
 @discussion    A session may have associated with it an HKLiveWorkoutBuilder that will be used to record the workout
                for this session. This method will return the session's associated builder, creating it if needed.
                Calling this method more than once will return the previously-created builder. If this session was not
                initialized with initWithHealthStore:configuration:error:, an exception will be thrown.
 */
- (HKLiveWorkoutBuilder *)associatedWorkoutBuilder API_AVAILABLE(watchos(5.0));

@end


/*!
 @enum          HKWorkoutSessionStateDelegate
 @abstract      This protocol should be implemented to be notified when a workout session's state changes.
 @discussion    The methods on this protocol are called on an anonymous serial background queue.
 */
API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
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

@end

NS_ASSUME_NONNULL_END
