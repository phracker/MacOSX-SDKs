/*
    File: CMIOExtensionDevice.h

    Contains: API for CoreMediaIO extensions

    Copyright: © 2019-2021 by Apple Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreMediaIO/CMIOExtensionProperties.h>

NS_ASSUME_NONNULL_BEGIN

@class CMIOExtensionStream;

/*!
@class CMIOExtensionDeviceProperties
@abstract
 A CMIOExtensionDeviceProperties describes a CoreMediaIO extension device properties.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionDeviceProperties : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method devicePropertiesWithDictionary:
@abstract
 Return a device properties instance.
@param propertiesDictionary
 The dictionary of properties.
@result
 A CMIOExtensionDeviceProperties instance.
*/
+ (instancetype)devicePropertiesWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary;

/*!
@method initWithDictionary:
@abstract
 Initialize a device properties instance.
 @param propertiesDictionary
  The dictionary of properties.
@result
 A CMIOExtensionDeviceProperties instance.
*/
- (instancetype)initWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary NS_DESIGNATED_INITIALIZER;

/*!
@property model
@abstract
 The device model.
@discussion
 The property key is CMIOExtensionPropertyDeviceModel.
*/
@property(atomic, strong, nullable) NSString *model;

/*!
@property suspended
@abstract
 Indicates whether the device is suspended.
@discussion
 The property key is CMIOExtensionPropertyDeviceIsSuspended.
*/
@property(atomic, strong, nullable) NSNumber *suspended NS_REFINED_FOR_SWIFT;

/*!
@property transportType
@abstract
 The transport type of the receiver (e.g. USB, PCI, etc) whose value correspond to the audio transport type ( kIOAudioDeviceTransportType... ) defined in <IOKit/audio/IOAudioTypes.h>.
@discussion
 The property key is CMIOExtensionPropertyDeviceTransportType.
*/
@property(atomic, strong, nullable) NSNumber *transportType NS_REFINED_FOR_SWIFT;

/*!
@property linkedCoreAudioDeviceUID
@abstract
 The device linked CoreAudio device UID.
@discussion
 The property key is CMIOExtensionPropertyDeviceLinkedCoreAudioDeviceUID.
*/
@property(atomic, strong, nullable) NSString *linkedCoreAudioDeviceUID;

/*!
@property setPropertyState:forProperty:
@abstract
 Set the property value.
@param propertyState
 The property state.
@param property
 The property key.
@discussion
 Setting nil to propertyState does remove the property.
*/
- (void)setPropertyState:(nullable CMIOExtensionPropertyState *)propertyState forProperty:(CMIOExtensionProperty)property;

/*!
@property propertiesDictionary
@abstract
 The dictionary of properties.
@discussion
 The dictionary containing all keys and values.
*/
@property(atomic, copy) NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *propertiesDictionary;

@end

API_AVAILABLE(macos(12.3))
@protocol CMIOExtensionDeviceSource <NSObject>
@required

/*!
@property availableProperties
@abstract
 The set of available properties.
@discussion
 The availableProperties should not change during the life cycle of the associated device.
*/
@property(atomic, readonly, copy) NSSet<CMIOExtensionProperty> *availableProperties;

/*!
@method devicePropertiesForProperties:error:
@abstract
 Get the state of properties.
@param properties
 The addresses of properties from which to get the state.
@param outError
 An error return on failure.
@result
 A device properties instance containing the properties states.
*/
- (nullable CMIOExtensionDeviceProperties *)devicePropertiesForProperties:(NSSet<CMIOExtensionProperty> *)properties error:(NSError * _Nullable *)outError;

/*!
@method setDeviceProperties:error:
@abstract
 Set the provider properties.
@param deviceProperties
 The device properties instance containing the properties states.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
@discussion
 The property attributes associated with a property state are always nil in setter.
 In case of error, it is highly advisable to pass more detailed information regarding the property or properties that failed in the localizedDescription of the NSError.
*/
- (BOOL)setDeviceProperties:(CMIOExtensionDeviceProperties *)deviceProperties error:(NSError * _Nullable *)outError;

@end

/*!
@class CMIOExtensionDevice
@abstract
 A CMIOExtensionDevice describes a device.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionDevice : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method deviceWithLocalizedName:deviceID:legacyDeviceID:source:
@abstract
 Returns a device instance.
@param localizedName
 The localized name of the device.
@param deviceID
 The device id (as a UUID).
@param legacyDeviceID
 The device identifier as a string (for backward compatibility with existing CMIO DAL clients, it may differ from deviceID.UUIDString). May be nil if your device has no compatibility requirements.
@param source
 The device source, a client instantiated object for the device that conforms to the CMIOExtensionDeviceSource protocol.
@result
 A CMIOExtensionDevice instance.
*/
+ (instancetype)deviceWithLocalizedName:(NSString *)localizedName deviceID:(NSUUID *)deviceID legacyDeviceID:(nullable NSString *)legacyDeviceID source:(id<CMIOExtensionDeviceSource>)source;

/*!
@method initWithLocalizedName:deviceID:legacyDeviceID:source:
@abstract
 Initialize a device instance.
@param localizedName
 The localized name of the device.
@param deviceID
 The device id (as a UUID).
@param legacyDeviceID
 The device identifier as a string (for backward compatibility with existing CMIO DAL clients, it may differ from deviceID.UUIDString). May be nil if your device has no compatibility requirements.
@param source
 The device source, a client instantiated object for the device that conforms to the CMIOExtensionDeviceSource protocol.
@result
 A CMIOExtensionDevice instance.
*/
- (instancetype)initWithLocalizedName:(NSString *)localizedName deviceID:(NSUUID *)deviceID legacyDeviceID:(nullable NSString *)legacyDeviceID source:(id<CMIOExtensionDeviceSource>)source NS_DESIGNATED_INITIALIZER;

/*!
@method deviceWithLocalizedName:deviceID:source:
@abstract
 Returns a device instance.
@param localizedName
 The localized name of the device.
@param deviceID
 The device unique identifier.
@param source
 The device source, a client instantiated object for the device that conforms to the CMIOExtensionDeviceSource protocol.
@result
 A CMIOExtensionDevice instance.
*/
+ (instancetype)deviceWithLocalizedName:(NSString *)localizedName deviceID:(NSUUID *)deviceID source:(id<CMIOExtensionDeviceSource>)source API_UNAVAILABLE(macos);

/*!
@method initWithLocalizedName:deviceID:source:
@abstract
 Initialize a device instance.
@param localizedName
 The localized name of the device.
@param deviceID
 The device unique identifier.
@param source
 The device source, a client instantiated object for the device that conforms to the CMIOExtensionDeviceSource protocol.
@result
 A CMIOExtensionDevice instance.
*/
- (instancetype)initWithLocalizedName:(NSString *)localizedName deviceID:(NSUUID *)deviceID source:(id<CMIOExtensionDeviceSource>)source API_UNAVAILABLE(macos);

/*!
@property localizedName
@abstract
 The localized name of the device.
*/
@property(atomic, readonly, copy) NSString *localizedName;

/*!
@property deviceID
@abstract
 The device identifier as UUID.
*/
@property(atomic, readonly, copy) NSUUID *deviceID;

/*!
@property legacyDeviceID
@abstract
 The device identifier as a string (for backward compatibility with AVCaptureDevice.uniqueIdentifier)
*/
@property(atomic, readonly, copy) NSString *legacyDeviceID;

/*!
@property source
@abstract
 The device source.
*/
@property(atomic, readonly, weak) id<CMIOExtensionDeviceSource> source;

/*!
@property streams
@abstract
 The streams array of the device.
@discussion
 This property is not key-value observable.
*/
@property(atomic, readonly, copy) NSArray<CMIOExtensionStream *> *streams;

/*!
@method addStream:error:
@abstract
 Add a stream to the device streams array.
@param stream
 The stream to be added to the device streams array.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)addStream:(CMIOExtensionStream *)stream error:(NSError * _Nullable *)outError;

/*!
@method removeStream:error:
@abstract
 Remove a stream from the device streams array.
@param stream
 The stream to be removed from the device streams array.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)removeStream:(CMIOExtensionStream *)stream error:(NSError * _Nullable *)outError;

/*!
@method notifyPropertiesChanged:
@abstract
 Notify client(s) of device properties changes.
@param propertyStates
 The dictionary of properties having changed.
*/
- (void)notifyPropertiesChanged:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertyStates;

@end

NS_ASSUME_NONNULL_END
