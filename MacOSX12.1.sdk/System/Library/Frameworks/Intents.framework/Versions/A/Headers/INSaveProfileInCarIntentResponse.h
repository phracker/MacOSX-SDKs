//
//  INSaveProfileInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSaveProfileInCarIntentResponseCode) {
    INSaveProfileInCarIntentResponseCodeUnspecified = 0,
    INSaveProfileInCarIntentResponseCodeReady,
    INSaveProfileInCarIntentResponseCodeInProgress,
    INSaveProfileInCarIntentResponseCodeSuccess,
    INSaveProfileInCarIntentResponseCodeFailure,
    INSaveProfileInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_DEPRECATED("INSaveProfileInCarIntentResponseCode is deprecated. There is no replacement.", ios(10.0, 15.0)) API_UNAVAILABLE(macos, watchos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSaveProfileInCarIntentResponse is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INSaveProfileInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSaveProfileInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSaveProfileInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
