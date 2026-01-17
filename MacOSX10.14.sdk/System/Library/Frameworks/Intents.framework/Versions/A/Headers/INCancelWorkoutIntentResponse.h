//
//  INCancelWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INCancelWorkoutIntentResponseCode) {
    INCancelWorkoutIntentResponseCodeUnspecified = 0,
    INCancelWorkoutIntentResponseCodeReady,
    INCancelWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INCancelWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INCancelWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INCancelWorkoutIntentResponseCodeFailure,
    INCancelWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INCancelWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INCancelWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INCancelWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INCancelWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INCancelWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCancelWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCancelWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
