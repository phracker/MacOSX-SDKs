//
//  HKWorkout.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @enum          HKWorkoutActivityType
 @abstract      Represents a particular type of workout or exercise
 */
typedef NS_ENUM(NSUInteger, HKWorkoutActivityType) {
    HKWorkoutActivityTypeAmericanFootball = 1,
    HKWorkoutActivityTypeArchery,
    HKWorkoutActivityTypeAustralianFootball,
    HKWorkoutActivityTypeBadminton,
    HKWorkoutActivityTypeBaseball,
    HKWorkoutActivityTypeBasketball,
    HKWorkoutActivityTypeBowling,
    HKWorkoutActivityTypeBoxing, // See also HKWorkoutActivityTypeKickboxing.
    HKWorkoutActivityTypeClimbing,
    HKWorkoutActivityTypeCricket,
    HKWorkoutActivityTypeCrossTraining, // Any mix of cardio and/or strength training. See also HKWorkoutActivityTypeCoreTraining and HKWorkoutActivityTypeFlexibility.
    HKWorkoutActivityTypeCurling,
    HKWorkoutActivityTypeCycling,
    HKWorkoutActivityTypeDance API_DEPRECATED("Use HKWorkoutActivityTypeSocialDance or HKWorkoutActivityTypeCardioDance", ios(8.0, 14.0), watchos(2.0, 7.0)), // This enum remains available to access older data.
    HKWorkoutActivityTypeDanceInspiredTraining API_DEPRECATED("Use HKWorkoutActivityTypeSocialDance, HKWorkoutActivityTypeCardioDance, HKWorkoutActivityTypeBarre or HKWorkoutActivityTypePilates", ios(8.0, 10.0), watchos(2.0, 3.0)), // This enum remains available to access older data.
    HKWorkoutActivityTypeElliptical,
    HKWorkoutActivityTypeEquestrianSports, // Polo, Horse Racing, Horse Riding, etc.
    HKWorkoutActivityTypeFencing,
    HKWorkoutActivityTypeFishing,
    HKWorkoutActivityTypeFunctionalStrengthTraining, // Primarily free weights and/or body weight and/or accessories
    HKWorkoutActivityTypeGolf,
    HKWorkoutActivityTypeGymnastics,
    HKWorkoutActivityTypeHandball,
    HKWorkoutActivityTypeHiking,
    HKWorkoutActivityTypeHockey, // Ice Hockey, Field Hockey, etc.
    HKWorkoutActivityTypeHunting,
    HKWorkoutActivityTypeLacrosse,
    HKWorkoutActivityTypeMartialArts,
    HKWorkoutActivityTypeMindAndBody, // Qigong, meditation, etc.
    HKWorkoutActivityTypeMixedMetabolicCardioTraining API_DEPRECATED("Use HKWorkoutActivityTypeMixedCardio or HKWorkoutActivityTypeHighIntensityIntervalTraining", ios(8.0, 11.0), watchos(2.0, 4.0)), // This enum remains available to access older data.
    HKWorkoutActivityTypePaddleSports, // Canoeing, Kayaking, Outrigger, Stand Up Paddle Board, etc.
    HKWorkoutActivityTypePlay, // Dodge Ball, Hopscotch, Tetherball, Jungle Gym, etc.
    HKWorkoutActivityTypePreparationAndRecovery, // Therapeutic activities like foam rolling, self massage and flexibility moves.
    HKWorkoutActivityTypeRacquetball,
    HKWorkoutActivityTypeRowing,
    HKWorkoutActivityTypeRugby,
    HKWorkoutActivityTypeRunning,
    HKWorkoutActivityTypeSailing,
    HKWorkoutActivityTypeSkatingSports, // Ice Skating, Speed Skating, Inline Skating, Skateboarding, etc.
    HKWorkoutActivityTypeSnowSports, // Sledding, Snowmobiling, Building a Snowman, etc. See also HKWorkoutActivityTypeCrossCountrySkiing, HKWorkoutActivityTypeSnowboarding, and HKWorkoutActivityTypeDownhillSkiing.
    HKWorkoutActivityTypeSoccer,
    HKWorkoutActivityTypeSoftball,
    HKWorkoutActivityTypeSquash,
    HKWorkoutActivityTypeStairClimbing, // See also HKWorkoutActivityTypeStairs and HKWorkoutActivityTypeStepTraining.
    HKWorkoutActivityTypeSurfingSports, // Traditional Surfing, Kite Surfing, Wind Surfing, etc.
    HKWorkoutActivityTypeSwimming,
    HKWorkoutActivityTypeTableTennis,
    HKWorkoutActivityTypeTennis,
    HKWorkoutActivityTypeTrackAndField, // Shot Put, Javelin, Pole Vaulting, etc.
    HKWorkoutActivityTypeTraditionalStrengthTraining, // Primarily machines and/or free weights
    HKWorkoutActivityTypeVolleyball,
    HKWorkoutActivityTypeWalking,
    HKWorkoutActivityTypeWaterFitness,
    HKWorkoutActivityTypeWaterPolo,
    HKWorkoutActivityTypeWaterSports, // Water Skiing, Wake Boarding, etc.
    HKWorkoutActivityTypeWrestling,
    HKWorkoutActivityTypeYoga,
    
    HKWorkoutActivityTypeBarre              API_AVAILABLE(ios(10.0), watchos(3.0)),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeCoreTraining       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeCrossCountrySkiing API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeDownhillSkiing     API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeFlexibility        API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeHighIntensityIntervalTraining    API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeJumpRope           API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeKickboxing         API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypePilates            API_AVAILABLE(ios(10.0), watchos(3.0)),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeSnowboarding       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeStairs             API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeStepTraining       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeWheelchairWalkPace API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeWheelchairRunPace  API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeTaiChi             API_AVAILABLE(ios(11.0), watchos(4.0)),
    HKWorkoutActivityTypeMixedCardio        API_AVAILABLE(ios(11.0), watchos(4.0)),    // HKWorkoutActivityTypeMixedMetabolicCardioTraining
    HKWorkoutActivityTypeHandCycling        API_AVAILABLE(ios(11.0), watchos(4.0)),
    HKWorkoutActivityTypeDiscSports         API_AVAILABLE(ios(13.0), watchos(6.0)),
    HKWorkoutActivityTypeFitnessGaming      API_AVAILABLE(ios(13.0), watchos(6.0)),
    HKWorkoutActivityTypeCardioDance        API_AVAILABLE(ios(14.0), watchos(7.0)),
    HKWorkoutActivityTypeSocialDance        API_AVAILABLE(ios(14.0), watchos(7.0)),    // Dances done in social settings like swing, salsa and folk dances from different world regions.
    HKWorkoutActivityTypePickleball         API_AVAILABLE(ios(14.0), watchos(7.0)),
    HKWorkoutActivityTypeCooldown           API_AVAILABLE(ios(14.0), watchos(7.0)),    // Low intensity stretching and mobility exercises following a more vigorous workout type
    
    HKWorkoutActivityTypeOther = 3000,
} API_AVAILABLE(ios(8.0), watchos(2.0));

typedef NS_ENUM(NSInteger, HKWorkoutEventType) {
    HKWorkoutEventTypePause = 1,
    HKWorkoutEventTypeResume,
    HKWorkoutEventTypeLap           API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMarker        API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMotionPaused  API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMotionResumed API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeSegment       API_AVAILABLE(ios(11.0), watchos(4.0)),
    HKWorkoutEventTypePauseOrResumeRequest API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @class         HKWorkoutEvent
 @abstract      Represents a particular event that occurred during a workout.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkoutEvent : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      workoutEventType
 @abstract      Represents the type of event that occurred during a workout.
 */
@property (readonly, assign) HKWorkoutEventType type;

@property (readonly, copy) NSDate *date API_DEPRECATED_WITH_REPLACEMENT("dateInterval", ios(8.0, 11.0), watchos(2.0, 4.0));

/*!
 @property      dateInterval
 @abstract      Date interval representing the time period for which the event is valid.
 @discussion    Most event types only support date intervals with zero duration. Events of type HKWorkoutEventTypeLap
                and HKWorkoutEventTypeSegment are currently the only events that support a nonzero duration.
 */
@property (readonly, copy) NSDateInterval *dateInterval API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(10.0), watchos(3.0));

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date API_DEPRECATED_WITH_REPLACEMENT("workoutEventWithType:dateInterval:metadata:", ios(8.0, 11.0), watchos(2.0, 4.0));

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date metadata:(NSDictionary<NSString *, id> *)metadata API_DEPRECATED_WITH_REPLACEMENT("workoutEventWithType:dateInterval:metadata:", ios(10.0, 11.0), watchos(3.0, 4.0));

/*!
 @method        workoutEventWithType:dateInterval:metadata:
 @discussion    Creates an event with a date interval with or without a duration.
 @param         type                    The type of event to create
 @param         dateInterval            The dateInterval over which the event occurs
 @param         metadata                Dictionary of metadata associated with the event, nullable
 */
+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type dateInterval:(NSDateInterval *)dateInterval metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(11.0), watchos(4.0));

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKWorkout
 @abstract      An HKObject subclass representing a workout or activity
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkout : HKSample

/*!
 @property      workoutActivityType
 @abstract      Represents the activity that the user was performing during a workout
 */
@property (readonly, assign) HKWorkoutActivityType workoutActivityType;

/*!
 @property      workoutEvents
 @abstract      An array of HKWorkoutEvents that occurred during a workout.
 @discussion    These events will be ordered by date in ascending order. All events must take place
                between the start date and end date of the workout. The first workout event should never be a resume event
                because it is assumed that the workout begins in a running state.
 */
@property (readonly, copy, nullable) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @property      duration
 @abstract      The length of time that a workout was recording
 @discussion    The duration is derived from the start and end dates of the workout and takes into account periods that the
                workout was paused. Periods that the workout was paused are based off of the workoutEvents property.
 */
@property (readonly, assign) NSTimeInterval duration;

/*!
 @property      totalEnergyBurned
 @abstract      The amount of energy that was burned during a workout
 @discussion    This metric should represent the total active energy burned during the course of the workout. It should be a
                quantity with a unit representing energy.
 */
@property (readonly, strong, nullable) HKQuantity *totalEnergyBurned;
/*!
 @property      totalDistance
 @abstract      The total distance that was traveled during a workout
 @discussion    This metric should represent the total distance traveled during the course of the workout. It should be a
                quantity with a unit representing length.
 */
@property (readonly, strong, nullable) HKQuantity *totalDistance;

/*!
 @property      totalSwimmingStrokeCount
 @abstract      The total count of swimming strokes that was accumulated during a workout
 @discussion    This metric should represent the total count of swimming strokes accumulated during the course of the
                workout. It should be a quantity with a unit representing count.
 */
@property (readonly, strong, nullable) HKQuantity *totalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @property      totalFlightsClimbed
 @abstract      The total count of flights climbed during a workout
 @discussion    This metric should represent the total count of flights accumulated during the course of the
 workout. It should be a quantity with a unit representing count.
 */
@property (readonly, strong, nullable) HKQuantity *totalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:

 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:totalSwimmingStrokeCount:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType         The activity type of the workout
 @param         startDate                   The point in time that the workout was started
 @param         endDate                     The point in time that the workout was ended
 @param         workoutEvents               An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned           The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance               The total distance that was traveled during the workout. (Optional)
 @param         totalSwimmingStrokeCount    The total count of swimming strokes that was accumulated during the workout. (Optional)
 @param         device                      The HKDevice associated with the workout. (Optional)
 @param         metadata                    Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
               totalSwimmingStrokeCount:(nullable HKQuantity *)totalSwimmingStrokeCount
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:totalFlightsClimbed:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total
                quantities should be associated with this workout using addSamples:toWorkout:completion: in
                HKHealthStore.
 
 @param         workoutActivityType         The activity type of the workout
 @param         startDate                   The point in time that the workout was started
 @param         endDate                     The point in time that the workout was ended
 @param         workoutEvents               An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned           The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance               The total distance that was traveled during the workout. (Optional)
 @param         totalFlightsClimbed         The total count of flights climbed that was accumulated during the workout. (Optional)
 @param         device                      The HKDevice associated with the workout. (Optional)
 @param         metadata                    Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                    totalFlightsClimbed:(nullable HKQuantity *)totalFlightsClimbed
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(11.0), watchos(4.0));

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutDuration API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalDistance API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutType API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));


// Sort Identifiers
HK_EXTERN NSString * const HKWorkoutSortIdentifierDuration API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalDistance API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));

NS_ASSUME_NONNULL_END
