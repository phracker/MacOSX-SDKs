//
//  CPRouteInformation.h
//  CarPlay
//
//  Copyright © 2024 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CarPlay/CPManeuver.h>
#import <CarPlay/CPLaneGuidance.h>
#import <CarPlay/CPTravelEstimates.h>

NS_ASSUME_NONNULL_BEGIN

/**
 CPRouteInformation describes information pertaining to a route that is necessary for rerouting.
 */
API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos) NS_SWIFT_SENDABLE
@interface CPRouteInformation : NSObject

/**
 Initialize a CPRouteInformation object with maneuvers, lane guidances, the current maneuvers, the current lane guidance, and trip and current maneuver travel estimates.
 */
- (instancetype)initWithManeuvers:(NSArray<CPManeuver *> *)maneuvers laneGuidances:(NSArray<CPLaneGuidance *> *)laneGuidances currentManeuvers:(NSArray<CPManeuver *> *)currentManeuvers currentLaneGuidance:(CPLaneGuidance *)currentLaneGuidance tripTravelEstimates:(CPTravelEstimates *)tripTravelEstimates maneuverTravelEstimates:(CPTravelEstimates *)maneuverTravelEstimates  NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/**
 maneuvers is an array of CPManeuver objects, each describes a single maneuver.
*/
@property (readonly, nonatomic, copy) NSArray<CPManeuver *> *maneuvers API_AVAILABLE(ios(17.4));

/**
 laneGuidances is an array of CPLaneGuidance objects, each describes a single lane guidance.
*/
@property (readonly, nonatomic, copy) NSArray<CPLaneGuidance *> *laneGuidances API_AVAILABLE(ios(17.4));

/**
 currentManeuvers is an array of CPManeuver objects, describing the current maneuvers.
*/
@property (readonly, nonatomic, copy) NSArray<CPManeuver *> *currentManeuvers API_AVAILABLE(ios(17.4));

/**
 currentLaneGuidance is a CPLaneGuidance object, describing the current lane guidance.
*/
@property (readonly, nonatomic, copy) CPLaneGuidance *currentLaneGuidance API_AVAILABLE(ios(17.4));

/**
 tripTravelEstimates is a CPTravelEstimates object, describing the travel estimates for the current trip.
*/
@property (readonly, nonatomic, copy) CPTravelEstimates *tripTravelEstimates API_AVAILABLE(ios(17.4));

/**
 maneuverTravelEstimates is a CPTravelEstimates object, describing the travel estimates for the first maneuver in the list of current maneuvers.
*/
@property (readonly, nonatomic, copy) CPTravelEstimates *maneuverTravelEstimates API_AVAILABLE(ios(17.4));


@end

NS_ASSUME_NONNULL_END
