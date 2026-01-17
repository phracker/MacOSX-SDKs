//
//  HMService.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMServiceTypes.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class HMAccessory;
@class HMCharacteristic;

/*!
 * @brief Represents a service provided by an accessory.
 *
 * @discussion This class represents a service provided by an accessory in the home.
 *             A service is composed of one or more characteristics that can be 
 *             modified.
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@interface HMService : NSObject

/*!
 * @brief Accessory that provides this service.
 */
@property (nonatomic, readonly, weak) HMAccessory *accessory;

/*!
 * @brief The type of the service, e.g. HMServiceTypeLightbulb.
 */
@property (nonatomic, readonly, copy) NSString *serviceType;

/*!
 * @brief The localized description of the service.
 */
@property (nonatomic, readonly, copy) NSString *localizedDescription API_AVAILABLE(ios(9.0));

/*!
 * @brief Name for the service.
 *
 * @discussion Returns the service's name that is associated with HomeKit. The initial value is the value of
 *             the name characteristic of the service, if it has one.
 */
@property (nonatomic, readonly, copy) NSString *name;

/*!
 * @brief For HMServiceTypeOutlet and HMServiceTypeSwitch, this is the type of the associated service.
 *
 * @discussion This could be any of the HomeKit Accessory Profile defined services (except HMServiceTypeOutlet
 *             or HMServiceTypeSwitch) that supports HMCharacteristicTypePowerState characteristic.
 */
@property (nullable, nonatomic, readonly, copy) NSString *associatedServiceType;

/*!
 * @brief Array of HMCharacteristic objects that represents all the characteristics
 *        provided by the service.
 */
@property (nonatomic, readonly, copy) NSArray<HMCharacteristic *> *characteristics;

/*!
 * @brief A unique identifier for the service.
 */
@property (nonatomic, readonly, copy) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief Indicates if this service supports user interaction or not.
 *
 * @discussion Applications should use this property to filter out services that the users
 *             should not directly interact with, e.g. HMServiceTypeAccessoryInformation.
 */
@property (nonatomic, readonly, getter=isUserInteractive) BOOL userInteractive API_AVAILABLE(ios(9.0));

/*!
 * @brief Indicates if this services is the primary service.
 *
 * @discussion Applications should use this property to show the primary service on the accessory.
 */
@property (nonatomic, readonly, getter=isPrimaryService) BOOL primaryService API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @brief Array of HMService objects that represents all the services that the service links to.
 *  
 * @discussion Applications should use this property to show logical grouping of services on the accessory.
 *             linkedServices will be nil when the service does not link to any other services.
 */
@property (nonatomic, readonly, copy) NSArray<HMService *> *__nullable linkedServices API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @brief The Matter endpoint identifier that this service is mapped to.
 *
 * @discussion This property is nil for HAP accessories, and set to a valid value for Matter devices.
 */
@property (nullable, nonatomic, readonly, copy) NSNumber *matterEndpointID NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), watchos(11.0), tvos(18.0), macCatalyst(18.0)) API_UNAVAILABLE(macos);

/*!
 * @brief This method is used to change the name of the service.
 *
 * @param name New name for the service.
 *
 * @discussion The new name is stored in HomeKit and not on the accessory.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method is used to set up the service type of the device connected to a contact sensor, switch or an outlet.
 *
 * @param serviceType Service type of the device connected to a contact sensor/switch/outlet service.
 *
 * @discussion This method is only valid for the services of the following types:
 *                 HMServiceTypeOutlet, HMServiceTypeContactSensor and HMServiceTypeSwitch
 *
 *             For services of type HMServiceTypeOutlet and HMServiceTypeSwitch, serviceType can be one of the
 *             HomeKit Accessory Profile defined services (except HMServiceTypeOutlet or HMServiceTypeSwitch)
 *             that supports HMCharacteristicTypePowerState characteristic.
 *
 *             For services of type HMServiceTypeContactSensor, serviceType can be one of the following services:
 *                 HMServiceTypeDoor, HMServiceTypeGarageDoorOpener, HMServiceTypeWindow and HMServiceTypeWindowCovering
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAssociatedServiceType:(nullable NSString *)serviceType completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

- (instancetype)init API_DEPRECATED("HMService objects are created by their parent container objects. Directly creating them is not supported.", ios(8.0, 8.0), watchos(2.0, 2.0), tvos(10.0, 10.0), macCatalyst(14.0, 14.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
