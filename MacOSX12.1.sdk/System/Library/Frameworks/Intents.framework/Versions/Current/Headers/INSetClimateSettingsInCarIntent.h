//
//  INSetClimateSettingsInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarSeat.h>
#import <Intents/INRelativeSetting.h>

@class INBooleanResolutionResult;
@class INCarAirCirculationModeResolutionResult;
@class INCarSeatResolutionResult;
@class INDoubleResolutionResult;
@class INIntegerResolutionResult;
@class INRelativeSettingResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INTemperatureResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSetClimateSettingsInCarIntent is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INSetClimateSettingsInCarIntent : INIntent

- (instancetype)initWithEnableFan:(nullable NSNumber *)enableFan
             enableAirConditioner:(nullable NSNumber *)enableAirConditioner
             enableClimateControl:(nullable NSNumber *)enableClimateControl
                   enableAutoMode:(nullable NSNumber *)enableAutoMode
               airCirculationMode:(INCarAirCirculationMode)airCirculationMode
                    fanSpeedIndex:(nullable NSNumber *)fanSpeedIndex
               fanSpeedPercentage:(nullable NSNumber *)fanSpeedPercentage
          relativeFanSpeedSetting:(INRelativeSetting)relativeFanSpeedSetting
                      temperature:(nullable NSMeasurement<NSUnitTemperature *> *)temperature
       relativeTemperatureSetting:(INRelativeSetting)relativeTemperatureSetting
                      climateZone:(INCarSeat)climateZone
                          carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableFan NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableAirConditioner NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableClimateControl NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableAutoMode NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarAirCirculationMode airCirculationMode;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fanSpeedIndex NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fanSpeedPercentage NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeFanSpeedSetting;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitTemperature *> *temperature;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeTemperatureSetting;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSeat climateZone;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetClimateSettingsInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetClimateSettingsInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_DEPRECATED("INSetClimateSettingsInCarIntentHandling is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@protocol INSetClimateSettingsInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetClimateSettingsInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetClimateSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetClimateSettingsInCarIntentResponse
 */

- (void)handleSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                           completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetClimateSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetClimateSettingsInCarIntentResponse
 */

- (void)confirmSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                            completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveEnableFanForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableFan(for:with:));

- (void)resolveEnableAirConditionerForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                               withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAirConditioner(for:with:));

- (void)resolveEnableClimateControlForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                               withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableClimateControl(for:with:));

- (void)resolveEnableAutoModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                         withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAutoMode(for:with:));

- (void)resolveAirCirculationModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                             withCompletion:(void (^)(INCarAirCirculationModeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAirCirculationMode(for:with:));

- (void)resolveFanSpeedIndexForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                        withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedIndex(for:with:));

- (void)resolveFanSpeedPercentageForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                             withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedPercentage(for:with:));

- (void)resolveRelativeFanSpeedSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                                  withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeFanSpeedSetting(for:with:));

- (void)resolveTemperatureForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INTemperatureResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemperature(for:with:));

- (void)resolveRelativeTemperatureSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                                     withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeTemperatureSetting(for:with:));

- (void)resolveClimateZoneForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INCarSeatResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveClimateZone(for:with:));

- (void)resolveCarNameForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                  withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END
