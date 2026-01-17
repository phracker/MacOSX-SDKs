//
//  HMAccessoryCategoryTypes.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 * @group Accessory Category Types
 *
 * @brief These constants define the accessory category types supported for HomeKit accessories.
 */

/*!
 * @brief Category type for Other.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeOther API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Security System.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeSecuritySystem API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Bridge.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeBridge API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Door.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeDoor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Door Lock.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeDoorLock API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Fan.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeFan API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Garage Door Opener.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeGarageDoorOpener API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*
* @brief Category type for IP Camera.
*/
HM_EXTERN NSString *const HMAccessoryCategoryTypeIPCamera API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Lightbulb.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeLightbulb API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Outlet.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeOutlet API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Programmable Switch.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Range Extender
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeRangeExtender API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Sensor.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Switch.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Thermostat.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeThermostat API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Video Doorbell.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeVideoDoorbell API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Window.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeWindow API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Window Covering.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeWindowCovering API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Purifier.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirPurifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Heater.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirHeater API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Conditioner.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirConditioner API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Humidifier.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirHumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Dehumidifier.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirDehumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Sprinkler.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeSprinkler API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Faucet.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeFaucet API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Shower Head.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeShowerHead API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Television.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeTelevision API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Television Set Top Box.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeTelevisionSetTopBox API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Television Streaming Stick.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeTelevisionStreamingStick API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Wi-Fi Router.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeWiFiRouter API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Speakers.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeSpeaker API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for an audio receiver that supports HAP and AirPlay2.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAudioReceiver API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for AirPort accessories.
 */
HM_EXTERN NSString *const HMAccessoryCategoryTypeAirPort API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
