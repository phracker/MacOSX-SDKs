//
//  CPNavigationEnum.h
//  CarPlay
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CarPlay/CPLane.h>
#import <CarPlay/CPManeuver.h>

#pragma mark - Maneuver
NSString *NSStringFromCPManeuverType(CPManeuverType maneuverType) API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);
NSString *NSStringFromCPJunctionType(CPJunctionType junctionType) API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);
NSString *NSStringFromCPTrafficSide(CPTrafficSide trafficSide) API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

#pragma mark - Lane
NSString *NSStringFromCPLaneStatus(CPLaneStatus laneStatus) API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

