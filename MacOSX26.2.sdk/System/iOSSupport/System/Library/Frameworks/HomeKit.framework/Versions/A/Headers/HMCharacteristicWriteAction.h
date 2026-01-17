//
//  HMCharacteristicWriteAction.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMAction.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class HMCharacteristic;

/*!
 * @brief This class is used to represent an entry in an action set that writes a specific
 *        value to a characteristic.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicWriteAction<TargetValueType : id<NSCopying>> : HMAction

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @brief Initializer method that ties the action to a particular characteristic.
 *
 * @param characteristic The characteristic bound to the action.
 *
 * @param targetValue The target value for the characteristic.
 *
 * @return Instance object representing the characteristic write action.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic targetValue:(TargetValueType)targetValue API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief The characteristic associated with the action.
 */
@property (nonatomic, readonly, strong) HMCharacteristic *characteristic;

/*!
 * @brief The target value for the action.
 */
@property (nonatomic, readonly, copy) TargetValueType targetValue;

/*!
 * @brief This method is used to change target value for the characteristic.
 *
 * @param targetValue New target value for the characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateTargetValue:(TargetValueType)targetValue completionHandler:(void (^)(NSError *__nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
