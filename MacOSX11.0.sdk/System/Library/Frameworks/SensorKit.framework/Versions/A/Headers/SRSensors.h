//
//  SRSensors.h
//  SensorKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

typedef NSString * SRSensor NS_TYPED_ENUM API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN SRSensor const SRSensorAmbientLightSensor API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorAccelerometer API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorRotationRate API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorVisits API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorPedometerData API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorDeviceUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorMessagesUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorPhoneUsageReport API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorOnWristState API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);
SR_EXTERN SRSensor const SRSensorKeyboardMetrics API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
