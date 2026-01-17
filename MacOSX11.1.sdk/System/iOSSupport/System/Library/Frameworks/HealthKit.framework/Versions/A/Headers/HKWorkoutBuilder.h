//
//  HKWorkoutBuilder.h
//  HealthKit
//
//  Copyright © 2017-2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKObjectType.h>
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKSeriesBuilder;
@class HKStatistics;
@class HKWorkoutConfiguration;

/*!
 @class         HKWorkoutBuilder
 @discussion    An HKWorkoutBuilder is used to incrementally create new workouts in the HealthKit database. Samples,
                events, and metadata may be added to a builder either during a live workout session or to create a
                workout that occurred in the past. Calling finishWorkoutWithCompletion: will create a new workout
                with samples, events, and metadata that have been provided.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKWorkoutBuilder : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      device
 @abstract      The HKDevice to be associated with the workout.
 */
@property (copy, nullable, readonly) HKDevice *device;

/*!
 @property      startDate
 @abstract      The start date for the workout, as provided by beginCollectionWithStartDate:completion:
 */
@property (copy, nullable, readonly) NSDate *startDate;

/*!
 @property      endDate
 @abstract      The end date for the workout, as provided by endCollectionWithEndDate:completion:
 */
@property (copy, nullable, readonly) NSDate *endDate;

/*!
 @property      workoutConfiguration
 @abstract      The configuration for the workout being built.
 */
@property (copy, readonly) HKWorkoutConfiguration *workoutConfiguration;

/*!
 @property      metadata
 @abstract      The metadata that will be used when the workout is finished.
 */
@property (copy, readonly) NSDictionary<NSString *, id> *metadata;

/*!
 @property      workoutEvents
 @abstract      Workout events that have been added to the builder.
 @discussion    New events that are added using addWorkoutEvents:completion: will be appended to this array once the
                completion is called.
 */
@property (copy, readonly) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @method        initWithHealthStore:configuration:device:
 @abstract      The designated initializer to create an HKWorkoutBuilder.
 @discussion    Creates a new HKWorkoutBuilder unconnected to any HKWorkoutSession or any sources of data.

 @param         healthStore     Specifies the HKHealthStore object to use for building the workout. The store is retained
                                until the builder is finished and a workout has been saved or discarded.
 @param         configuration   The workout configuration to be used.
 @param         device          The HKDevice to attach to the resulting HKWorkout.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                      configuration:(HKWorkoutConfiguration *)configuration
                             device:(nullable HKDevice *)device;

/*!
 @method        beginCollectionWithStartDate:error:
 @abstract      Sets the workout start date and activates the workout builder.
 @discussion    Calling this method is required before any samples, events or metadata can be added to the builder.
 
 @param         startDate   The start date of the workout.
 @param         completion  Called once data collection has started or has failed to start.
 */
- (void)beginCollectionWithStartDate:(NSDate *)startDate completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addSamples:completion:
 @discussion    Adds new samples to the builder instance. This method can be called multiple times to add samples
                incrementally to the builder. The samples will be saved to the database if they have not already been
                saved. The constraints of -[HKHealthStore saveObject:withCompletion:] apply to this method as well.
                The start date of the samples must be later than the start date of the receiver. It is an error to call
                this method after finishWorkoutWithCompletion: has been called. This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.

 @param         samples     The samples to add to the workout.
 @param         completion  Block to be called when the insertion is complete. If success is YES, the samples were added
                            to the builder successfully. If success is NO, error will be non-nil and contain the error
                            encountered while adding the new samples.
 */
- (void)addSamples:(NSArray<HKSample *> *)samples completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addWorkoutEvents:completion:
 @discussion    Adds new workout events to the builder instance. This method can be called many times to add workout
                events incrementally to the builder. It is an error to call this method after
                finishWorkoutWithCompletion: has been called. This operation is performed asynchronously and the
                completion will be executed on an arbitrary background queue.

 @param         workoutEvents   The events to add to the builder.
 @param         completion      Block to be called when the addition of events to the builder is complete. If success is
                                YES, the events were added to the builder successfully. If success is NO, error will be
                                non-null and will contain the error encountered during the insertion operation.
 */
- (void)addWorkoutEvents:(NSArray<HKWorkoutEvent *> *)workoutEvents completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addMetadata:completion:
 @discussion    Adds new metadata to the builder instance. This method can be called more than once; each time the newly
                provided metadata will be merged with previously added metadata in the same manner as
                -[NSMutableDictionary addEntriesFromDictionary:]. This operation is performed asynchronously and the
                completion will be executed on an arbitrary background queue.

 @param         metadata    The metadata to add to the workout.
 @param         completion  Block to be called when the addition of metadata to the builder is complete. If success is
                            YES, the metadata has been added to the builder successfully. If success is NO, error will
                            be non-null and will contain the error encountered during the insertion operation. When an
                            error occurs, the builder's metadata property will remain unchanged.
 */
- (void)addMetadata:(NSDictionary<NSString *, id> *)metadata completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        endCollectionWithEndDate:error:
 @abstract      Sets the workout end date and deactivates the workout builer.
 @discussion    Calling this method is required before you finish a workout builder.
 
 @param         endDate     The end date of the workout.
 @param         completion  Called once data collection has stopped or has failed to stop.
 */
- (void)endCollectionWithEndDate:(NSDate *)endDate completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        finishWorkoutWithCompletion:
 @discussion    Creates and saves an HKWorkout using samples and events that have been added to workout previously.
 
 @param         completion  Block to be called after the HKWorkout object has been created and saved. If success is NO,
                            then error will be the error encountered during the operation.
 */
- (void)finishWorkoutWithCompletion:(void(^)(HKWorkout * _Nullable workout, NSError * _Nullable error))completion;

/*!
 @method        discardWorkout
 @discussion    Finishes building the workout and discards ther result instead of saving it. Samples that were added to
                the workout will not be deleted. Adding samples, events, and metadata to the receiver after
                discardWorkout has been called is an error.
 */
- (void)discardWorkout;

/*!
 @method        elapsedTimeAtDate:
 @abstract      The elapsed duration of the workout evaluated at the specified date. The duration does not include
                periods when the workout was paused, which are the intervals between pause and resume events.
 */
- (NSTimeInterval)elapsedTimeAtDate:(NSDate *)date;

/*!
 @method        statisticsForType:
 @discussion    Returns an HKStatistics object containing the statistics for all the samples of the given type that
                have been added to the receiver. If there are no samples of the given type then nil is returned.
 
 @param         quantityType    The quantity type to gather statistics about.
 */
- (nullable HKStatistics *)statisticsForType:(HKQuantityType *)quantityType;

/*!
 @method        seriesBuilderForType:
 @abstract      Retrieves the associated series builder for the specified type.
 @discussion    Retrieves, and creates if it does not already exist, the series builder for the specified type. The
                series constructed with the returned builder will be associated with the workout when it is finished.
 
 @param         seriesType  The series type for which the builder should be retrieved.
 */
- (nullable __kindof HKSeriesBuilder *)seriesBuilderForType:(HKSeriesType *)seriesType;

@end

NS_ASSUME_NONNULL_END
