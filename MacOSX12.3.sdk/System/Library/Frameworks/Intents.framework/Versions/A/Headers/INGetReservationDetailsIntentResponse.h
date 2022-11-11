//
//  INGetReservationDetailsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INReservation;

typedef NS_ENUM(NSInteger, INGetReservationDetailsIntentResponseCode) {
    INGetReservationDetailsIntentResponseCodeUnspecified = 0,
    INGetReservationDetailsIntentResponseCodeReady,
    INGetReservationDetailsIntentResponseCodeInProgress,
    INGetReservationDetailsIntentResponseCodeSuccess,
    INGetReservationDetailsIntentResponseCodeFailure,
    INGetReservationDetailsIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INGetReservationDetailsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetReservationDetailsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetReservationDetailsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INReservation *> *reservations;

@end

NS_ASSUME_NONNULL_END
