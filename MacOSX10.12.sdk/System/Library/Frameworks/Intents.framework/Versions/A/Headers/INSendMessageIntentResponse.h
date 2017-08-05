//
//  INSendMessageIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSendMessageIntentResponseCode) {
    INSendMessageIntentResponseCodeUnspecified = 0,
    INSendMessageIntentResponseCodeReady,
    INSendMessageIntentResponseCodeInProgress,
    INSendMessageIntentResponseCodeSuccess,
    INSendMessageIntentResponseCodeFailure,
    INSendMessageIntentResponseCodeFailureRequiringAppLaunch,
    INSendMessageIntentResponseCodeFailureMessageServiceNotAvailable,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSendMessageIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendMessageIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendMessageIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
