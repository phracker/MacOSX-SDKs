//
//  CPTravelEstimates.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPTravelEstimates describes the time and distance remaining for the active navigation session.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPTravelEstimates : NSObject <NSSecureCoding>

/**
 Initialize a @c CPTravelEstimates with distance and time remaining.

 @note A distance value less than 0 or a time remaining value less than 0 will render
 as "--" in the ETA and trip preview cards, indicating that distance or time remaining are
 unavailable, due to route calculations/rerouting or internet connectivity problems.
 Values less than 0 are distinguished from distance or time values equal to 0; your app may
 display 0 as the user is imminently arriving at their destination.
 */
- (instancetype)initWithDistanceRemaining:(NSMeasurement<NSUnitLength *> *)distance timeRemaining:(NSTimeInterval)time NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithDistanceRemaining:(NSMeasurement<NSUnitLength *> *)distanceRemaining distanceRemainingToDisplay:(NSMeasurement<NSUnitLength *> *)distanceRemainingToDisplay timeRemaining:(NSTimeInterval)time NS_DESIGNATED_INITIALIZER  API_AVAILABLE(ios(17.4));

/**
 Distance remaining for displaying to the user.  If not set falls back to distanceRemaining;
 */
@property (nonatomic, readonly, copy) NSMeasurement<NSUnitLength *> *distanceRemainingToDisplay API_AVAILABLE(ios(17.4));

/**
 Distance remaining.
 */
@property (nonatomic, readonly, copy) NSMeasurement<NSUnitLength *> *distanceRemaining;

/**
 Time remaining.
 */
@property (nonatomic, readonly, assign) NSTimeInterval timeRemaining;

@end

NS_ASSUME_NONNULL_END
