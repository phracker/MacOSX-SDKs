//
//  HKDevice.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKDevicePropertyKeyName
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device name.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyName API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyManufacturer
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device manufacturer.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyManufacturer API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyModel
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device model.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyModel API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyHardwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a hardware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyHardwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyFirmwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a firmware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyFirmwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeySoftwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a software version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeySoftwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyLocalIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a local identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyLocalIdentifier API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyUDIDeviceIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a UDI device identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyUDIDeviceIdentifier API_AVAILABLE(ios(9.0), watchos(2.0));



HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKDevice : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      name
 @abstract      The name of the receiver.
 @discussion    The user-facing name, such as the one displayed in the Bluetooth Settings for a BLE device.
 */
@property (readonly, nullable) NSString *name;

/*!
 @property      manufacturer
 @abstract      The manufacturer of the receiver.
 */
@property (readonly, nullable) NSString *manufacturer;

/*!
 @property      model
 @abstract      The model of the receiver.
 */
@property (readonly, nullable) NSString *model;

/*!
 @property      hardwareVersion
 @abstract      The hardware revision of the receiver.
 */
@property (readonly, nullable) NSString *hardwareVersion;

/*!
 @property      firmwareVersion
 @abstract      The firmware revision of the receiver.
 */
@property (readonly, nullable) NSString *firmwareVersion;

/*!
 @property      softwareVersion
 @abstract      The software revision of the receiver.
 */
@property (readonly, nullable) NSString *softwareVersion;

/*!
 @property      localIdentifier
 @abstract      A unique identifier for the receiver.
 @discussion    This property is available to clients for a local identifier.
                For example, Bluetooth peripherals managed by HealthKit use this
                for the CoreBluetooth UUID which is valid only on the local
                device and thus distinguish the same Bluetooth peripheral used
                between multiple devices.
 */
@property (readonly, nullable) NSString *localIdentifier;

/*!
 @property      UDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's FDA UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the FDA's GUDID (Globally Unique Device
                Identifier Database). Note that for user privacy concerns this field should not be used to
                persist the production identifier portion of the device UDI. HealthKit clients should manage
                the production identifier independently, if needed.
                See http://www.fda.gov/MedicalDevices/DeviceRegulationandGuidance/UniqueDeviceIdentification/ for more information.
 */
@property (readonly, nullable) NSString *UDIDeviceIdentifier;


/*!
 @method        initWithName:manufacturer:model:hardwareVersion:firmwareVersion:softwareVersion:localIdentifier:UDIDeviceIdentifier:
 @abstract      Initialize a new HKDevice with the specified values.
 @discussion    This allows initialization of an HKDevice object based on the
                information provided.
 */
- (instancetype)initWithName:(nullable NSString *)name
                manufacturer:(NSString * _Nullable)manufacturer
                       model:(NSString * _Nullable)model
             hardwareVersion:(NSString * _Nullable)hardwareVersion
             firmwareVersion:(NSString * _Nullable)firmwareVersion
             softwareVersion:(NSString * _Nullable)softwareVersion
             localIdentifier:(NSString * _Nullable)localIdentifier
         UDIDeviceIdentifier:(NSString * _Nullable)UDIDeviceIdentifier;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        localDevice
 @abstract      Returns a device representing the host.
 @discussion    If an app chooses to save samples that were retrieved from the local device, e.g. an HKWorkout with a 
                totalDistance HKQuantity gathered from CoreLocation GPS distances, then this would be an appropriate 
                HKDevice to use.
 */
+ (HKDevice *)localDevice;

@end

NS_ASSUME_NONNULL_END
