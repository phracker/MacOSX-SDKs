//
//  HMCharacteristic.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMCharacteristicTypes.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;
@class HMService;
@class HMCharacteristicMetadata;

/*!
 * @brief Represent a characteristic on a service of an accessory.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristic : NSObject

/*!
 * @brief The type of the characteristic, e.g. HMCharacteristicTypePowerState.
 */
@property(readonly, copy, nonatomic) NSString *characteristicType;

/*!
 * @brief The localized description of the characteristic.
 */
@property(readonly, copy, nonatomic) NSString *localizedDescription API_AVAILABLE(ios(9.0));

/*!
 * @brief Service that contains this characteristic.
 */
@property(weak, readonly, nonatomic) HMService *service;

/*!
 * @brief Array that describes the properties of the characteristic.
 *
 * @discussion This value corresponds to the properties associated with this characteristic.
 *             The contents of the array are one or more HMCharacteristicProperty constants.
 */
@property(readonly, copy, nonatomic) NSArray<NSString *> *properties;

/*!
 * @brief Meta data associated with the characteristic.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristicMetadata *metadata;

/*!
 * @brief The value of the characteristic.
 *
 * @discussion The value is a cached value that may have been updated as a result of prior
 *             interaction with the accessory.
 */
@property(readonly, copy, nonatomic, nullable) id value;

/*!
 * @brief Specifies whether the characteristic has been enabled to send notifications.
 *
 * @discussion This property is reset to NO if the reachability of the accessory is NO.
 */
@property(readonly, getter=isNotificationEnabled, nonatomic) BOOL notificationEnabled;

/*!
 * @brief A unique identifier for the characteristic.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));


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
- (void)writeValue:(nullable id)value completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Reads the value of the characteristic. The updated value can be read from the 'value' property of the characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)readValueWithCompletionHandler:(void (^)(NSError * __nullable error))completion;

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
- (void)enableNotification:(BOOL)enable completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Sets/clears authorization data used when writing to the characteristic.
 *
 * @param data New authorization data to use. Specify nil to remove authorization data.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAuthorizationData:(nullable NSData *)data completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
