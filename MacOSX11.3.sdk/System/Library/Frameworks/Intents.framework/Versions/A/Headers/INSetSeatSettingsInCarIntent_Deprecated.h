//
//  INSetSeatSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INSetSeatSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetSeatSettingsInCarIntent (Deprecated)

- (instancetype)initWithEnableHeating:(nullable NSNumber *)enableHeating
                        enableCooling:(nullable NSNumber *)enableCooling
                        enableMassage:(nullable NSNumber *)enableMassage
                                 seat:(INCarSeat)seat
                                level:(nullable NSNumber *)level
                 relativeLevelSetting:(INRelativeSetting)relativeLevelSetting API_DEPRECATED_WITH_REPLACEMENT("-initWithEnableHeating:enableCooling:enableMassage:seat:level:relativeLevelSetting:relativeLevelSetting:carName:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
