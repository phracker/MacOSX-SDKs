//
//  INSearchForPhotosIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class CLPlacemark;

typedef NS_ENUM(NSInteger, INSearchForPhotosIntentResponseCode) {
    INSearchForPhotosIntentResponseCodeUnspecified = 0,
    INSearchForPhotosIntentResponseCodeReady,
    INSearchForPhotosIntentResponseCodeContinueInApp,
    INSearchForPhotosIntentResponseCodeFailure,
    INSearchForPhotosIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForPhotosIntentResponseCodeFailureAppConfigurationRequired,
} API_DEPRECATED("INSearchForPhotosIntentResponseCode is deprecated. There is no replacement.", ios(10.0, 15.0), watchos(3.2, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSearchForPhotosIntentResponse is deprecated. There is no replacement.", ios(10.0, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INSearchForPhotosIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForPhotosIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForPhotosIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *searchResultsCount NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
