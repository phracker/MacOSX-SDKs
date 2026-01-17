//
//  HMCharacteristic.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMCharacteristicTypes.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class HMAccessory;
@class HMService;
@class HMCharacteristicMetadata;

/*!
 * @brief Represent a characteristic on a service of an accessory.
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@interface HMCharacteristic : NSObject

/*!
 * @brief The type of the characteristic, e.g. HMCharacteristicTypePowerState.
 */
@property (nonatomic, readonly, copy) NSString *characteristicType;

/*!
 * @brief The localized description of the characteristic.
 */
@property (nonatomic, readonly, copy) NSString *localizedDescription API_AVAILABLE(ios(9.0));

/*!
 * @brief Service that contains this characteristic.
 */
@property (nonatomic, readonly, weak) HMService *service;

/*!
 * @brief Array that describes the properties of the characteristic.
 *
 * @discussion This value corresponds to the properties associated with this characteristic.
 *             The contents of the array are one or more HMCharacteristicProperty constants.
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *properties;

/*!
 * @brief Meta data associated with the characteristic.
 */
@property (nullable, nonatomic, readonly, strong) HMCharacteristicMetadata *metadata;

/*!
 * @brief The value of the characteristic.
 *
 * @discussion The value is a cached value that may have been updated as a result of prior
 *             interaction with the accessory.
 */
@property (nullable, nonatomic, readonly, copy) id value;

/*!
 * @brief Specifies whether the characteristic has been enabled to send notifications.
 *
 * @discussion This property is reset to NO if the reachability of the accessory is NO.
 */
@property (nonatomic, readonly, getter=isNotificationEnabled) BOOL notificationEnabled;

/*!
 * @brief A unique identifier for the characteristic.
 */
@property (nonatomic, readonly, copy) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));


/*!
 * @brief Modifies the value of the characteristic.
 *
 * @param value The value to be written.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 *
 * @discussion The value being written is validated against the metadata, format and permissions.
 *             The value written may be bounded by metadata for characteristics with int and 
 *             float format. If validation fails, the error provided to the completion handler
 *             indicates the type of failure.
 */
- (void)writeValue:(nullable id)value completionHandler:(void (^)(NSError *__nullable error))completion;

/*!
 * @brief Reads the value of the characteristic. The updated value can be read from the 'value' property of the characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)readValueWithCompletionHandler:(void (^)(NSError *__nullable error))completion;

/*!
 * @brief Enables/disables notifications or indications for the value of a specified characteristic.
 *
 * @param enable A Boolean value indicating whether you wish to receive notifications or
 *                indications whenever the characteristic’s value changes.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)enableNotification:(BOOL)enable completionHandler:(void (^)(NSError *__nullable error))completion;

/*!
 * @brief Sets/clears authorization data used when writing to the characteristic.
 *
 * @param data New authorization data to use. Specify nil to remove authorization data.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAuthorizationData:(nullable NSData *)data completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

- (instancetype)init API_DEPRECATED("HMCharacteristic objects are created by their parent container objects. Directly creating them is not supported.", ios(8.0, 8.0), watchos(2.0, 2.0), tvos(10.0, 10.0), macCatalyst(14.0, 14.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
