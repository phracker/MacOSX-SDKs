//
//  HKWorkoutActivity.h
//  HKWorkoutActivity
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantityType;
@class HKStatistics;
@class HKWorkoutConfiguration;
@class HKWorkoutEvent;

/*!
 @class         HKWorkoutActivity
 @abstract      An HKWorkoutActivity is an object describing the properties of an activity within an HKWorkout.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKWorkoutActivity : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      UUID
 @abstract      A unique identifier of the activity in the HealthKit database.
 */
@property (copy, readonly) NSUUID *UUID;

/*!
 @property      workoutConfiguration
 @abstract      The configuration object describing the workout activity.
 */
@property (copy, readonly) HKWorkoutConfiguration *workoutConfiguration;

/*!
 @property      startDate
 @abstract      The point in time when the workout activity was started.
 */
@property (copy, readonly) NSDate *startDate;

/*!
 @property      endDate
 @abstract      The point in time when the workout activity was ended.
 @discussion    This value is nil when a workout activity is in progress.
 */
@property (copy, readonly, nullable) NSDate *endDate;

/*!
 @property      metadata
 @abstract      Extra information describing properties of the workout activity.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (copy, readonly, nullable) NSDictionary<NSString *, id> *metadata;

/*!
 @property      duration
 @abstract      The length of time that the workout activity was recording
 @discussion    The duration is derived from the start and end dates of the activity and takes
                into account periods that the activity was paused. Periods that the activity was
                paused are based off of the workoutEvents property of the parent workout object.
 */
@property (readonly, assign) NSTimeInterval duration;

/*!
 @property      workoutEvents
 @abstract      An array of HKWorkoutEvents that occurred during the workout activity.
 @discussion    These events will be ordered by date in ascending order. These events are a subset
                of the workout events that take place between the start date and end date of the
                activity. This includes any event that overlaps the activity, even partially.
                Consequently, some events may be included in more than one activity.
 */
@property (readonly, copy) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @property      allStatistics
 @abstract      A dictionary of statistics per quantity type during the activity
 @discussion    This dictionary will contain HKStatistics objects containing the statistics by quantity
                sample type for all of the samples that have been added to the workout within the date
                interval of this activity.
 */
@property (readonly, copy) NSDictionary<HKQuantityType *, HKStatistics *> *allStatistics API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @method        statisticsForType:
 @discussion    Returns an HKStatistics object containing the statistics for all the samples of the given type that
                have been added to the workout within the date interval of this activity. If there are no samples of
                the given type then nil is returned.
  
 @param         quantityType    The quantity type to gather statistics about.
 */
- (nullable HKStatistics *)statisticsForType:(HKQuantityType *)quantityType;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @method        initWithWorkoutConfiguration:startDate:endDate:metadata:
 @abstract      Initialize a new HKWorkoutActivity with the specified values.
 
 @param     workoutConfiguration    The configuration object describing the workout activity.
 @param     startDate               The point in time when the workout activity was started.
 @param     endDate                 The point in time when the workout activity was ended.
 @param     metadata                Metadata for the workout activity. (Optional)
 */
- (instancetype)initWithWorkoutConfiguration:(HKWorkoutConfiguration *)workoutConfiguration
                                   startDate:(NSDate *)startDate
                                     endDate:(nullable NSDate *)endDate
                                    metadata:(nullable NSDictionary<NSString *, id> *)metadata;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityType API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityDuration API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityStartDate API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityEndDate API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivitySumQuantity API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityMinimumQuantity API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityMaximumQuantity API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutActivityAverageQuantity API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

NS_ASSUME_NONNULL_END
