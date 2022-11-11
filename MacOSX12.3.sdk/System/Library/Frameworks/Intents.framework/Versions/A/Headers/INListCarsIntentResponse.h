//
//  INListCarsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCar;

typedef NS_ENUM(NSInteger, INListCarsIntentResponseCode) {
    INListCarsIntentResponseCodeUnspecified = 0,
    INListCarsIntentResponseCodeReady,
    INListCarsIntentResponseCodeInProgress,
    INListCarsIntentResponseCodeSuccess,
    INListCarsIntentResponseCodeFailure,
    INListCarsIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INListCarsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INListCarsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INListCarsIntentResponseCode code;

// An array of INCar objects representing a user’s electric vehicles. These vehicles should potentially respond to an INGetCarPowerLevelStatusIntent request so that the user can navigate with one of these vehicles in Maps.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INCar *> *cars;

@end

NS_ASSUME_NONNULL_END
