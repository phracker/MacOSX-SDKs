//
//  INGetCarLockStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INGetCarLockStatusIntentResponseCode) {
    INGetCarLockStatusIntentResponseCodeUnspecified = 0,
    INGetCarLockStatusIntentResponseCodeReady,
    INGetCarLockStatusIntentResponseCodeInProgress,
    INGetCarLockStatusIntentResponseCodeSuccess,
    INGetCarLockStatusIntentResponseCodeFailure,
    INGetCarLockStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INGetCarLockStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetCarLockStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetCarLockStatusIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *locked NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
