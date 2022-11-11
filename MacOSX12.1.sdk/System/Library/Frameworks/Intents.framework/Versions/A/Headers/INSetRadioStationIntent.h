//
//  INSetRadioStationIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRadioType.h>

@class INDoubleResolutionResult;
@class INIntegerResolutionResult;
@class INRadioTypeResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSetRadioStationIntent is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INSetRadioStationIntent : INIntent

- (instancetype)initWithRadioType:(INRadioType)radioType
                        frequency:(nullable NSNumber *)frequency
                      stationName:(nullable NSString *)stationName
                          channel:(nullable NSString *)channel
                     presetNumber:(nullable NSNumber *)presetNumber NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRadioType radioType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *frequency NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *stationName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *channel;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *presetNumber NS_REFINED_FOR_SWIFT;

@end

@class INSetRadioStationIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetRadioStationIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_DEPRECATED("INSetRadioStationIntentHandling is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@protocol INSetRadioStationIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetRadioStationIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetRadioStationIntentResponse containing the details of the result of having executed the intent

 @see  INSetRadioStationIntentResponse
 */

- (void)handleSetRadioStation:(INSetRadioStationIntent *)intent
                   completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetRadioStationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetRadioStationIntentResponse
 */

- (void)confirmSetRadioStation:(INSetRadioStationIntent *)intent
                    completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRadioTypeForSetRadioStation:(INSetRadioStationIntent *)intent
                            withCompletion:(void (^)(INRadioTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRadioType(for:with:));

- (void)resolveFrequencyForSetRadioStation:(INSetRadioStationIntent *)intent
                            withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFrequency(for:with:));

- (void)resolveStationNameForSetRadioStation:(INSetRadioStationIntent *)intent
                              withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStationName(for:with:));

- (void)resolveChannelForSetRadioStation:(INSetRadioStationIntent *)intent
                          withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveChannel(for:with:));

- (void)resolvePresetNumberForSetRadioStation:(INSetRadioStationIntent *)intent
                               withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePresetNumber(for:with:));

@end

NS_ASSUME_NONNULL_END
