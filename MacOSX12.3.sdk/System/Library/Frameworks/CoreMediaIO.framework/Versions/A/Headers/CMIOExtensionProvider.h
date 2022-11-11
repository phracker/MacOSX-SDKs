/*
    File: CMIOExtensionProvider.h

    Contains: API for CoreMediaIO extensions

    Copyright: © 2019-2021 by Apple Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreMediaIO/CMIOExtensionProperties.h>

NS_ASSUME_NONNULL_BEGIN

@class CMIOExtensionDevice;

/*!
@constant CMIOExtensionInfoDictionaryKey
@abstract
 The CoreMediaIO extension info dictionary key.
*/
FOUNDATION_EXTERN NSString * const CMIOExtensionInfoDictionaryKey API_AVAILABLE(macos(12.3));

/*!
@constant CMIOExtensionMachServiceNameKey
@abstract
 A key contained in the Info.plist that specifies the mach service name.
*/
FOUNDATION_EXTERN NSString * const CMIOExtensionMachServiceNameKey API_AVAILABLE(macos(12.3));

/*!
@class CMIOExtensionProviderProperties
@abstract
 A CMIOExtensionProviderProperties describes CoreMediaIO extension provider properties.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionProviderProperties : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method providerPropertiesWithDictionary:
@abstract
 Return a provider properties instance.
@param propertiesDictionary
 The dictionary of properties.
@result
 A CMIOExtensionProviderProperties instance.
*/
+ (instancetype)providerPropertiesWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary;

/*!
@method initWithDictionary:
@abstract
 Initialize a provider properties instance.
 @param propertiesDictionary
  The dictionary of properties.
@result
 A CMIOExtensionProviderProperties instance.
*/
- (instancetype)initWithDictionary:(NSDictionary<CMIOExtensionProperty, CMIOExtensionPropertyState *> *)propertiesDictionary NS_DESIGNATED_INITIALIZER;

/*!
@property name
@abstract
 The provider name.
@discussion
 The property key is CMIOExtensionPropertyProviderName.
*/
@property(atomic, strong, nullable) NSString *name;

/*!
@property manufacturer
@abstract
 The provider manufacturer.
@discussion
 The property key is CMIOExtensionPropertyProviderManufacturer.
*/
@property(atomic, strong, nullable) NSString *manufacturer;

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
@protocol CMIOExtensionProviderSource <NSObject>
@required

/*!
@method connectClient:error:
@abstract
 Connect a client to the provider.
@param client
 The client.
@param outError
 An error return on failure.
@result
 Return YES is the connection is accepted, NO otherwise.
*/
- (BOOL)connectClient:(CMIOExtensionClient *)client error:(NSError * _Nullable *)outError NS_SWIFT_NAME(connect(to:));

/*!
@method disconnectClient:
@abstract
 Disconnect a client from the provider.
@param client
 The client.
*/
- (void)disconnectClient:(CMIOExtensionClient *)client NS_SWIFT_NAME(disconnect(from:));

/*!
@property availableProperties
@abstract
 The set of available properties.
@discussion
 The availableProperties should not change during the life cycle of the associated provider.
*/
@property(atomic, readonly, copy) NSSet<CMIOExtensionProperty> *availableProperties;

/*!
@method providerPropertiesForProperties:error:
@abstract
 Get the state of properties.
@param properties
 The addresses of properties from which to get the state.
@param outError
 An error return on failure.
@result
 A provider properties instance containing the properties states.
*/
- (nullable CMIOExtensionProviderProperties *)providerPropertiesForProperties:(NSSet<CMIOExtensionProperty> *)properties error:(NSError * _Nullable *)outError;

/*!
@method setProviderProperties:error:
@abstract
 Set the provider properties.
@param providerProperties
 The provider properties instance containing the properties states.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
@discussion
 The property attributes associated with a property state are always nil in setter.
 In case of error, it is highly advisable to pass more detailed information regarding the property or properties that failed in the localizedDescription of the NSError.
*/
- (BOOL)setProviderProperties:(CMIOExtensionProviderProperties *)providerProperties error:(NSError * _Nullable *)outError;

@end

/*!
@class CMIOExtensionProvider
@abstract
 A CMIOExtensionProvider describes a CoreMediaIO extension provider.
*/
API_AVAILABLE(macos(12.3))
@interface CMIOExtensionProvider : NSObject

/*!
@method startServiceWithProvider:
@abstract
 Starts the CoreMediaIO Extension machinery.
*/
+ (void)startServiceWithProvider:(CMIOExtensionProvider *)provider NS_SWIFT_NAME(startService(provider:));


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
@method providerWithSource:clientQueue:
@abstract
 Returns a provider instance.
@param source
 The provider source.
@param clientQueue
 The client dispatch queue, or nil for the default dispatch queue.
@result
 A CMIOExtensionProvider instance.
*/
+ (instancetype)providerWithSource:(id<CMIOExtensionProviderSource>)source clientQueue:(nullable dispatch_queue_t)clientQueue;

/*!
@method initWithSource:clientQueue:
@abstract
 Initialize a provider instance.
@param source
 The provider source.
@param clientQueue
 The client dispatch queue, or nil for the default dispatch queue.
@result
 A CMIOExtensionProvider instance.
*/
- (instancetype)initWithSource:(id<CMIOExtensionProviderSource>)source clientQueue:(nullable dispatch_queue_t)clientQueue NS_DESIGNATED_INITIALIZER;

/*!
@property source
@abstract
 The provider source.
*/
@property(atomic, readonly, weak) id<CMIOExtensionProviderSource> source;

/*!
@property clientQueue
@abstract
 The dispatch queue on which source methods from the provider/device/stream will be called.
*/
@property(atomic, readonly, strong) dispatch_queue_t clientQueue;

/*!
@property connectedClients
@abstract
 The array of connected clients.
@discussion
 This property is key-value observable.
*/
@property(atomic, readonly, copy) NSArray<CMIOExtensionClient *> *connectedClients;

/*!
@property devices
@abstract
 The devices array of the provider.
@discussion
 This property is not key-value observable.
*/
@property(atomic, readonly, copy) NSArray<CMIOExtensionDevice *> *devices;

/*!
@method addDevice:error:
@abstract
 Add a device to the provider devices array.
@param device
 The device to be added to the provider devices array.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)addDevice:(CMIOExtensionDevice *)device error:(NSError * _Nullable *)outError;

/*!
@method removeDevice:error:
@abstract
 Remove a device from the provider devices array.
@param device
 The device to be removed from the provider devices array.
@param outError
 An error return on failure.
@result
 Return YES on success, NO otherwise.
*/
- (BOOL)removeDevice:(CMIOExtensionDevice *)device error:(NSError * _Nullable *)outError;

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
