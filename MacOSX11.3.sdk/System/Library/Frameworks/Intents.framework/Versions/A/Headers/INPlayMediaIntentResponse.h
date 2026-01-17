//
//  INPlayMediaIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INPlayMediaIntentResponseCode) {
    INPlayMediaIntentResponseCodeUnspecified = 0,
    INPlayMediaIntentResponseCodeReady,
    INPlayMediaIntentResponseCodeContinueInApp,
    INPlayMediaIntentResponseCodeInProgress,
    INPlayMediaIntentResponseCodeSuccess,
    INPlayMediaIntentResponseCodeHandleInApp API_UNAVAILABLE(watchos),
    INPlayMediaIntentResponseCodeFailure,
    INPlayMediaIntentResponseCodeFailureRequiringAppLaunch,
    INPlayMediaIntentResponseCodeFailureUnknownMediaType,
    INPlayMediaIntentResponseCodeFailureNoUnplayedContent,
    INPlayMediaIntentResponseCodeFailureRestrictedContent,
} API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INPlayMediaIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INPlayMediaIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INPlayMediaIntentResponseCode code;

// This dictionary should be populated using the keys from MPNowPlayingInfoCenter.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDictionary<NSString *, id> *nowPlayingInfo;

@end

NS_ASSUME_NONNULL_END
