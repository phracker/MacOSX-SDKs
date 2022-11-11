//
//  INDeleteTasksIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INTask;

typedef NS_ENUM(NSInteger, INDeleteTasksIntentResponseCode) {
    INDeleteTasksIntentResponseCodeUnspecified = 0,
    INDeleteTasksIntentResponseCodeReady,
    INDeleteTasksIntentResponseCodeInProgress,
    INDeleteTasksIntentResponseCodeSuccess,
    INDeleteTasksIntentResponseCodeFailure,
    INDeleteTasksIntentResponseCodeFailureRequiringAppLaunch,
} API_DEPRECATED("INDeleteTasksIntentResponseCode is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INDeleteTasksIntentResponse is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INDeleteTasksIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INDeleteTasksIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INDeleteTasksIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *deletedTasks;

@end

NS_ASSUME_NONNULL_END
