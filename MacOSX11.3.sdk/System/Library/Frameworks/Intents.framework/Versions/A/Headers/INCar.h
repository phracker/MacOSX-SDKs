//
//  INCar.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreGraphics/CoreGraphics.h>
#import <Intents/INCarChargingConnectorType.h>

@class INCarHeadUnit;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INCar : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// Instantiates an INCar object.
- (instancetype)initWithCarIdentifier:(NSString *)carIdentifier
                          displayName:(nullable NSString *)displayName
                                 year:(nullable NSString *)year
                                 make:(nullable NSString *)make
                                model:(nullable NSString *)model
                                color:(nullable CGColorRef)color
                             headUnit:(nullable INCarHeadUnit *)headUnit
          supportedChargingConnectors:(NSArray<INCarChargingConnectorType> *)supportedChargingConnectors NS_DESIGNATED_INITIALIZER;

// An identifier for the vehicles. Use this same value as the carIdentifier property of INGetCarPowerLevelStatusResponse. Do not use the VIN (or the equivalent code) as the identifier.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *carIdentifier;

// A user-defined display name for the vehicle that is expected to be set in the OEM app.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

// Manufacturing year of the vehicle.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *year;

// Make of the vehicle. Should be set by the OEM app. This is later used by Maps to be shown to the user.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *make;

// Model name of the vehicle. Should be set by the OEM app. This is later used by Maps to be shown to the user.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *model;

// Color of the vehicle.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) CGColorRef color;

// A data structure containing the bluetooth identifier and the iAP 2 identifier of the head unit of the vehicle.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCarHeadUnit *headUnit;

// An array containing the supported charging connectors of a vehicle
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<INCarChargingConnectorType> *supportedChargingConnectors;

// Use this method to set the maximum supported power for each charging connector type a vehicle supports. This function can be called multiple times for different connector types.
- (void)setMaximumPower:(NSMeasurement<NSUnitPower *> *)power forChargingConnectorType:(INCarChargingConnectorType)chargingConnectorType NS_SWIFT_NAME(setMaximumPower(_:for:));

// Use this method to read the maximum power set for each charging connector type.
- (nullable NSMeasurement<NSUnitPower *> *)maximumPowerForChargingConnectorType:(INCarChargingConnectorType)chargingConnectorType NS_SWIFT_NAME(maximumPower(for:));

@end

NS_ASSUME_NONNULL_END
