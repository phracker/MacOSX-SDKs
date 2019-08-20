//
//  INSetClimateSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Intents/INSetClimateSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetClimateSettingsInCarIntent (Deprecated)

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
                      climateZone:(INCarSeat)climateZone API_DEPRECATED_WITH_REPLACEMENT("-initWithEnableFan:enableAirConditioner:enableClimateControl:enableAutoMode:airCirculationMode:fanSpeedIndex:fanSpeedPercentage:relativeFanSpeedSetting:temperature:relativeTemperatureSetting:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
