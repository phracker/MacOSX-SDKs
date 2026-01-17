//
//  INRideStatus.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRidePhase.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INRideVehicle;
@class INRideDriver;
@class INRideOption;
@class INRideCompletionStatus;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macos, tvos)
@interface INRideStatus : NSObject <NSCopying, NSSecureCoding>

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INRidePhase phase;

// This property should be set if the phase is INRidePhaseCompleted.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideCompletionStatus *completionStatus;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideVehicle *vehicle;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideDriver *driver;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupDate;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedDropOffDate;

// This is the date after arrival at the pickup location after which the ride may stop waiting for the passenger to be picked up.
// The passenger is expected to arrive at pickup before this date.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupEndDate;

// Time range for the scheduled pickup.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *scheduledPickupTime API_AVAILABLE(ios(10.3), watchos(3.2));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<CLPlacemark *> *waypoints;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideOption *rideOption;

@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivityForCancelingInApplication; // If set, and the ride hasn't completed or been canceled yet, the system may open the containing application and request continuation of this activity to request that the ride be canceled. It is appropriate to show confirmation UI to the user when this happens.

// These actions may be available for the user to choose during the ride.
// When shown, the .title of each activity will presented to the user. Selecting an activity will open your application to continue it.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSUserActivity *> *additionalActionActivities;

@end

NS_ASSUME_NONNULL_END
