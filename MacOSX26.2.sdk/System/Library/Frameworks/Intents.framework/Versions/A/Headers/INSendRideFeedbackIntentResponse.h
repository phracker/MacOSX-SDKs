//
//  INSendRideFeedbackIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSendRideFeedbackIntentResponseCode) {
    INSendRideFeedbackIntentResponseCodeUnspecified = 0,
    INSendRideFeedbackIntentResponseCodeReady,
    INSendRideFeedbackIntentResponseCodeSuccess,
    INSendRideFeedbackIntentResponseCodeFailure,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos, tvos)
@interface INSendRideFeedbackIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendRideFeedbackIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendRideFeedbackIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
