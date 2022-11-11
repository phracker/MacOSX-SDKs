//
//  INStartWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutLocationType.h>

@class INBooleanResolutionResult;
@class INDoubleResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INWorkoutGoalUnitTypeResolutionResult;
@class INWorkoutLocationTypeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INStartWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName
                          goalValue:(nullable NSNumber *)goalValue
                workoutGoalUnitType:(INWorkoutGoalUnitType)workoutGoalUnitType
                workoutLocationType:(INWorkoutLocationType)workoutLocationType
                        isOpenEnded:(nullable NSNumber *)isOpenEnded NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *goalValue NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INWorkoutGoalUnitType workoutGoalUnitType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INWorkoutLocationType workoutLocationType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *isOpenEnded NS_REFINED_FOR_SWIFT;

@end

@class INStartWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INStartWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INStartWorkoutIntentResponse
 */

- (void)handleStartWorkout:(INStartWorkoutIntent *)intent
                completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartWorkoutIntentResponse
 */

- (void)confirmStartWorkout:(INStartWorkoutIntent *)intent
                 completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForStartWorkout:(INStartWorkoutIntent *)intent
                           withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

- (void)resolveGoalValueForStartWorkout:(INStartWorkoutIntent *)intent
                         withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGoalValue(for:with:));

- (void)resolveWorkoutGoalUnitTypeForStartWorkout:(INStartWorkoutIntent *)intent
                                   withCompletion:(void (^)(INWorkoutGoalUnitTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutGoalUnitType(for:with:));

- (void)resolveWorkoutLocationTypeForStartWorkout:(INStartWorkoutIntent *)intent
                                   withCompletion:(void (^)(INWorkoutLocationTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutLocationType(for:with:));

- (void)resolveIsOpenEndedForStartWorkout:(INStartWorkoutIntent *)intent
                           withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveIsOpenEnded(for:with:));

@end

NS_ASSUME_NONNULL_END
