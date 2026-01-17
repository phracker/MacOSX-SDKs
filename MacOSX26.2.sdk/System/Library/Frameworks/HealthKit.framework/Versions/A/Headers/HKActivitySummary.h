//
//  HKActivitySummary.h
//  HealthKit
//
//  Copyright (c) 2015-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKActivitySummary
 @abstract      An object that represents a summary of a user's activity for a given day.
 */
HK_EXTERN
API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(13.0), macos(13.0))
@interface HKActivitySummary : NSObject <NSSecureCoding, NSCopying>

/**
 @method        dateComponentsForCalendar:
 @abstract      The date components representing the day for this particular HKActivitySummary.
 @discussion    These date components will contain era, year, month, and day components in the provided calendar.
 */
- (NSDateComponents *)dateComponentsForCalendar:(NSCalendar *)calendar;

/**
  @property      activityMoveMode
  @abstract      The move mode of this activity summary
  @discussion    The move mode of an activity summary determines if activeEnergyBurned or appleMoveTime are used for the move ring.
  */
@property (nonatomic, assign) HKActivityMoveMode activityMoveMode API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/**
 @property paused
 @abstract The paused state of this activity summary
 @discussion The paused state of an activity summary indicates if the user is tracking their rings for the given day.
 */
@property (nonatomic, assign, getter=isPaused) BOOL paused API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));

/**
  @property      activeEnergyBurned
  @abstract      The amount of active energy that the user burned.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurned;

/**
  @property      appleMoveTime
  @abstract      The amount of move time that the user performed.
  @discussion    This quantity is compatible with time units. The measurement criteria of
                 move time time is defined by Apple.
  */
@property (nonatomic, strong) HKQuantity *appleMoveTime API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

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
  @property      activeEnergyBurnedGoal
  @abstract      The user's active energy goal for the day.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurnedGoal;

/**
  @property      appleMoveTimeGoal
  @abstract      The user's move time goal for the day.
  @discussion    This quantity is compatible with time units.
  */
@property (nonatomic, strong) HKQuantity *appleMoveTimeGoal API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));

/**
  @property      appleExerciseTimeGoal
  @abstract      The user's exercise time goal for the day.
  @discussion    This quantity is compatible with time units.
  */
@property (nonatomic, strong) HKQuantity *appleExerciseTimeGoal API_DEPRECATED_WITH_REPLACEMENT("exerciseTimeGoal", ios(9.3, API_TO_BE_DEPRECATED), watchos(2.2, API_TO_BE_DEPRECATED));

/**
  @property      exerciseTimeGoal
  @abstract      The user's exercise time goal for the day.
  @discussion    This quantity is compatible with time units.
  */
@property (nonatomic, strong, nullable) HKQuantity *exerciseTimeGoal API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/**
  @property      appleStandHoursGoal
  @abstract      The user's active stand hours goal for the day.
  @discussion    This quantity is compatible with the count unit.
  */
@property (nonatomic, strong) HKQuantity *appleStandHoursGoal API_DEPRECATED_WITH_REPLACEMENT("standHoursGoal", ios(9.3, API_TO_BE_DEPRECATED), watchos(2.2, API_TO_BE_DEPRECATED));

/**
  @property      standHoursGoal
  @abstract      The user's active stand hours goal for the day.
  @discussion    This quantity is compatible with the count unit.
  */
@property (nonatomic, strong, nullable) HKQuantity *standHoursGoal API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathDateComponents API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
