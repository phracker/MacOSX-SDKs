//
//  INStartAudioCallIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

#import <Intents/INCallAudioRoute.h>

typedef NS_ENUM(NSInteger, INStartAudioCallIntentResponseCode) {
    INStartAudioCallIntentResponseCodeUnspecified = 0,
    INStartAudioCallIntentResponseCodeReady,
    INStartAudioCallIntentResponseCodeContinueInApp,
    INStartAudioCallIntentResponseCodeFailure,
    INStartAudioCallIntentResponseCodeFailureRequiringAppLaunch,
    INStartAudioCallIntentResponseCodeFailureAppConfigurationRequired,
    INStartAudioCallIntentResponseCodeFailureCallingServiceNotAvailable,
    INStartAudioCallIntentResponseCodeFailureContactNotSupportedByApp,
    INStartAudioCallIntentResponseCodeFailureNoValidNumber API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos),
} API_DEPRECATED("INStartAudioCallIntent is deprecated. Please adopt INStartCallIntent instead", ios(10.0, 13.0), watchos(3.2, 6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INStartAudioCallIntent is deprecated. Please adopt INStartCallIntent instead", ios(10.0, 13.0), watchos(3.2, 6.0))
API_UNAVAILABLE(macos, tvos)
@interface INStartAudioCallIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INStartAudioCallIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INStartAudioCallIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
