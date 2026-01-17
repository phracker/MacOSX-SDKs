//
//  INGetCarPowerLevelStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INGetCarPowerLevelStatusIntentResponseCode) {
    INGetCarPowerLevelStatusIntentResponseCodeUnspecified = 0,
    INGetCarPowerLevelStatusIntentResponseCodeReady,
    INGetCarPowerLevelStatusIntentResponseCodeInProgress,
    INGetCarPowerLevelStatusIntentResponseCodeSuccess,
    INGetCarPowerLevelStatusIntentResponseCodeFailure,
    INGetCarPowerLevelStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetCarPowerLevelStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetCarPowerLevelStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetCarPowerLevelStatusIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fuelPercentRemaining NS_REFINED_FOR_SWIFT;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *chargePercentRemaining NS_REFINED_FOR_SWIFT;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *distanceRemaining;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *charging NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *minutesToFull NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

@end

NS_ASSUME_NONNULL_END
