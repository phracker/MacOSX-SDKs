//
//  INAnswerCallIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCallRecord;

typedef NS_ENUM(NSInteger, INAnswerCallIntentResponseCode) {
    INAnswerCallIntentResponseCodeUnspecified = 0,
    INAnswerCallIntentResponseCodeReady,
    INAnswerCallIntentResponseCodeContinueInApp,
    INAnswerCallIntentResponseCodeInProgress,
    INAnswerCallIntentResponseCodeSuccess,
    INAnswerCallIntentResponseCodeFailure,
    INAnswerCallIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2))
API_UNAVAILABLE(tvos)
@interface INAnswerCallIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INAnswerCallIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INAnswerCallIntentResponseCode code;

// The call that was targeted, if found, otherwise empty. The call type should be in-progress or missed.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INCallRecord *> *callRecords;

@end

NS_ASSUME_NONNULL_END
