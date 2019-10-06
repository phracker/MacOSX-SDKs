//
//  HKActivitySummary.h
//  HealthKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKActivitySummary
 @abstract      An object that represents a summary of a user's activity for a given day.
 */
HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummary : NSObject <NSSecureCoding, NSCopying>

/**
 @method        dateComponentsForCalendar:
 @abstract      The date components representing the day for this particular HKActivitySummary.
 @discussion    These date components will contain era, year, month, and day components in the provided calendar.
 */
- (NSDateComponents *)dateComponentsForCalendar:(NSCalendar *)calendar;

/**
  @property      activeEnergyBurned
  @abstract      The amount of active energy that the user burned.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurned;

/**
  @property      appleExerciseTime
  @abstract      The amount of exercise time that the user performed.
  @discussion    This quantity is compatible with time units. The measurement criteria of
                 exercise time is defined by Apple.
  */
@property (nonatomic, strong) HKQuantity *appleExerciseTime;

/**
  @property      appleStandHours
  @abstract      The number of stand hours that the user earned.
 @discussion     This quantity is compatible with the count unit. The measurement criteria of
                 stand hours is defined by Apple.
  */
@property (nonatomic, strong) HKQuantity *appleStandHours;

/**
  @property      activeEnergyBurnedGoal
  @abstract      The user's active energy goal for the day.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurnedGoal;

/**
  @property      appleExerciseTimeGoal
  @abstract      The user's exercise time goal for the day.
  @discussion    This quantity is compatible with time units.
  */
@property (nonatomic, strong) HKQuantity *appleExerciseTimeGoal;

/**
  @property      appleStandHoursGoal
  @abstract      The user's active stand hours goal for the day.
  @discussion    This quantity is compatible with the count unit.
  */
@property (nonatomic, strong) HKQuantity *appleStandHoursGoal;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathDateComponents API_AVAILABLE(ios(9.3), watchos(2.2));

NS_ASSUME_NONNULL_END

