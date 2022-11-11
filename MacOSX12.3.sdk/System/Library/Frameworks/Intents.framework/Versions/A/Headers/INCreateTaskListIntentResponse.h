//
//  INCreateTaskListIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INTaskList;

typedef NS_ENUM(NSInteger, INCreateTaskListIntentResponseCode) {
    INCreateTaskListIntentResponseCodeUnspecified = 0,
    INCreateTaskListIntentResponseCodeReady,
    INCreateTaskListIntentResponseCodeInProgress,
    INCreateTaskListIntentResponseCodeSuccess,
    INCreateTaskListIntentResponseCodeFailure,
    INCreateTaskListIntentResponseCodeFailureRequiringAppLaunch,
} API_DEPRECATED("INCreateTaskListIntentResponseCode is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INCreateTaskListIntentResponse is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INCreateTaskListIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCreateTaskListIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCreateTaskListIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INTaskList *createdTaskList;

@end

NS_ASSUME_NONNULL_END
