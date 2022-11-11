//
//  INSearchCallHistoryIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCallRecord;

typedef NS_ENUM(NSInteger, INSearchCallHistoryIntentResponseCode) {
    INSearchCallHistoryIntentResponseCodeUnspecified = 0,
    INSearchCallHistoryIntentResponseCodeReady,
    INSearchCallHistoryIntentResponseCodeContinueInApp,
    INSearchCallHistoryIntentResponseCodeFailure,
    INSearchCallHistoryIntentResponseCodeFailureRequiringAppLaunch,
    INSearchCallHistoryIntentResponseCodeFailureAppConfigurationRequired,
    INSearchCallHistoryIntentResponseCodeInProgress API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
    INSearchCallHistoryIntentResponseCodeSuccess API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
} API_DEPRECATED("INSearchCallHistoryIntentResponseCode is deprecated. There is no replacement.", ios(10.0, 15.0), watchos(3.2, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSearchCallHistoryIntentResponse is deprecated. There is no replacement.", ios(10.0, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INSearchCallHistoryIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchCallHistoryIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchCallHistoryIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INCallRecord *> *callRecords API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
