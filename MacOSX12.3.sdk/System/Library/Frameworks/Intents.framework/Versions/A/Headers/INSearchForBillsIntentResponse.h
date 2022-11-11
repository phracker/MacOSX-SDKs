//
//  INSearchForBillsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INBillDetails;

typedef NS_ENUM(NSInteger, INSearchForBillsIntentResponseCode) {
    INSearchForBillsIntentResponseCodeUnspecified = 0,
    INSearchForBillsIntentResponseCodeReady,
    INSearchForBillsIntentResponseCodeInProgress,
    INSearchForBillsIntentResponseCodeSuccess,
    INSearchForBillsIntentResponseCodeFailure,
    INSearchForBillsIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForBillsIntentResponseCodeFailureCredentialsUnverified,
    INSearchForBillsIntentResponseCodeFailureBillNotFound,
} API_DEPRECATED("INSearchForBillsIntentResponseCode is deprecated. There is no replacement.", ios(10.3, 15.0), watchos(3.2, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSearchForBillsIntentResponse is deprecated. There is no replacement.", ios(10.3, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INSearchForBillsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForBillsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForBillsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INBillDetails *> *bills;

@end

NS_ASSUME_NONNULL_END
