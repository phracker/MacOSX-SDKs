//
//  CPNavigationSession.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPManeuver.h>
#import <CarPlay/CPTravelEstimates.h>
#import <CarPlay/CPTrip.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPTripPauseReason) {
    CPTripPauseReasonArrived          = 1,
    CPTripPauseReasonLoading          = 2,
    CPTripPauseReasonLocating         = 3,
    CPTripPauseReasonRerouting        = 4,
    CPTripPauseReasonProceedToRoute   = 5,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 @c CPNavigationSession represents the active navigation session. A @c CPNavigationSession will be created for you
 when calling startNavigationSessionForTrip: on @c CYMapTemplate
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNavigationSession : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Pause the current trip.
 
 @param reason The reason navigation was paused.
 @param description An optional description of the pause reason. If @c nil, a system-provided string will be used.
 */
- (void)pauseTripForReason:(CPTripPauseReason)reason description:(nullable NSString *)description;

/**
 Finish the trip.
 */
- (void)finishTrip;

/**
 Cancel the trip.
 */
- (void)cancelTrip;

/**
 The next maneuvers that should be performed to follow the current route.
 Multiple maneuvers are displayed simultaneously, however the system may limit the number of maneuvers shown at the same time.
 */
@property (nonatomic, readwrite, copy) NSArray<CPManeuver *> *upcomingManeuvers;

/**
 The trip associated with this navigation session.
 */
@property (nonatomic, readonly, strong) CPTrip *trip;

/**
 Update the travel estimates for the active navigation session and maneuver.
 
 @param estimates The updated travel estimates.
 @param maneuver The maneuver pertaining to this update.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forManeuver:(CPManeuver *)maneuver;


@end

NS_ASSUME_NONNULL_END
