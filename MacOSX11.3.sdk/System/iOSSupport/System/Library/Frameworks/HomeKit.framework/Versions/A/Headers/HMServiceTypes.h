//
//  HMServiceTypes.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @group Accessory Service Types
 *
 * @brief These constants define the service types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Service type for switch.
 */
HM_EXTERN NSString * const HMServiceTypeSwitch API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for thermostat.
 */
HM_EXTERN NSString * const HMServiceTypeThermostat API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for accessory information.
 */
HM_EXTERN NSString * const HMServiceTypeAccessoryInformation API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for outlet.
 */
HM_EXTERN NSString * const HMServiceTypeOutlet API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for lock management.
 */
HM_EXTERN NSString * const HMServiceTypeLockManagement API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for air quality sensor.
 */
HM_EXTERN NSString * const HMServiceTypeAirQualitySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for carbon dioxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonDioxideSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for carbon monoxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonMonoxideSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for contact sensor.
 */
HM_EXTERN NSString * const HMServiceTypeContactSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for door.
 */
HM_EXTERN NSString * const HMServiceTypeDoor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for humidity sensor.
 */
HM_EXTERN NSString * const HMServiceTypeHumiditySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for leak sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLeakSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for light sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLightSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for motion sensor.
 */
HM_EXTERN NSString * const HMServiceTypeMotionSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for occupancy sensor.
 */
HM_EXTERN NSString * const HMServiceTypeOccupancySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for security system.
 */
HM_EXTERN NSString * const HMServiceTypeSecuritySystem API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stateful programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatefulProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stateless programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatelessProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for smoke sensor.
 */
HM_EXTERN NSString * const HMServiceTypeSmokeSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for temperature sensor.
 */
HM_EXTERN NSString * const HMServiceTypeTemperatureSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for window.
 */
HM_EXTERN NSString * const HMServiceTypeWindow API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for window covering.
 */
HM_EXTERN NSString * const HMServiceTypeWindowCovering API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stream management.
 */
HM_EXTERN NSString * const HMServiceTypeCameraRTPStreamManagement API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for camera control.
 */
HM_EXTERN NSString * const HMServiceTypeCameraControl API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for microphone.
 */
HM_EXTERN NSString * const HMServiceTypeMicrophone API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for speaker.
 */
HM_EXTERN NSString * const HMServiceTypeSpeaker API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for air purifier.
 */
HM_EXTERN NSString * const HMServiceTypeAirPurifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for filter maintenance.
 */
HM_EXTERN NSString * const HMServiceTypeFilterMaintenance API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for slats.
 */
HM_EXTERN NSString * const HMServiceTypeSlats API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for label namespace when accessory supports multiple services of the same type.
 */
HM_EXTERN NSString * const HMServiceTypeLabel API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for irrigation system.
 */
HM_EXTERN NSString * const HMServiceTypeIrrigationSystem API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for valve.
 */
HM_EXTERN NSString * const HMServiceTypeValve API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for faucet.
 */
HM_EXTERN NSString * const HMServiceTypeFaucet API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);


/*!
 * @brief Service type for fan.
 */
HM_EXTERN NSString * const HMServiceTypeFan API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for garage door opener.
 */
HM_EXTERN NSString * const HMServiceTypeGarageDoorOpener API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for lightbulb.
 */
HM_EXTERN NSString * const HMServiceTypeLightbulb API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for lock mechanism.
 */
HM_EXTERN NSString * const HMServiceTypeLockMechanism API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for battery.
 */
HM_EXTERN NSString * const HMServiceTypeBattery API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for ventilation fan.
 */
HM_EXTERN NSString * const HMServiceTypeVentilationFan API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for heater/cooler.
 */
HM_EXTERN NSString * const HMServiceTypeHeaterCooler API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for humidifier-dehumidifier.
 */
HM_EXTERN NSString * const HMServiceTypeHumidifierDehumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for doorbell.
 */
HM_EXTERN NSString * const HMServiceTypeDoorbell API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
